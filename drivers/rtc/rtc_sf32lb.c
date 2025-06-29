/*
 * SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sifli_sf32lb_rtc

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/sys/util.h>
#include <zephyr/logging/log.h>
#include <soc.h>

#include "bf0_hal.h"

LOG_MODULE_REGISTER(rtc_sf32lb, CONFIG_RTC_LOG_LEVEL);

struct rtc_sf32lb_data {
	RTC_HandleTypeDef hrtc;
	struct rtc_time time;
};

struct rtc_sf32lb_config {
	uint32_t reg;
	void (*irq_config_func)(const struct device *dev);
};

static int rtc_sf32lb_set_time(const struct device *dev, const struct rtc_time *time)
{
	struct rtc_sf32lb_data *data = dev->data;
	RTC_TimeTypeDef rtc_time;
	RTC_DateTypeDef rtc_date;
	HAL_StatusTypeDef status;

	if (!time) {
		return -EINVAL;
	}

	/* Convert from struct rtc_time to RTC_TimeTypeDef and RTC_DateTypeDef */
	rtc_time.Hours = time->tm_hour;
	rtc_time.Minutes = time->tm_min;
	rtc_time.Seconds = time->tm_sec;
	rtc_time.TimeFormat = RTC_HOURFORMAT_24;
	rtc_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	rtc_time.StoreOperation = RTC_STOREOPERATION_RESET;

	rtc_date.WeekDay = time->tm_wday;
	rtc_date.Month = time->tm_mon + 1;  /* RTC months are 1-12 */
	rtc_date.Date = time->tm_mday;
	rtc_date.Year = time->tm_year - 100; /* RTC years are 0-99 */

	status = HAL_RTC_SetTime(&data->hrtc, &rtc_time, RTC_FORMAT_BIN);
	if (status != HAL_OK) {
		LOG_ERR("Failed to set RTC time");
		return -EIO;
	}

	status = HAL_RTC_SetDate(&data->hrtc, &rtc_date, RTC_FORMAT_BIN);
	if (status != HAL_OK) {
		LOG_ERR("Failed to set RTC date");
		return -EIO;
	}

	return 0;
}

static int rtc_sf32lb_get_time(const struct device *dev, struct rtc_time *time)
{
	struct rtc_sf32lb_data *data = dev->data;
	RTC_TimeTypeDef rtc_time;
	RTC_DateTypeDef rtc_date;
	HAL_StatusTypeDef status;

	if (!time) {
		return -EINVAL;
	}

	status = HAL_RTC_GetTime(&data->hrtc, &rtc_time, RTC_FORMAT_BIN);
	if (status != HAL_OK) {
		LOG_ERR("Failed to get RTC time");
		return -EIO;
	}

	status = HAL_RTC_GetDate(&data->hrtc, &rtc_date, RTC_FORMAT_BIN);
	if (status != HAL_OK) {
		LOG_ERR("Failed to get RTC date");
		return -EIO;
	}

	/* Convert from RTC_TimeTypeDef and RTC_DateTypeDef to struct rtc_time */
	time->tm_hour = rtc_time.Hours;
	time->tm_min = rtc_time.Minutes;
	time->tm_sec = rtc_time.Seconds;
	time->tm_wday = rtc_date.WeekDay;
	time->tm_mon = rtc_date.Month - 1;  /* Convert to 0-11 range */
	time->tm_mday = rtc_date.Date;
	time->tm_year = rtc_date.Year + 100; /* Convert to years since 1900 */

	return 0;
}

static int rtc_sf32lb_init(const struct device *dev)
{
	struct rtc_sf32lb_data *data = dev->data;
	const struct rtc_sf32lb_config *config = dev->config;
	HAL_StatusTypeDef status;

	/* Initialize RTC */
	data->hrtc.Instance = (RTC_TypeDef *)config->reg;
	data->hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	data->hrtc.Init.DivAInt = 0;
	data->hrtc.Init.DivAFrac = 0;
	data->hrtc.Init.DivB = RC10K_SUB_SEC_DIVB;

	status = HAL_RTC_Init(&data->hrtc, 0);
	if (status != HAL_OK) {
		LOG_ERR("Failed to initialize RTC");
		return -EIO;
	}

	/* Configure RTC interrupts if needed */
	if (config->irq_config_func) {
		config->irq_config_func(dev);
	}

	return 0;
}

static const struct rtc_driver_api rtc_sf32lb_driver_api = {
	.set_time = rtc_sf32lb_set_time,
	.get_time = rtc_sf32lb_get_time,
};

#define RTC_SF32LB_INIT(n) \
	static void rtc_sf32lb_irq_config_func_##n(const struct device *dev); \
	static struct rtc_sf32lb_data rtc_sf32lb_data_##n; \
	static const struct rtc_sf32lb_config rtc_sf32lb_config_##n = { \
		.reg = DT_INST_REG_ADDR(n), \
		.irq_config_func = rtc_sf32lb_irq_config_func_##n, \
	}; \
	DEVICE_DT_INST_DEFINE(n, \
		rtc_sf32lb_init, \
		NULL, \
		&rtc_sf32lb_data_##n, \
		&rtc_sf32lb_config_##n, \
		POST_KERNEL, \
		CONFIG_RTC_INIT_PRIORITY, \
		&rtc_sf32lb_driver_api); \
	static void rtc_sf32lb_irq_config_func_##n(const struct device *dev) \
	{ \
		IRQ_CONNECT(DT_INST_IRQN(n), \
			DT_INST_IRQ(n, priority), \
			HAL_RTC_IRQHandler, \
			DEVICE_DT_INST_GET(n), \
			0); \
		irq_enable(DT_INST_IRQN(n)); \
	}

DT_INST_FOREACH_STATUS_OKAY(RTC_SF32LB_INIT)
