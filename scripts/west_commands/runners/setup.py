# Copyright (c) 2025 Qingsong Gou <gouqs@foxmail.com>
#
# SPDX-License-Identifier: Apache-2.0

from setuptools import setup

setup(
    name='sf32lb-runner',
    version='0.1.0',
    description='Runner for SF32LB platform',
    author='Qingsong Gou',
    author_email='gouqs@foxmail.com',
    packages=['runners'],
    entry_points={
        'zephyr_runner': [
            'sf32lb = runners.sf32lb:Sf32lbBinaryRunner',
        ],
    },
)