# Copyright (c) 2024 SiFli
# SPDX-License-Identifier: Apache-2.0
zephyr_compile_definitions(
  -DSOC_BF0_HCPU
  -DHAL_TICK_PER_SECOND=1000
  -D__HAL_ROM_USED=
  -DUSE_HAL_DRIVER
)

add_subdirectory(${SOC_SERIES})
