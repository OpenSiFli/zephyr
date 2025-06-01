#
# SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
#
# SPDX-License-Identifier: Apache-2.0


zephyr_library_amend()

zephyr_library_sources_ifdef(CONFIG_CLOCK_CONTROL_SF32LB clock_control_sf32lb.c)
