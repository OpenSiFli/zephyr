/*
 * Copyright (c) 2025 Sifli Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/pm/pm.h>
#include <soc.h>
#include <zephyr/init.h>
#include <bf0_hal.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(soc, CONFIG_SOC_LOG_LEVEL);

void set_mode_stop(uint8_t substate_id)
{
	switch (substate_id) {
	case 1: /* this corresponds to the STOP0 mode: */
		break;
	case 2: /* this corresponds to the STOP1 mode: */
		break;
	case 3: /* this corresponds to the STOP2 mode: */
		break;
	default:
		LOG_DBG("Unsupported power state substate-id %u", substate_id);
		break;
	}
}

/* Invoke Low Power/System Off specific Tasks */
void pm_state_set(enum pm_state state, uint8_t substate_id)
{
	switch (state) {
	case PM_STATE_SUSPEND_TO_IDLE:
		break;
	case PM_STATE_STANDBY:
		break;
	default:
		LOG_DBG("Unsupported power state %u", state);
		return;
	}

}

/* Handle SOC specific activity after Low Power Mode Exit */
void pm_state_exit_post_ops(enum pm_state state, uint8_t substate_id)
{
	switch (state) {
	case PM_STATE_SUSPEND_TO_IDLE:
		break;
	case PM_STATE_STANDBY:
		__fallthrough;
	case PM_STATE_SUSPEND_TO_RAM:
		__fallthrough;
	case PM_STATE_SUSPEND_TO_DISK:
		__fallthrough;
	default:
		LOG_DBG("Unsupported power state %u", state);
		break;
	}

}

/* Initialize SF32LB52X Power */
void sf32lb52x_power_init(void)
{

}
