/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 * Copyright (c) 2024 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/poweroff.h>
#include <zephyr/toolchain.h>
#include <zephyr/bf0_hal.h>

void z_sys_poweroff(void)
{
    // TODO
	k_cpu_idle();
	CODE_UNREACHABLE;
}
