# SPDX-FileCopyrightText: 2025 SiFli Technologies(Nanjing) Co., Ltd
# SPDX-License-Identifier: Apache-2.0

zephyr_library_amend()

zephyr_library_sources_ifdef(CONFIG_I2C_SF32LB i2c_sf32lb.c)
