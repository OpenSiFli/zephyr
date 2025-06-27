/*
 * Copyright (c) 2025 Qingsong Gou <gouqs@hotmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#define DT_DRV_COMPAT sifli_sf32lb_rng

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/entropy.h>
#include <zephyr/logging/log.h>
#include <zephyr/irq.h>
#include <zephyr/sys/util.h>

#include "bf0_hal.h"
#include "bf0_hal_rng.h"

LOG_MODULE_REGISTER(entropy_sf32lb, CONFIG_ENTROPY_LOG_LEVEL);

/* Entropy configuration structure */
struct entropy_sf32lb_config {
	TRNG_TypeDef *base;
	uint32_t irq_num;
	void (*irq_config_func)(void);
};

/* Entropy data structure */
struct entropy_sf32lb_data {
	RNG_HandleTypeDef handle;
	uint32_t state;
	uint32_t error;
	uint8_t initialized;
};

/* Entropy API implementation */
static int entropy_sf32lb_init(const struct device *dev)
{
	const struct entropy_sf32lb_config *config = dev->config;
	struct entropy_sf32lb_data *data = dev->data;
	int ret = 0;

	/* Initialize RNG peripheral */
	data->handle.Instance = config->base;
	if (HAL_RNG_Init(&data->handle) != HAL_OK) {
		LOG_ERR("Failed to initialize RNG");
		return -EIO;
	}

	/* Configure interrupt */
	config->irq_config_func();

	/* Generate initial seed */
	if (HAL_RNG_Generate(&data->handle, NULL, 1) != HAL_OK) {
		LOG_ERR("Failed to generate initial seed");
		return -EIO;
	}

	data->initialized = 1;
	return ret;
}

static int entropy_sf32lb_get_entropy(const struct device *dev, uint8_t *buffer, uint16_t length)
{
	struct entropy_sf32lb_data *data = dev->data;
	uint32_t random;
	int ret = 0;

	if (!data->initialized) {
		return -ENODEV;
	}

	/* Generate random data */
	for (int i = 0; i < length; i += 4) {
		if (HAL_RNG_Generate(&data->handle, &random, 0) != HAL_OK) {
			LOG_ERR("Failed to generate random data");
			return -EIO;
		}

		/* Copy random data to buffer */
		if (i + 4 <= length) {
			memcpy(buffer + i, &random, 4);
		} else {
			memcpy(buffer + i, &random, length - i);
		}
	}

	return ret;
}

static int entropy_sf32lb_get_entropy_isr(const struct device *dev, uint8_t *buffer,
					  uint16_t length, uint32_t flags)
{
	/* Use the same implementation as get_entropy */
	return entropy_sf32lb_get_entropy(dev, buffer, length);
}

static void entropy_sf32lb_isr(const struct device *dev)
{
	struct entropy_sf32lb_data *data = dev->data;

	HAL_RNG_IRQHandler(&data->handle);
}

static const struct entropy_driver_api entropy_sf32lb_api = {
	.get_entropy = entropy_sf32lb_get_entropy,
	.get_entropy_isr = entropy_sf32lb_get_entropy_isr,
};

/* Device instantiation */
#define ENTROPY_SF32LB_INIT(n)                                                                     \
	static void entropy_sf32lb_irq_config_##n(void);                                           \
                                                                                                   \
	static const struct entropy_sf32lb_config entropy_sf32lb_config_##n = {                    \
		.base = (TRNG_TypeDef *)DT_INST_REG_ADDR(n),                                       \
		.irq_num = DT_INST_IRQN(n),                                                        \
		.irq_config_func = entropy_sf32lb_irq_config_##n,                                  \
	};                                                                                         \
                                                                                                   \
	static struct entropy_sf32lb_data entropy_sf32lb_data_##n;                                 \
                                                                                                   \
	DEVICE_DT_INST_DEFINE(n, entropy_sf32lb_init, NULL, &entropy_sf32lb_data_##n,              \
			      &entropy_sf32lb_config_##n, PRE_KERNEL_1,                            \
			      CONFIG_ENTROPY_INIT_PRIORITY, &entropy_sf32lb_api);                  \
                                                                                                   \
	static void entropy_sf32lb_irq_config_##n(void)                                            \
	{                                                                                          \
		IRQ_CONNECT(DT_INST_IRQN(n), DT_INST_IRQ(n, priority), entropy_sf32lb_isr,         \
			    DEVICE_DT_INST_GET(n), 0);                                             \
		irq_enable(DT_INST_IRQN(n));                                                       \
	}

DT_INST_FOREACH_STATUS_OKAY(ENTROPY_SF32LB_INIT)
