# Copyright (c) 2025, Qingsong Gou <gouqs@hotmail.com>
# SPDX-License-Identifier: Apache-2.0

zephyr_library_amend()

zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_SF32LB clock_sf32lb.c)
