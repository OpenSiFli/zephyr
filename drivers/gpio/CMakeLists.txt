#
# SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
#
# SPDX-License-Identifier: Apache-2.0


zephyr_library_amend()

zephyr_library_sources_ifdef(CONFIG_GPIO_SF32LB     gpio_sf32lb.c)