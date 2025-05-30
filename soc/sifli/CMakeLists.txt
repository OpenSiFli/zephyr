# Copyright (c) 2024 SiFli
# SPDX-License-Identifier: Apache-2.0
zephyr_compile_definitions(
  -DSOC_BF0_HCPU
  -DHAL_TICK_PER_SECOND=1000
  -D__HAL_ROM_USED=  
  -DUSE_HAL_DRIVER  
)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/drivers/include)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/drivers/cmsis/include)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SifliSDK/customer/boards/include)

add_subdirectory(${SOC_SERIES})

