# SPDX-License-Identifier: Apache-2.0

# keep first
board_runner_args(jlink "--device=SF32LB56X_NAND" "--speed=4000")

# keep first
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
