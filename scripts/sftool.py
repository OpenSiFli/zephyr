from runners.core import FileType, BuildConfiguration, RunnerCaps, ZephyrBinaryRunner

class SfToolBinaryRunner(ZephyrBinaryRunner):
    '''Runner front-end for the sftool.'''

    def __init__(self, cfg, chip, port, flash_addr, memory='nor', baud='1000000'):
        super().__init__(cfg)
        self.chip = chip
        self.port = port
        self.flash_addr = flash_addr
        self.memory = memory
        self.baud = baud

    @classmethod
    def name(cls):
        return 'sftool'

    @classmethod
    def capabilities(cls):
        return RunnerCaps(commands={'flash'}, flash_addr=True)

    @classmethod
    def dev_id_help(cls) -> str:
        return '''Device identifier. Use it to select the ImgDownUart device.'''

    @classmethod
    def tool_opt_help(cls) -> str:
        return "Additional options for sftool"

    @classmethod
    def do_add_parser(cls, parser):
        # Required:
        parser.add_argument('--chip', required=True, help='target chip type')
        parser.add_argument('--port', required=True, help='Serial port device')
        # Optional:
        parser.add_argument('-m', '--memory', default='nor', help='memory type, default is nor.')
        parser.add_argument('-b', '--baud', default='1000000', help='serial port buad rate, default is 1000000')
        parser.add_argument('--before', default='default_reset', help='interface speed, default is autodetect')
        parser.add_argument('--after', default='soft_reset', help='default is soft_reset')
        parser.add_argument('--connect-attempts', default=3, type=int, help='number of connection attempts, default is 3')

    @classmethod
    def do_create(cls, cfg, args):
        args.dt_flash = True
        build_conf = BuildConfiguration(cfg.build_dir)
        flash_addr = hex(cls.get_flash_address(args, build_conf))
        return SfToolBinaryRunner(cfg, args.chip, args.port, flash_addr,
                      memory=getattr(args, 'memory', 'nor'),
                      baud=getattr(args, 'baud', '1000000'))

    def do_run(self, command: str, **kwargs):
        self.require('sftool')

        if command == "flash":
            self.flash(**kwargs)
        else:
            raise ValueError(f"Unknown command: {command}")

    def run_flash_cmd(self, firmware_file, address, **kwargs):
        # Compose the sftool command
        cmd = [
            'sftool',
            '--chip', self.chip,
            '--port', self.port,
            'write_flash',
            f'{firmware_file}@{address}'
        ]

        self.logger.info(f'Flashing with command: {cmd}')
        self.check_call(cmd)

    def flash(self, **kwargs):
        # Ensure we have a binary to flash
        self.ensure_output('bin')
        firmware_file = self.cfg.bin_file
        self.run_flash_cmd(firmware_file, self.flash_addr, **kwargs)
