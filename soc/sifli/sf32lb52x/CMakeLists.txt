# SPDX-License-Identifier: Apache-2.0

zephyr_compile_definitions(
  -DSF32LB52X
  -DSOC_SF32LB52X
  -DNONE_HAL_TICK_INIT
)

zephyr_sources(
  soc.c
  )

zephyr_sources(
  lcpu.c
  )

zephyr_sources_ifdef(CONFIG_PM
  power.c
  )

zephyr_sources_ifdef(CONFIG_POWEROFF poweroff.c)

zephyr_include_directories(.)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../SifliSDK/drivers/cmsis/sf32lb52x)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/arm/cortex_m/scripts/linker.ld CACHE INTERNAL "")
