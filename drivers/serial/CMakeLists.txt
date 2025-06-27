# SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
# SPDX-License-Identifier: Apache-2

zephyr_library_amend()

zephyr_library_sources_ifdef(CONFIG_UART_SF32LB uart_sf32lb.c)