# Copyright (c) 2017 Linaro Limited.
#
# SPDX-License-Identifier: Apache-2.0

'''Runner for debugging with J-Link.'''

import argparse
import glob
import ipaddress
import logging
import os
import shlex
import socket
import subprocess
import sys
import tempfile
import time
from pathlib import Path

from runners.core import FileType, RunnerCaps, ZephyrBinaryRunner

try:
    import pylink
    from pylink.library import Library
    MISSING_REQUIREMENTS = False
except ImportError:
    MISSING_REQUIREMENTS = True

if sys.platform == 'win32':
    DEFAULT_UARTDL_EXE = "../../SifliSDK/tools/uart_download/ImgDownUart.exe"
else:
    DEFAULT_UARTDL_EXE = "ImgDownUart"

class ToggleAction(argparse.Action):

    def __call__(self, parser, args, ignored, option):
        setattr(args, self.dest, not option.startswith('--no-'))

class sfrunner(ZephyrBinaryRunner):
    '''Runner front-end for the J-Link GDB server.'''

    def __init__(self, cfg, device, dev_id=None,
                 commander=DEFAULT_UARTDL_EXE,
                 dt_flash=True, erase=True, reset=False,
                 iface='swd', speed='auto', flash_script = None,
                 loader=None
                 ):
        super().__init__(cfg)
        self.file = cfg.file
        self.file_type = cfg.file_type
        self.hex_name = cfg.hex_file
        self.bin_name = cfg.bin_file
        self.elf_name = cfg.elf_file
        self.gdb_cmd = [cfg.gdb] if cfg.gdb else None
        self.device = device
        self.dev_id = dev_id
        self.commander = commander
        self.flash_script = flash_script
        self.dt_flash = dt_flash
        self.erase = erase
        self.reset = reset
        self.iface = iface
        self.speed = speed
        self.loader = loader

        self.tool_opt = []
        if tool_opt is not None:
            for opts in [shlex.split(opt) for opt in tool_opt]:
                self.tool_opt += opts

    @classmethod
    def name(cls):
        return 'ImgDownUart'

    @classmethod
    def capabilities(cls):
        return RunnerCaps(commands={'flash'},
                          dev_id=True, flash_addr=True, erase=True, reset=True,
                          tool_opt=True, file=True)

    @classmethod
    def dev_id_help(cls) -> str:
        return '''Device identifier. Use it to select the ImgDownUart device
                  .'''

    @classmethod
    def tool_opt_help(cls) -> str:
        return "Additional options for ImgDownUart"

    @classmethod
    def do_add_parser(cls, parser):
        # Required:
        parser.add_argument('--device', required=True, help='device name')

        # Optional:
        parser.add_argument('--speed', default='auto',
                            help='interface speed, default is autodetect')
        parser.add_argument('--commander', default=DEFAULT_UARTDL_EXE,
                            help=f'''J-Link Commander, default is
                            {DEFAULT_UARTDL_EXE}''')
        parser.add_argument('--reset-after-load', '--no-reset-after-load',
                            dest='reset', nargs=0,
                            action=ToggleAction,
                            help='obsolete synonym for --reset/--no-reset')
        parser.set_defaults(reset=False)

    @classmethod
    def do_create(cls, cfg, args):
        return sfrunner(cfg, args.device,
                                 dev_id=args.dev_id,
                                 commander=args.commander,
                                 dt_flash=args.dt_flash,
                                 erase=args.erase,
                                 reset=args.reset,
                                 iface=args.iface, speed=args.speed,
                                 flash_script=args.flash_script,
                                 gdbserver=args.gdbserver,
                                 loader=args.loader,
                                 gdb_host=args.gdb_host,
                                 gdb_port=args.gdb_port,
                                 rtt_port=args.rtt_port,
                                 tui=args.tui, tool_opt=args.tool_opt)

    def do_run(self, command, **kwargs):

        if MISSING_REQUIREMENTS:
            raise RuntimeError('one or more Python dependencies were missing; '
                               "see the getting started guide for details on "
                               "how to fix")
        # Convert commander to a real absolute path. We need this to
        # be able to find the shared library that tells us what
        # version of the tools we're using.
        self.commander = os.fspath(
            Path(self.require(self.commander)).resolve())
            
        if command == 'flash':
            self.flash(**kwargs)

    def get_default_flash_commands(self):
        lines = [
            'ExitOnError 1',  # Treat any command-error as fatal
            'r',  # Reset and halt the target
            'BE' if self.build_conf.getboolean('CONFIG_BIG_ENDIAN') else 'LE'
        ]

        if self.erase:
            lines.append('erase') # Erase all flash sectors

        # Get the build artifact to flash
        if self.file is not None:
            # use file provided by the user
            if not os.path.isfile(self.file):
                err = 'Cannot flash; file ({}) not found'
                raise ValueError(err.format(self.file))

            flash_file = self.file

            if self.file_type == FileType.HEX:
                flash_cmd = f'loadfile "{self.file}"'
            elif self.file_type == FileType.BIN:
                if self.dt_flash:
                    flash_addr = self.flash_address_from_build_conf(self.build_conf)
                else:
                    flash_addr = 0
                flash_cmd = f'loadfile "{self.file}" 0x{flash_addr:x}'
            else:
                err = 'Cannot flash; SF runner only supports hex and bin files'
                raise ValueError(err)

        else:
            # Use hex, bin or elf file provided by the buildsystem.
            # Preferring .hex over .bin and .elf
            if self.hex_name is not None and os.path.isfile(self.hex_name):
                flash_file = self.hex_name
                flash_cmd = f'loadfile "{self.hex_name}"'
            # Preferring .bin over .elf
            elif self.bin_name is not None and os.path.isfile(self.bin_name):
                if self.dt_flash:
                    flash_addr = self.flash_address_from_build_conf(self.build_conf)
                else:
                    flash_addr = 0
                flash_file = self.bin_name
                flash_cmd = f'loadfile "{self.bin_name}" 0x{flash_addr:x}'
            elif self.elf_name is not None and os.path.isfile(self.elf_name):
                flash_file = self.elf_name
                flash_cmd = f'loadfile "{self.elf_name}"'
            else:
                err = 'Cannot flash; no hex ({}), bin ({}) or elf ({}) files found.'
                raise ValueError(err.format(self.hex_name, self.bin_name, self.elf_name))

        # Flash the selected build artifact
        lines.append(flash_cmd)

        if self.reset:
            lines.append('r') # Reset and halt the target

        lines.append('g') # Start the CPU

        # Reset the Debug Port CTRL/STAT register
        # Under normal operation this is done automatically, but if other
        # SF tools are running, it is not performed.
        # The J-Link scripting layer chains commands, meaning that writes are
        # not actually performed until after the next operation. After writing
        # the register, read it back to perform this flushing.
        lines.append('writeDP 1 0')
        lines.append('readDP 1')

        lines.append('q') # Close the connection and quit

        self.logger.debug('SF commander script:\n' +
                          '\n'.join(lines))
        return flash_file, lines

    def run_flash_cmd(self, fname, flash_file, **kwargs):
        loader_details = ""
        if self.supports_loader and self.loader:
            loader_details = "?" + self.loader

        cmd = (
            [self.commander]
            + (
                ['-IP', f'{self.dev_id}']
                if (is_ip(self.dev_id) or is_tunnel(self.dev_id))
                else (['-USB', f'{self.dev_id}'] if self.dev_id else [])
            )
            + (['-nogui', '1'] if self.supports_nogui else [])
            + ['-if', self.iface]
            + ['-speed', self.speed]
            + ['-device', self.device + loader_details]
            + ['-CommanderScript', fname]
            + (['-nogui', '1'] if self.supports_nogui else [])
            + self.tool_opt
        )

        if flash_file:
            self.logger.info(f'Flashing file: {flash_file}')
        kwargs = {}
        if not self.logger.isEnabledFor(logging.DEBUG):
            kwargs['stdout'] = subprocess.DEVNULL
        self.check_call(cmd, **kwargs)

    def flash(self, **kwargs):
        fname = self.flash_script
        print("flash " + fname)
        if fname is None:
            # Don't use NamedTemporaryFile: the resulting file can't be
            # opened again on Windows.
            with tempfile.TemporaryDirectory(suffix='jlink') as d:
                flash_file, lines = self.get_default_flash_commands()
                fname = os.path.join(d, 'runner.jlink')
                with open(fname, 'wb') as f:
                    f.writelines(bytes(line + '\n', 'utf-8') for line in lines)

                self.run_flash_cmd(fname, flash_file, **kwargs)
        else:
            self.run_flash_cmd(fname, None, **kwargs)
