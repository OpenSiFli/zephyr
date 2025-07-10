/*
 * Copyright (c) 2025 Qingsong Gou <gouqs@hotmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#define DT_DRV_COMPAT focaltech_ft6146

#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(ft6146, CONFIG_INPUT_LOG_LEVEL);

/* FT6146 register definitions */
#define FT6146_REG_DEVICE_MODE        0x00
#define FT6146_REG_GEST_ID           0x01
#define FT6146_REG_TD_STATUS         0x02
#define FT6146_REG_P1_XH             0x03
#define FT6146_REG_P1_XL             0x04
#define FT6146_REG_P1_YH             0x05
#define FT6146_REG_P1_YL             0x06
#define FT6146_REG_P1_WEIGHT         0x07
#define FT6146_REG_P1_MISC           0x08
#define FT6146_REG_P2_XH             0x09
#define FT6146_REG_P2_XL             0x0A
#define FT6146_REG_P2_YH             0x0B
#define FT6146_REG_P2_YL             0x0C
#define FT6146_REG_P2_WEIGHT         0x0D
#define FT6146_REG_P2_MISC           0x0E
#define FT6146_REG_THRESHOLD         0x80
#define FT6146_REG_FILTER_COE        0x85
#define FT6146_REG_CTRL              0x86
#define FT6146_REG_TIMEENTERMONITOR  0x87
#define FT6146_REG_PERIODACTIVE      0x88
#define FT6146_REG_PERIODMONITOR     0x89
#define FT6146_REG_RADIAN_VALUE      0x91
#define FT6146_REG_OFFSET_LEFT_RIGHT 0x92
#define FT6146_REG_OFFSET_UP_DOWN    0x93
#define FT6146_REG_DIST_LEFT_RIGHT   0x94
#define FT6146_REG_DIST_UP_DOWN      0x95
#define FT6146_REG_ZOOM_DIS_SQR      0x96
#define FT6146_REG_RADIAN_THRESHOLD  0x97
#define FT6146_REG_SMALL_OBJECT_THRESHOLD 0x98

/* Device mode values */
#define FT6146_DEVICE_MODE_NORMAL    0x00
#define FT6146_DEVICE_MODE_TEST      0x04
#define FT6146_DEVICE_MODE_SYSTEM    0x01

/* Gesture IDs */
#define FT6146_GESTURE_NO_GESTURE    0x00
#define FT6146_GESTURE_MOVE_UP       0x10
#define FT6146_GESTURE_MOVE_RIGHT    0x14
#define FT6146_GESTURE_MOVE_DOWN     0x18
#define FT6146_GESTURE_MOVE_LEFT     0x1C
#define FT6146_GESTURE_ZOOM_IN       0x48
#define FT6146_GESTURE_ZOOM_OUT      0x49

/* Reset timing */
#define FT6146_RESET_DELAY_MS        10
#define FT6146_POST_RESET_DELAY_MS   100

#define MAX_POINT_NUM 2

#define FT6146_READ_ID_H            (0xA3)
#define FT6146_READ_ID_L            (0x9F)

struct ft6146_data {
	const struct device *dev;
	const struct device *int_gpio;
	struct gpio_callback int_cb;
	struct k_work work;
	struct k_timer poll_timer;
	uint8_t i2c_addr;
	uint16_t x_max;
	uint16_t y_max;
	bool gesture_enabled;
	bool last_touch_state;
};

struct ft6146_config {
	struct i2c_dt_spec i2c;
	struct gpio_dt_spec int_gpio;
	struct gpio_dt_spec reset_gpio;
	uint16_t x_max;
	uint16_t y_max;
	bool gesture_enabled;
};

static void ft6146_process_touch(const struct device *dev, uint8_t status)
{
	const struct ft6146_config *config = dev->config;
	//struct ft6146_data *data = dev->data;
	uint8_t point_data[14];
	uint8_t touch_num = 0;
	uint8_t  event_flag = 0;
	uint16_t x, y;
	int id = 0;
	int ret;

	/* Read touch data */
	ret = i2c_burst_read_dt(&config->i2c, FT6146_REG_GEST_ID, point_data, sizeof(point_data));
	if (ret < 0) {
		LOG_ERR("Failed to read touch data: %d", ret);
		return;
	}

	touch_num = point_data[1] & 0x0f;
	LOG_DBG("%s:touch_num:%d", __func__, touch_num);
	if (touch_num > MAX_POINT_NUM) {
			return;
		} else if (touch_num == 0) {
			input_report_key(dev, INPUT_BTN_TOUCH, 0, true, K_FOREVER);
	} else {
		for (int i = 0; i < touch_num; i++) {
			event_flag = (point_data[2 + i * 6] >> 6) & 0x03;
			id  = point_data[4 + i * 6] >> 4;
			x = ((point_data[2 + i * 6] & 0x0F) << 8) + point_data[3 + i * 6];
			y = ((point_data[4 + i * 6] & 0x0F) << 8) + point_data[5 + i * 6];
			LOG_DBG("%s %d :event_flag:%d, id:%d, x:%d, y:%d", __func__, __LINE__, event_flag, id, x, y);

			/* Report touch event */
			input_report_abs(dev, INPUT_ABS_X, x, false, K_FOREVER);
			input_report_abs(dev, INPUT_ABS_Y, y, false, K_FOREVER);
			input_report_key(dev, INPUT_BTN_TOUCH, 1, true, K_FOREVER);
		}
	}

}

static void ft6146_work_handler(struct k_work *work)
{
	struct ft6146_data *data = CONTAINER_OF(work, struct ft6146_data, work);
	const struct device *dev = data->dev;

	ft6146_process_touch(dev, 0);
}

#ifndef CONFIG_INPUT_FT6146_INTERRUPT
static void ft6146_poll_timer_handler(struct k_timer *timer)
{
	struct ft6146_data *data = CONTAINER_OF(timer, struct ft6146_data, poll_timer);
	k_work_submit(&data->work);
}
#else
static void ft6146_isr_handler(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	struct ft6146_data *data = CONTAINER_OF(cb, struct ft6146_data, int_cb);

	k_work_submit(&data->work);
}
#endif

static int ft6146_reset(const struct device *dev)
{
	const struct ft6146_config *config = dev->config;
	int ret;

	if (!config->reset_gpio.port) {
		return 0;
	}

	/* Assert reset */
	ret = gpio_pin_set_dt(&config->reset_gpio, 0);
	if (ret < 0) {
		LOG_ERR("Failed to assert reset: %d", ret);
		return ret;
	}

	k_msleep(FT6146_RESET_DELAY_MS);

	/* De-assert reset */
	ret = gpio_pin_set_dt(&config->reset_gpio, 1);
	if (ret < 0) {
		LOG_ERR("Failed to de-assert reset: %d", ret);
		return ret;
	}

	k_msleep(FT6146_POST_RESET_DELAY_MS);

	return 0;
}

static int ft6146_init(const struct device *dev)
{
	const struct ft6146_config *config = dev->config;
	struct ft6146_data *data = dev->data;
	int ret;
	uint8_t id;

	if (!device_is_ready(config->i2c.bus)) {
		LOG_ERR("I2C bus not ready");
		return -ENODEV;
	}

	data->dev = dev;

	if (config->reset_gpio.port) {
		if (!device_is_ready(config->reset_gpio.port)) {
			LOG_ERR("Reset GPIO not ready");
			return -ENODEV;
		}

		ret = gpio_pin_configure_dt(&config->reset_gpio, GPIO_OUTPUT_INACTIVE);
		if (ret < 0) {
			LOG_ERR("Failed to configure reset GPIO: %d", ret);
			return ret;
		}

		/* Perform reset sequence */
		ret = ft6146_reset(dev);
		if (ret < 0) {
			return ret;
		}
	}

	ret = i2c_reg_read_byte_dt(&config->i2c, FT6146_READ_ID_H, &id);
	if (ret < 0) {
		LOG_ERR("Failed to read ID_H: %d", ret);
		return ret;
	}
	LOG_INF("ft6146 chip ID: 0x%x", id);
	ret = i2c_reg_read_byte_dt(&config->i2c, FT6146_READ_ID_L, &id);
	if (ret < 0) {
		LOG_ERR("Failed to read ID_L: %d", ret);
		return ret;
	}
	LOG_INF("ft6146 chip ID: 0x%x", id);

#ifdef CONFIG_INPUT_FT6146_INTERRUPT
	ret = gpio_pin_configure_dt(&config->int_gpio, GPIO_INPUT);
	if (ret < 0) {
		LOG_ERR("Failed to configure interrupt GPIO: %d", ret);
		return ret;
	}

	ret = gpio_pin_interrupt_configure_dt(&config->int_gpio, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret < 0) {
		LOG_ERR("Failed to configure interrupt: %d", ret);
		return ret;
	}

	gpio_init_callback(&data->int_cb, ft6146_isr_handler, BIT(config->int_gpio.pin));
	ret = gpio_add_callback(config->int_gpio.port, &data->int_cb);
	if (ret < 0) {
		LOG_ERR("Failed to add callback: %d", ret);
		return ret;
	}
#else
	/* Initialize polling timer */
	k_timer_init(&data->poll_timer, ft6146_poll_timer_handler, NULL);
	k_timer_start(&data->poll_timer, K_MSEC(CONFIG_INPUT_FT6416_PERIOD),
						  K_MSEC(CONFIG_INPUT_FT6416_PERIOD));
#endif

	/* Initialize reset GPIO if present */
	if (config->reset_gpio.port) {
		if (!device_is_ready(config->reset_gpio.port)) {
			LOG_ERR("Reset GPIO not ready");
			return -ENODEV;
		}

		ret = gpio_pin_configure_dt(&config->reset_gpio, GPIO_OUTPUT_INACTIVE);
		if (ret < 0) {
			LOG_ERR("Failed to configure reset GPIO: %d", ret);
			return ret;
		}

		/* Perform reset sequence */
		ret = ft6146_reset(dev);
		if (ret < 0) {
			return ret;
		}
	}

	/* Initialize work queue */
	k_work_init(&data->work, ft6146_work_handler);

	LOG_INF("FT6146 initialized");
	return 0;
}

#define FT6146_INIT(n) \
	static struct ft6146_data ft6146_data_##n; \
	\
	static const struct ft6146_config ft6146_config_##n = { \
		.i2c = I2C_DT_SPEC_INST_GET(n), \
		.reset_gpio = GPIO_DT_SPEC_INST_GET_OR(n, reset_gpios, {0}), \
		COND_CODE_1(CONFIG_INPUT_FT6146_INTERRUPT, \
		(.int_gpio = GPIO_DT_SPEC_INST_GET(n, int_gpios),), ()) \
	}; \
	\
	DEVICE_DT_INST_DEFINE(n, ft6146_init, NULL, \
				  &ft6146_data_##n, \
				  &ft6146_config_##n, \
				  POST_KERNEL, \
				  CONFIG_INPUT_INIT_PRIORITY, \
				  NULL);

DT_INST_FOREACH_STATUS_OKAY(FT6146_INIT)
