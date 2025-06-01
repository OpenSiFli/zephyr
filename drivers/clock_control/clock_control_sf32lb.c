/*
 * SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sifli_sf32lb_rcc

#include <stdint.h>

#include <zephyr/arch/cpu.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/clock_control.h>
#include <zephyr/drivers/clock_control/sf32lb_clock_control.h>
#include <zephyr/logging/log.h>
#include <zephyr/dt-bindings/clock/sf32lb525-clock.h>
#include "bf0_hal_rcc.h"

LOG_MODULE_REGISTER(clock_sf32lb, CONFIG_CLOCK_CONTROL_LOG_LEVEL);

struct sf32lb_clock_config {
	uint32_t base;
};

struct sf32lb_clock_data {
};

static int sf32lb_clock_control_on(const struct device *dev,
				   clock_control_subsys_t sys)
{
	UNUSED(dev);
	RCC_MODULE_TYPE id = (RCC_MODULE_TYPE)sys;

	// HAL_RCC_EnableModule(id);
	if (id == RCC_MOD_I2C1) {
		/* Special handling for I2C1 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C1);
	} else if (id == RCC_MOD_I2C2) {
		/* Special handling for I2C2 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C2);
	} else if (id == RCC_MOD_I2C3) {
		/* Special handling for I2C3 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C3);
	} else if (id == RCC_MOD_I2C4) {
		/* Special handling for I2C4 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C4);
	} else if (id == RCC_MOD_I2C5) {
		/* Special handling for I2C5 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C5);
	} else if (id == RCC_MOD_I2C6) {
		/* Special handling for I2C6 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C6);
	} else if (id == RCC_MOD_I2C7) {
		/* Special handling for I2C7 if needed */
		HAL_RCC_EnableModule(RCC_MOD_I2C7);
	} else if (id == RCC_CLK_GPIO1) {
		HAL_RCC_EnableModule(RCC_CLK_GPIO1);
	}

	return 0;
}

static int sf32lb_clock_control_off(const struct device *dev,
				  clock_control_subsys_t sys)
{
	UNUSED(dev);
	RCC_MODULE_TYPE id = (uintptr_t)sys;

	HAL_RCC_DisableModule(id);

	return 0;
}

static int sf32lb_clock_control_get_rate(const struct device *dev,
					clock_control_subsys_t subsys,
					uint32_t *rate)
{
	RCC_MODULE_TYPE module = (RCC_MODULE_TYPE)subsys;

	*rate = 0;//HAL_RCC_GetModuleFreq(module);

	return 0;
}

static const struct clock_control_driver_api sf32lb_clock_api = {
	.on = sf32lb_clock_control_on,
	.off = sf32lb_clock_control_off,
	.get_rate = sf32lb_clock_control_get_rate,
};

static int sf32lb_clock_init(const struct device *dev)
{
	UNUSED(dev);

	if (IS_ENABLED(SF32LB_HXT48M_ENABLED)) {
		HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_SYS, RCC_SYSCLK_HXT48);
		HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_HP_PERI, RCC_CLK_PERI_HXT48);
		HAL_RCC_HCPU_EnableDLL1(240000000);
		HAL_RCC_HCPU_ClockSelect(RCC_CLK_MOD_SYS, RCC_SYSCLK_DLL1);
	}

	if (IS_ENABLED(SF32_SYS_CLOCK_ENABLED)) {
		HAL_RCC_HCPU_SetDiv(SF32_SCLK_HDIV, SF32_SCLK_PDIV1, SF32_SCLK_PDIV2);
	}

	if (IS_ENABLED(SF32LB_LXT32K_ENABLED)) {
	}

	LOG_INF("SF32LB clock initialized");
	LOG_INF("SYSCLK clock: %d Hz", HAL_RCC_GetSysCLKFreq(CORE_ID_HCPU));
	LOG_INF("HCLK clock: %d Hz", HAL_RCC_GetHCLKFreq(CORE_ID_HCPU));
	LOG_INF("PCLK1 clock: %d Hz", HAL_RCC_GetPCLKFreq(CORE_ID_HCPU, 1));
	LOG_INF("PCLK2 clock: %d Hz", HAL_RCC_GetPCLKFreq(CORE_ID_HCPU, 0));

	return 0;
}

#define SF32LB_CLOCK_INIT(n)                                                   \
	static const struct sf32lb_clock_config sf32lb_clock_config_##n = {    \
		.base = DT_INST_REG_ADDR(n),                                   \
	};                                                                     \
	static struct sf32lb_clock_data sf32lb_clock_data_##n;                 \
	DEVICE_DT_INST_DEFINE(n,                                               \
			     sf32lb_clock_init,                                \
			     NULL,                                             \
			     &sf32lb_clock_data_##n,                           \
			     &sf32lb_clock_config_##n,                         \
			     PRE_KERNEL_1,                                     \
			     CONFIG_CLOCK_CONTROL_INIT_PRIORITY,               \
			     &sf32lb_clock_api);

DT_INST_FOREACH_STATUS_OKAY(SF32LB_CLOCK_INIT)