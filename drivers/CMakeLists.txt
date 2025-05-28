# Copyright (c) 2024 SiFli
# Copyright (c) 2025, Qingsong Gou <gouqs@hotmail.com>
# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_FLASH flash)
add_subdirectory_ifdef(CONFIG_GPIO gpio)
# add_subdirectory_ifdef(CONFIG_BT bluetooth)
add_subdirectory_ifdef(CONFIG_SERIAL serial)