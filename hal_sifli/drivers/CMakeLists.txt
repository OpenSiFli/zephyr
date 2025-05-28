#
# Copyright (c) 2025, Qingsong Gou <gouqs@hotmail.com>
#
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(Include) # dir name with lower case to get good score in zephyr github CI
zephyr_include_directories(cmsis/Include)

zephyr_include_directories(cmsis/sf32lb52x)
zephyr_include_directories_ifdef(CONFIG_SOC_SERIES_SF32LB52X cmsis/sf32lb52x)

zephyr_compile_definitions_ifdef(CONFIG_PINCTRL_SF32LB HAL_PINMUX_MODULE_ENABLED)

zephyr_library()

zephyr_library_sources(hal/bf0_hal.c)
zephyr_library_sources(hal/bf0_hal_cortex.c)
zephyr_library_sources(hal/bf0_hal_efuse.c)
zephyr_library_sources(hal/bf0_hal_pmu.c)
zephyr_library_sources(hal/bf0_hal_rcc.c)
#zephyr_library_sources(cmsis/sf32lb52x/Templates/system_bf0_ap.c)

zephyr_library_sources_ifdef(CONFIG_GPIO_SF32LB hal/bf0_hal_gpio.c)
zephyr_library_sources_ifdef(CONFIG_UART_SF32LB hal/bf0_hal_uart.c)
zephyr_library_sources_ifdef(CONFIG_I2C_SF32LB hal/bf0_hal_i2c.c)
zephyr_library_sources_ifdef(CONFIG_PINCTRL_SF32LB hal/bf0_hal_pinmux.c)

# Add HAL source code
file(GLOB SF32LB_SOURCES "hal/*.c")
foreach(FILE ${SF32LB_SOURCES})
    string(FIND "${FILE}" "bf0_hal_audcodec_m.c" POSITION)
    if(POSITION GREATER -1 AND CONFIG_SOC_SERIES_SF32LB56X)
        message("Remove ${FILE} from compiling.")
    else()
        string(FIND "${FILE}" "bf0_hal_audcodec.c" POSITION)
        if(POSITION GREATER -1 AND CONFIG_SOC_SERIES_SF32LB52X)
            message("Remove ${FILE} from compiling.")
        else()
            zephyr_library_sources(${FILE})
        endif()
    endif()
endforeach()

# Relocate HAL source code to RAM
zephyr_code_relocate(FILES hal/bf0_hal_mpi.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_mpi_ex.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_mpi_psram.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_mpi_psram.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_rcc.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_hpaon.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_pinmux.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_gpio.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/flash_table.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal.c FILTER ".*\\.HAL_Init|.*\\.HAL_PostMspInit|.*\\.HAL_Delay|.*\\.HAL_Delay_us|.*\\.HAL_Delay_us_" LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_hal_pmu.c FILTER ".*\\.HAL_PMU_SET_HXT_CBANK|.*\\.HAL_PMU_GetHpsysVoutRef|.*\\.HAL_PMU_GetHpsysVoutRef2" LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES hal/bf0_sys_cfg.c FILTER ".*\\BSP_HxtCbank_Config" LOCATION RAM NOKEEP)


## Add 56x specific code
#if (CONFIG_SOC_SERIES_SF32LB56X)
#	zephyr_library_sources("../../SifliSDK/drivers/cmsis/sf32lb56x/Templates/system_bf0_ap.c")
#	zephyr_library_sources("../../SifliSDK/drivers/cmsis/sf32lb56x/bt_rf_fulcal.c")
#	zephyr_library_sources("../../SifliSDK/drivers/cmsis/sf32lb56x/bf0_pin_const.c")
#	zephyr_library_sources("../../SifliSDK/drivers/cmsis/sf32lb56x/bf0_lcpu_init.c")
#    zephyr_code_relocate(FILES ../../SifliSDK/drivers/cmsis/sf32lb56x/bf0_pin_const.c LOCATION RAM NOKEEP)
#endif()

# Add 52x specific code
if (CONFIG_SOC_SERIES_SF32LB52X)
	zephyr_library_sources(cmsis/sf32lb52x/Templates/system_bf0_ap.c)
	zephyr_library_sources(cmsis/sf32lb52x/bt_rf_fulcal.c)
	zephyr_library_sources(cmsis/sf32lb52x/bf0_pin_const.c)
	zephyr_library_sources(cmsis/sf32lb52x/bf0_lcpu_init.c)
	zephyr_library_sources(cmsis/sf32lb52x/lcpu_patch.c)
	zephyr_library_sources(cmsis/sf32lb52x/lcpu_patch_rev_b.c)
    zephyr_code_relocate(FILES cmsis/sf32lb52x/bf0_pin_const.c LOCATION RAM NOKEEP)
endif()

## Add Bluetooth HCI
#if (CONFIG_BT)
#	file(GLOB SF32LB_IPC "../../SifliSDK/middleware/ipc_queue/common/*.c")
#	foreach(FILE ${SF32LB_IPC})
#        zephyr_library_sources(${FILE})
#	endforeach()
#	zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/middleware/include)
#	zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/middleware/ipc_queue/common)
#	if (CONFIG_SOC_SERIES_SF32LB52X)
#		file(GLOB SF32LB_IPC_PORT "../../SifliSDK/middleware/ipc_queue/porting/sf32lb52x/hcpu/*.c")
#		zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/middleware/ipc_queue/porting/sf32lb52x/hcpu)
#	endif()
#	if (CONFIG_SOC_SERIES_SF32LB56X)
#		file(GLOB SF32LB_IPC_PORT "../../SifliSDK/middleware/ipc_queue/porting/sf32lb56x/hcpu/*.c")
#		zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/middleware/ipc_queue/porting/sf32lb56x/hcpu)
#	endif()
#	foreach(FILE ${SF32LB_IPC_PORT})
#        zephyr_library_sources(${FILE})
#	endforeach()
#endif()
