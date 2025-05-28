# SPDX-License-Identifier: Apache-2.0

# keep first
board_runner_args(sfrunner "--device=SF32LB52X" "--speed=4000")

# keep first
board_set_flasher_ifnset(sfrunner)
board_finalize_runner_args(sfrunner)
