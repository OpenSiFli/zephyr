# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../SifliSDK/customer/boards/include/)
file(GLOB SF32LB56X_SOURCES "../../../SifliSDK/customer/boards/eh-lb56xu/*.c")
foreach(FILE ${SF32LB56X_SOURCES})
    zephyr_library_sources(${FILE})
endforeach()
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../SifliSDK/customer/boards/include/config/sf32lb56x)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../SifliSDK/customer/boards/eh-lb56xu)

file(GLOB SF32LB_SOURCES "../../../SifliSDK/customer/boards/common/*.c")
foreach(FILE ${SF32LB_SOURCES})
    zephyr_sources(${FILE})
endforeach()


zephyr_code_relocate(FILES ../../../SifliSDK/customer/boards/eh-lb56xu/bsp_init.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES ../../../SifliSDK/customer/boards/eh-lb56xu/bsp_lcd_tp.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES ../../../SifliSDK/customer/boards/eh-lb56xu/bsp_pinmux.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES ../../../SifliSDK/customer/boards/eh-lb56xu/bsp_power.c LOCATION RAM NOKEEP)
zephyr_code_relocate(FILES ../../../SifliSDK/customer/boards/eh-lb56xu/bsp_power.c LOCATION RAM NOKEEP)