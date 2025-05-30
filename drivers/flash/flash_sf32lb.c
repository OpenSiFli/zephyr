/*
 * Copyright (c) 2022 BrainCo Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sifli_sf32lb_flash_controller

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>
#include "drv_io.h"

#define SOC_NV_FLASH_NODE	DT_INST(0, soc_nv_flash)
#define SOC_NV_FLASH_SIZE	DT_REG_SIZE(SOC_NV_FLASH_NODE)
#define SOC_NV_FLASH_ADDR	DT_REG_ADDR(SOC_NV_FLASH_NODE)
#define SOC_NV_FLASH_PRG_SIZE	DT_PROP(SOC_NV_FLASH_NODE, write_block_size)
#define SOC_NV_FLASH_ERASE_SIZE	DT_PROP(SOC_NV_FLASH_NODE, erase_block_size)


LOG_MODULE_REGISTER(flash_sf32lb, CONFIG_FLASH_LOG_LEVEL);

struct flash_sf32lb_data {
	struct k_sem mutex;
};

static struct flash_sf32lb_data flash_data;

static const struct flash_parameters flash_sf32lb_parameters = {
	.write_block_size = SOC_NV_FLASH_PRG_SIZE,
	.erase_value = 0xff,
};

#ifdef CONFIG_FLASH_PAGE_LAYOUT
static const struct flash_pages_layout sf32lb_layout[] = {
	{
	.pages_size = SOC_NV_FLASH_ERASE_SIZE,
	.pages_count = SOC_NV_FLASH_SIZE / SOC_NV_FLASH_ERASE_SIZE
	}
};

void flash_sf32lb_pages_layout(const struct device *dev,
			     const struct flash_pages_layout **layout,
			     size_t *layout_size)
{
	ARG_UNUSED(dev);

	*layout = sf32lb_layout;
	*layout_size = ARRAY_SIZE(sf32lb_layout);
}
#endif /* CONFIG_FLASH_PAGE_LAYOUT */


static int flash_sf32lb_read(const struct device *dev, off_t offset,
			   void *data, size_t len)
{
	if ((offset > SOC_NV_FLASH_SIZE) ||
	    ((offset + len) > SOC_NV_FLASH_SIZE)) {
		return -EINVAL;
	}

	if (len == 0U) {
		return 0;
	}

	memcpy(data, (uint8_t *)SOC_NV_FLASH_ADDR + offset, len);

	return 0;
}

static int flash_sf32lb_write(const struct device *dev, off_t offset,
			    const void *data, size_t len)
{
	struct flash_sf32lb_data *dev_data = dev->data;
    FLASH_HandleTypeDef * hflash=(FLASH_HandleTypeDef *)BSP_Flash_get_handle(SOC_NV_FLASH_ADDR);
	int ret = 0;


	if (len == 0U) {
		return 0;
	}

	k_sem_take(&dev_data->mutex, K_FOREVER);

	ret = HAL_QSPIEX_WRITE_PAGE(hflash, offset, data, len);

	k_sem_give(&dev_data->mutex);

	return ret;
}

static int flash_sf32lb_erase(const struct device *dev, off_t offset, size_t size)
{
	struct flash_sf32lb_data *data = dev->data;
    FLASH_HandleTypeDef * hflash=(FLASH_HandleTypeDef *)BSP_Flash_get_handle(SOC_NV_FLASH_ADDR);
	int ret = 0;

	if (size == 0U) {
		return 0;
	}

	k_sem_take(&data->mutex, K_FOREVER);

	ret = HAL_QSPIEX_SECT_ERASE(hflash, offset);

	k_sem_give(&data->mutex);

	return ret;
}

static const struct flash_parameters*
flash_sf32lb_get_parameters(const struct device *dev)
{
	ARG_UNUSED(dev);

	return &flash_sf32lb_parameters;
}

static DEVICE_API(flash, flash_sf32lb_driver_api) = {
	.read = flash_sf32lb_read,
	.write = flash_sf32lb_write,
	.erase = flash_sf32lb_erase,
	.get_parameters = flash_sf32lb_get_parameters,
#ifdef CONFIG_FLASH_PAGE_LAYOUT
	.page_layout = flash_sf32lb_pages_layout,
#endif
};

static int flash_sf32lb_init(const struct device *dev)
{
	struct flash_sf32lb_data *data = dev->data;

    BSP_Flash_Init();
	k_sem_init(&data->mutex, 1, 1);

	return 0;
}

DEVICE_DT_INST_DEFINE(0, flash_sf32lb_init, NULL,
		      &flash_data, NULL, POST_KERNEL,
		      CONFIG_FLASH_INIT_PRIORITY, &flash_sf32lb_driver_api);
