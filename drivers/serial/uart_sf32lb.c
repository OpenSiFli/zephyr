/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2024 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sifli_uart

#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/sys/__assert.h>
#include <soc.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

#include <zephyr/sys/__assert.h>
#include <zephyr/sys/byteorder.h>
#include <bf0_hal.h>

LOG_MODULE_REGISTER(uart_sf32lb, CONFIG_UART_LOG_LEVEL);

// Driver data structure
struct uart_sf32lb_data {
    uint32_t base_addr;
    UART_HandleTypeDef handle;

    struct
    {
        DMA_HandleTypeDef handle;
        int last_index;
    } dma_rx;
    struct
    {
        DMA_HandleTypeDef handle;
        int last_index;
    } dma_tx;
	struct k_work_delayable tx_timeout_work;
	struct k_work_delayable rx_timeout_work;
    struct uart_config uart_cfg;
    uart_callback_t callback;
    void *          user_data;
};

// Driver configuration structure
struct uart_sf32lb_config {
    void (*irq_config_func)(const struct device * dev);
    const struct device *clock_dev;
    const clock_control_subsys_t clock_subsys;
};

static int sifli_configure(const struct device *dev)
{
    struct uart_sf32lb_data *uart = dev->data;

    if (uart->uart_cfg.parity!=UART_CFG_PARITY_NONE && uart->uart_cfg.data_bits < UART_CFG_DATA_BITS_9)
        uart->uart_cfg.data_bits++;                           // parity is part of data

    switch (uart->uart_cfg.data_bits)
    {
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
    switch (uart->uart_cfg.stop_bits)
    {
    case UART_CFG_STOP_BITS_1:
        uart->handle.Init.StopBits   = UART_STOPBITS_1;
        break;
    case UART_CFG_STOP_BITS_2:
        uart->handle.Init.StopBits   = UART_STOPBITS_2;
        break;
    case UART_CFG_STOP_BITS_0_5:
        uart->handle.Init.StopBits   = UART_STOPBITS_0_5;
        break;
    case UART_CFG_STOP_BITS_1_5:
        uart->handle.Init.StopBits   = UART_STOPBITS_1_5;
        break;
    default:
        uart->handle.Init.StopBits   = UART_STOPBITS_1;
        break;
    }
    switch (uart->uart_cfg.parity)
    {
    case UART_CFG_PARITY_NONE:
        uart->handle.Init.Parity     = UART_PARITY_NONE;
        break;
    case UART_CFG_PARITY_ODD:
        uart->handle.Init.Parity     = UART_PARITY_ODD;
        break;
    case UART_CFG_PARITY_EVEN:
        uart->handle.Init.Parity     = UART_PARITY_EVEN;
        break;
    default:
        uart->handle.Init.Parity     = UART_PARITY_NONE;
        break;
    }

    if (HAL_UART_Init(&uart->handle) != HAL_OK)
    {
        return -1;
    }
    return 0;
}

// Function prototypes
static void uart_sf32lb_isr(const struct device *dev);

static int uart_sf32lb_init(const struct device *dev);
static int uart_sf32lb_poll_in(const struct device *dev, uint8_t *user_data);
static void uart_sf32lb_poll_out(const struct device *dev, uint8_t c);
static int uart_sf32lb_configure(const struct device *dev, const struct uart_config *cfg);

#ifdef CONFIG_UART_ASYNC_API
static int uart_sf32lb_callback_set(const struct device *dev, uart_callback_t callback, void *user_data);
static int uart_sf32lb_rx_enable(const struct device *dev, uint8_t *buf, size_t len, int32_t timeout);
static int uart_sf32lb_rx_buf_rsp(const struct device *dev, uint8_t *buf, size_t len);
static int uart_sf32lb_rx_disable(const struct device *dev);
static int uart_sf32lb_tx(const struct device *dev, const uint8_t *buf, size_t len, int32_t timeout);
static int uart_sf32lb_tx_abort(const struct device *dev);
#endif

// UART API implementation
static const struct uart_driver_api uart_sf32lb_api = {
    .poll_in = uart_sf32lb_poll_in,
    .poll_out = uart_sf32lb_poll_out,
    .configure = uart_sf32lb_configure,
#ifdef CONFIG_UART_ASYNC_API
	.callback_set =uart_sf32lb_callback_set,
	.rx_enable =uart_sf32lb_rx_enable,
	.rx_buf_rsp =uart_sf32lb_rx_buf_rsp,
	.rx_disable =uart_sf32lb_rx_disable,
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

// Driver initialization function
static int uart_sf32lb_init(const struct device *dev)
{
    struct uart_sf32lb_data *uart = dev->data;
    const struct uart_sf32lb_config *config = dev->config;
    int ret;
    enum clock_control_status status;

    status = clock_control_get_status(config->clock_dev, config->clock_subsys);
    LOG_INF("UART clock status: %d", status);

    ret = clock_control_on(config->clock_dev, config->clock_subsys);
    if (ret < 0) {
        return ret;
    }

    // Initialize driver - specific data
    uart->handle.Instance          = (USART_TypeDef *)uart->base_addr;
    uart->handle.Init.BaudRate     = uart->uart_cfg.baudrate;
    uart->handle.Init.Mode         = UART_MODE_TX_RX;
    uart->handle.Init.OverSampling = UART_OVERSAMPLING_16;

	  config->irq_config_func(dev);
    sifli_configure(dev);
    return 0;
}

// Poll - based receive function
static int uart_sf32lb_poll_in(const struct device *dev, uint8_t *c)
{
    struct uart_sf32lb_data *uart = dev->data;
    if (__HAL_UART_GET_FLAG(&(uart->handle), UART_FLAG_RXNE) != RESET) {
        *c = (uint8_t)__HAL_UART_GETC(&uart->handle);
        return 0;
    }
    return -1;
}

// Poll - based transmit function
static void uart_sf32lb_poll_out(const struct device *dev, uint8_t c)
{
    struct uart_sf32lb_data *data = dev->data;

    __HAL_UART_CLEAR_FLAG(&(data->handle), UART_FLAG_TC);
    __HAL_UART_PUTC(&data->handle, c);
    while (__HAL_UART_GET_FLAG(&(data->handle), UART_FLAG_TC) == RESET);
}

// Configure the UART function
static int uart_sf32lb_configure(const struct device *dev, const struct uart_config *cfg)
{
    struct uart_sf32lb_data *uart = dev->data;

    // Update the configuration
    memcpy(&(uart->uart_cfg),cfg, sizeof(struct uart_config));
    sifli_configure(dev);
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

// Interrupt service routine
static void uart_sf32lb_isr(const struct device *dev)
{
    __asm("B .");
}

#define SF32LB_UART_IRQ_HANDLER_DECL(index)				\
	static void uart_sf32lb_irq_config_func_##index(const struct device *dev);

#define SF32LB_UART_IRQ_HANDLER(index)					\
static void uart_sf32lb_irq_config_func_##index(const struct device *dev)	\
{									\
	IRQ_CONNECT(DT_INST_IRQN(index),				\
		DT_INST_IRQ(index, priority),				\
		uart_sf32lb_isr, DEVICE_DT_INST_GET(index),		\
		0);							\
	irq_enable(DT_INST_IRQN(index));				\
}

#define SF32LB_UART_IRQ_HANDLER_FUNC(index)				\
	.irq_config_func = uart_sf32lb_irq_config_func_##index,

#define SF32LB_UART_INIT(index)						\
SF32LB_UART_IRQ_HANDLER_DECL(index)					\
\
static const struct uart_config uart_cfg_##index = {				\
	.baudrate   = 1000000,		\
	.parity     = UART_CFG_PARITY_NONE,			            \
	.stop_bits  = UART_CFG_STOP_BITS_1,		                \
	.data_bits  = UART_CFG_DATA_BITS_8,		                \
	.flow_ctrl  = UART_CFG_FLOW_CTRL_NONE,	                \
};\
\
static const struct uart_sf32lb_config uart_sf32lb_cfg_##index = {	\
	SF32LB_UART_IRQ_HANDLER_FUNC(index) \
    .clock_dev = DEVICE_DT_GET(DT_INST_CLOCKS_CTLR(index)), \
    .clock_subsys = (clock_control_subsys_t)DT_INST_CLOCKS_CELL(index, id), \
};									\
\
static struct uart_sf32lb_data uart_sf32lb_data_##index = {	\
	.uart_cfg = uart_cfg_##index,					\
    .base_addr = DT_INST_REG_ADDR(index)            \
};\
\
DEVICE_DT_INST_DEFINE(index,						                \
		    uart_sf32lb_init,					                    \
		    PM_DEVICE_DT_INST_GET(index),			                \
		    &uart_sf32lb_data_##index, &uart_sf32lb_cfg_##index,	\
		    PRE_KERNEL_1, CONFIG_SERIAL_INIT_PRIORITY,		        \
		    &uart_sf32lb_api);				                        \
                                                                    \
SF32LB_UART_IRQ_HANDLER(index)						                \

DT_INST_FOREACH_STATUS_OKAY(SF32LB_UART_INIT)
