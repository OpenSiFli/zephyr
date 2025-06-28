# SPDX-License-Identifier: Apache-2.0

# keep first
board_runner_args(sfrunner "--device=SF32LB52X" "--speed=4000")
board_runner_args(sftool "--chip=SF32LB52" "--port=COM5")

# keep first
board_set_flasher_ifnset(sftool)
board_finalize_runner_args(sftool)
board_set_flasher_ifnset(sfrunner)
board_finalize_runner_args(sfrunner)
