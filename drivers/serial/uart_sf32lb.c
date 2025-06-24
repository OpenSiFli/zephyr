/*
 * SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sifli_sf32lb_uart

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

#include <bf0_hal.h>

LOG_MODULE_REGISTER(uart_sf32lb, CONFIG_UART_LOG_LEVEL);

struct uart_sf32lb_data {
	UART_HandleTypeDef handle;

	struct {
		DMA_HandleTypeDef handle;
		int last_index;
	} dma_rx;
	struct {
		DMA_HandleTypeDef handle;
		int last_index;
	} dma_tx;
	struct k_work_delayable tx_timeout_work;
	struct k_work_delayable rx_timeout_work;
	struct uart_config uart_cfg;
	uart_callback_t callback;
	void *user_data;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	uart_irq_callback_user_data_t irq_callback;
	void *cb_data;
#endif
};

struct uart_sf32lb_config {
	USART_TypeDef *reg;
	const struct pinctrl_dev_config *pincfg;
	const struct device *clock_dev;
	const clock_control_subsys_t clock_subsys;
#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
	void (*irq_config_func)(const struct device *dev);
#endif
};

static int sf32lb_uart_configure(const struct device *dev)
{
	struct uart_sf32lb_data *uart = dev->data;

	if (uart->uart_cfg.parity != UART_CFG_PARITY_NONE &&
	    uart->uart_cfg.data_bits < UART_CFG_DATA_BITS_9) {
		uart->uart_cfg.data_bits++; // parity is part of data
	}

	switch (uart->uart_cfg.data_bits) {
	case UART_CFG_DATA_BITS_6:
		uart->handle.Init.WordLength = UART_WORDLENGTH_6B;
		break;
	case UART_CFG_DATA_BITS_7:
		uart->handle.Init.WordLength = UART_WORDLENGTH_7B;
		break;
	case UART_CFG_DATA_BITS_8:
		uart->handle.Init.WordLength = UART_WORDLENGTH_8B;
		break;
	case UART_CFG_DATA_BITS_9:
		uart->handle.Init.WordLength = UART_WORDLENGTH_9B;
		break;
	default:
		uart->handle.Init.WordLength = UART_WORDLENGTH_8B;
		break;
	}

	switch (uart->uart_cfg.stop_bits) {
	case UART_CFG_STOP_BITS_1:
		uart->handle.Init.StopBits = UART_STOPBITS_1;
		break;
	case UART_CFG_STOP_BITS_2:
		uart->handle.Init.StopBits = UART_STOPBITS_2;
		break;
	case UART_CFG_STOP_BITS_0_5:
		uart->handle.Init.StopBits = UART_STOPBITS_0_5;
		break;
	case UART_CFG_STOP_BITS_1_5:
		uart->handle.Init.StopBits = UART_STOPBITS_1_5;
		break;
	default:
		uart->handle.Init.StopBits = UART_STOPBITS_1;
		break;
	}

	switch (uart->uart_cfg.parity) {
	case UART_CFG_PARITY_NONE:
		uart->handle.Init.Parity = UART_PARITY_NONE;
		break;
	case UART_CFG_PARITY_ODD:
		uart->handle.Init.Parity = UART_PARITY_ODD;
		break;
	case UART_CFG_PARITY_EVEN:
		uart->handle.Init.Parity = UART_PARITY_EVEN;
		break;
	default:
		uart->handle.Init.Parity = UART_PARITY_NONE;
		break;
	}

	if (HAL_UART_Init(&uart->handle) != HAL_OK) {
		return -1;
	}
	return 0;
}

#ifdef CONFIG_UART_ASYNC_API
static int uart_sf32lb_callback_set(const struct device *dev, uart_callback_t callback, void *user_data);
static int uart_sf32lb_rx_enable(const struct device *dev, uint8_t *buf, size_t len, int32_t timeout);
static int uart_sf32lb_rx_buf_rsp(const struct device *dev, uint8_t *buf, size_t len);
static int uart_sf32lb_rx_disable(const struct device *dev);
static int uart_sf32lb_tx(const struct device *dev, const uint8_t *buf, size_t len, int32_t timeout);
static int uart_sf32lb_tx_abort(const struct device *dev);
#endif

static int uart_sf32lb_poll_in(const struct device *dev, uint8_t *c)
{
	struct uart_sf32lb_data *data = dev->data;
	int ret = -EIO;

	if (__HAL_UART_GET_FLAG(&(data->handle), UART_FLAG_RXNE) != RESET) {
		*c = (uint8_t)__HAL_UART_GETC(&data->handle);
		return 0;
	}
	return ret;
}

static void uart_sf32lb_poll_out(const struct device *dev, uint8_t c)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_CLEAR_FLAG(&(data->handle), UART_FLAG_TC);
	__HAL_UART_PUTC(&data->handle, c);
	while (__HAL_UART_GET_FLAG(&(data->handle), UART_FLAG_TC) == RESET);
}

static int uart_sf32lb_configure(const struct device *dev, const struct uart_config *cfg)
{
	struct uart_sf32lb_data *data = dev->data;

	memcpy(&(data->uart_cfg), cfg, sizeof(struct uart_config));
	sf32lb_uart_configure(dev);

	return 0;
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static int sf32lb_uart_fifo_fill(const struct device *dev, const uint8_t *tx_data, int len)
{
	struct uart_sf32lb_data *data = dev->data;
	int i;

	for (i = 0; i < len; i++) {
		if (__HAL_UART_GET_FLAG(&data->handle, UART_FLAG_TXE) == RESET) {
			break;
		}
		__HAL_UART_PUTC(&data->handle, tx_data[i]);
	}

	return i;
}

static int sf32lb_uart_fifo_read(const struct device *dev, uint8_t *rx_data, const int size)
{
	struct uart_sf32lb_data *data = dev->data;
	int i;

	for (i = 0; i < size; i++) {
		if (__HAL_UART_GET_FLAG(&data->handle, UART_FLAG_RXNE) == RESET) {
			break;
		}
		rx_data[i] = __HAL_UART_GETC(&data->handle);
	}

	return i;
}

static void sf32lb_uart_irq_tx_enable(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_ENABLE_IT(&data->handle, UART_IT_TXE);
}

static void sf32lb_uart_irq_tx_disable(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_DISABLE_IT(&data->handle, UART_IT_TXE);
}

static int sf32lb_uart_irq_tx_ready(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	return __HAL_UART_GET_FLAG(&data->handle, UART_FLAG_TXE);
}

static int sf32lb_uart_irq_tx_complete(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	return __HAL_UART_GET_FLAG(&data->handle, UART_FLAG_TC);
}

static void sf32lb_uart_irq_rx_enable(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_ENABLE_IT(&data->handle, UART_IT_RXNE);
}

static void sf32lb_uart_irq_rx_disable(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_DISABLE_IT(&data->handle, UART_IT_RXNE);
}

static int sf32lb_uart_irq_rx_full(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	return __HAL_UART_GET_FLAG(&data->handle, UART_FLAG_RXNE);
}

static void sf32lb_uart_irq_err_enable(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_ENABLE_IT(&data->handle, UART_IT_PE);
	__HAL_UART_ENABLE_IT(&data->handle, UART_IT_ERR);
}

static void sf32lb_uart_irq_err_disable(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	__HAL_UART_DISABLE_IT(&data->handle, UART_IT_PE);
	__HAL_UART_DISABLE_IT(&data->handle, UART_IT_ERR);
}

static int sf32lb_uart_irq_is_pending(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	return ((__HAL_UART_GET_FLAG(&data->handle, UART_FLAG_RXNE) &&
		 __HAL_UART_GET_IT_SOURCE(&data->handle, UART_IT_RXNE)) ||
		(__HAL_UART_GET_FLAG(&data->handle, UART_FLAG_TXE) &&
		 __HAL_UART_GET_IT_SOURCE(&data->handle, UART_IT_TXE)));
}

static int sf32lb_uart_irq_update(const struct device *dev)
{
	return 1;
}

static void sf32lb_uart_irq_callback_set(const struct device *dev, uart_irq_callback_user_data_t cb,
					 void *user_data)
{
	struct uart_sf32lb_data *data = dev->data;

	data->irq_callback = cb;
	data->cb_data = user_data;
}
#endif

static const struct uart_driver_api uart_sf32lb_api = {
	.poll_in = uart_sf32lb_poll_in,
	.poll_out = uart_sf32lb_poll_out,
	.configure = uart_sf32lb_configure,
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.fifo_fill = sf32lb_uart_fifo_fill,
	.fifo_read = sf32lb_uart_fifo_read,
	.irq_tx_enable = sf32lb_uart_irq_tx_enable,
	.irq_tx_disable = sf32lb_uart_irq_tx_disable,
	.irq_tx_complete = sf32lb_uart_irq_tx_complete,
	.irq_tx_ready = sf32lb_uart_irq_tx_ready,
	.irq_rx_enable = sf32lb_uart_irq_rx_enable,
	.irq_rx_disable = sf32lb_uart_irq_rx_disable,
	.irq_rx_ready = sf32lb_uart_irq_rx_full,
	.irq_err_enable = sf32lb_uart_irq_err_enable,
	.irq_err_disable = sf32lb_uart_irq_err_disable,
	.irq_is_pending = sf32lb_uart_irq_is_pending,
	.irq_update = sf32lb_uart_irq_update,
	.irq_callback_set = sf32lb_uart_irq_callback_set,
#endif
#ifdef CONFIG_UART_ASYNC_API
	.callback_set = uart_sf32lb_callback_set,
	.rx_enable = uart_sf32lb_rx_enable,
	.rx_buf_rsp = uart_sf32lb_rx_buf_rsp,
	.rx_disable = uart_sf32lb_rx_disable,
	.tx = uart_sf32lb_tx,
	.tx_abort = uart_sf32lb_tx_abort,
#endif
};

#ifdef CONFIG_UART_ASYNC_API
static int uart_sf32lb_callback_set(const struct device *dev, uart_callback_t callback, void *user_data)
{
    struct uart_sf32lb_data *data = dev->data;
    data->callback=callback;
    data->user_data=user_data;
}
static int uart_sf32lb_rx_enable(const struct device *dev, uint8_t *buf, size_t len, int32_t timeout)
{
    __HAL_LINKDMA(&(uart->handle), hdmarx, uart->dma_rx.handle);
    uart->handle.hdmarx->Instance = uart->config->dma_rx->Instance;
    uart->handle.hdmarx->Init.Request = uart->config->dma_rx->request;
    irq = uart->config->dma_rx->dma_irq;
#ifndef DMA_SUPPORT_DYN_CHANNEL_ALLOC
    HAL_NVIC_SetPriority(irq, 0, 0);
    HAL_NVIC_EnableIRQ(irq);
#endif /* !DMA_SUPPORT_DYN_CHANNEL_ALLOC */
    if (direction == RT_SERIAL_DMA_RX)  // For RX DMA, also need to enable UART IRQ.
    {
        __HAL_UART_ENABLE_IT(&(uart->handle), UART_IT_IDLE);
        HAL_NVIC_SetPriority(uart->config->irq_type, 1, 0);
        HAL_NVIC_EnableIRQ(uart->config->irq_type);
    }
    HAL_UART_DmaTransmit(&(uart->handle), buf, len, (direction == RT_SERIAL_DMA_RX) ? DMA_PERIPH_TO_MEMORY : DMA_MEMORY_TO_PERIPH);
}

static int uart_sf32lb_rx_buf_rsp(const struct device *dev, uint8_t *buf, size_t len)
{
}

static int uart_sf32lb_rx_disable(const struct device *dev);
static int uart_sf32lb_tx(const struct device *dev, const uint8_t *buf, size_t len, int32_t timeout);
static int uart_sf32lb_tx_abort(const struct device *dev);
#endif

static int uart_sf32lb_init(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;
	const struct uart_sf32lb_config *config = dev->config;
	int err = 0;

	err = pinctrl_apply_state(config->pincfg, PINCTRL_STATE_DEFAULT);
	if (err) {
		return err;
	}

	err = clock_control_on(config->clock_dev, (clock_control_subsys_t)config->clock_subsys);
	if (err) {
		return err;
	}
	data->handle.Instance = config->reg;
	data->handle.Init.BaudRate = data->uart_cfg.baudrate;
	data->handle.Init.Mode = UART_MODE_TX_RX;
	data->handle.Init.OverSampling = UART_OVERSAMPLING_16;

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	config->irq_config_func(dev);
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

	sf32lb_uart_configure(dev);

	return 0;
}

#ifdef CONFIG_UART_ASYNC_API
/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(const struct device *dev)
{
    struct uart_sf32lb_data *uart = dev->data;

    /* UART in mode Receiver -------------------------------------------------*/
    if ((__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_RXNE) != RESET) &&
            (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#ifdef RT_SERIAL_USING_DMA
    else if ((uart->uart_rx_dma_flag) && (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_IDLE) != RESET) &&
             (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_IDLE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(&uart->handle);
        level = rt_hw_interrupt_disable();
        recv_total_index = serial->config.bufsz - __HAL_DMA_GET_COUNTER(&(uart->dma_rx.handle));
        if (recv_total_index < uart->dma_rx.last_index)
            recv_len = serial->config.bufsz + recv_total_index - uart->dma_rx.last_index;
        else
            recv_len = recv_total_index - uart->dma_rx.last_index;
        uart->dma_rx.last_index = recv_total_index;
        rt_hw_interrupt_enable(level);

        if (recv_len)
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    else if ((uart->uart_tx_dma_flag)
             && (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TC) != RESET)
             && (__HAL_UART_GET_IT_SOURCE(&(uart->handle), UART_IT_TC) != RESET))
    {
        __HAL_UART_CLEAR_FLAG(&uart->handle, UART_CLEAR_TCF);
        uart->handle.gState = HAL_UART_STATE_READY;
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
        __HAL_UART_DISABLE_IT(&(uart->handle), UART_IT_TC);
    }
#endif
    else
    {
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_NE) != RESET)
        {
            __HAL_UART_CLEAR_NEFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_FE) != RESET)
        {
            __HAL_UART_CLEAR_FEFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_PE) != RESET)
        {
            __HAL_UART_CLEAR_PEFLAG(&uart->handle);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_CTS) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_CTS);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TXE) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TXE);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_TC) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_TC);
        }
        if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_RXNE) != RESET)
        {
            UART_INSTANCE_CLEAR_FUNCTION(&(uart->handle), UART_FLAG_RXNE);
        }
    }
}

#endif

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void uart_sf32lb_isr(const struct device *dev)
{
	struct uart_sf32lb_data *data = dev->data;

	if (data->irq_callback) {
		data->irq_callback(dev, data->cb_data);
	}
}

#define SF32LB_UART_IRQ_HANDLER_DECL(index)                                                        \
	static void uart_sf32lb_irq_config_func_##index(const struct device *dev);

#define SF32LB_UART_IRQ_HANDLER(index)                                                             \
	static void uart_sf32lb_irq_config_func_##index(const struct device *dev)                  \
	{                                                                                          \
		IRQ_CONNECT(DT_INST_IRQN(index), DT_INST_IRQ(index, priority), uart_sf32lb_isr,    \
			    DEVICE_DT_INST_GET(index), 0);                                         \
		irq_enable(DT_INST_IRQN(index));                                                   \
	}

#define SF32LB_UART_IRQ_HANDLER_FUNC(index) .irq_config_func = uart_sf32lb_irq_config_func_##index,
#else
#define SF32LB_UART_IRQ_HANDLER_DECL(index)
#define SF32LB_UART_IRQ_HANDLER(index)
#define SF32LB_UART_IRQ_HANDLER_FUNC(index)
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

#define SF32LB_UART_INIT(index)                                                                    \
	SF32LB_UART_IRQ_HANDLER_DECL(index)                                                        \
	PINCTRL_DT_INST_DEFINE(index);                                                             \
                                                                                                   \
	static const struct uart_config uart_cfg_##index = {                                       \
		.baudrate = DT_INST_PROP(index, current_speed),                                    \
		.parity = DT_INST_ENUM_IDX(index, parity),                                         \
		.stop_bits = DT_INST_ENUM_IDX(index, stop_bits),                                   \
		.data_bits = DT_INST_ENUM_IDX(index, data_bits),                                   \
		.flow_ctrl = DT_INST_PROP(index, hw_flow_control) ? UART_CFG_FLOW_CTRL_RTS_CTS     \
								  : UART_CFG_FLOW_CTRL_NONE,       \
	};                                                                                         \
                                                                                                   \
	static const struct uart_sf32lb_config uart_sf32lb_cfg_##index = {                         \
		.reg = (USART_TypeDef *)DT_INST_REG_ADDR(index),                                   \
		SF32LB_UART_IRQ_HANDLER_FUNC(index)                                                \
		.pincfg = PINCTRL_DT_INST_DEV_CONFIG_GET(index),                                   \
		.clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(index)),                            \
		.clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(index, id),            \
	};                                                                                         \
                                                                                                   \
	static struct uart_sf32lb_data uart_sf32lb_data_##index = {                                \
		.uart_cfg = uart_cfg_##index,                                                      \
	};                                                                                         \
                                                                                                   \
	DEVICE_DT_INST_DEFINE(index, uart_sf32lb_init, PM_DEVICE_DT_INST_GET(index),               \
			      &uart_sf32lb_data_##index, &uart_sf32lb_cfg_##index, PRE_KERNEL_1,   \
			      CONFIG_SERIAL_INIT_PRIORITY, &uart_sf32lb_api);                      \
                                                                                                   \
	SF32LB_UART_IRQ_HANDLER(index)

DT_INST_FOREACH_STATUS_OKAY(SF32LB_UART_INIT)
