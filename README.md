# How to
## Create repo:
- Pull zephyr from https://github.com/zephyrproject-rtos/zephyr 
- Clone this project to <zephyrproject>\modules\hal\sifli, Directory contains all the driver and devicetree provided by SiFli
- Add "sifli	SiFli, Inc." in <zephyrproject>\zephyr\dts\bindings\vendor-prefixes.txt

## Build with west 
```
west build -b <board> <project>  -- -DBOARD_ROOT=<zephyrproject>\modules\hal\sifli\zephyr -DSOC_ROOT=<zephyrproject>\modules\hal\sifli\zephyr  -DDTS_ROOT_BINDINGS=<zephyrproject>\modules\hal\sifli\zephyr\dts\bindings
```

Validated project including: 
- zephyr\samples\bluetooth\peripheral
- zephyr\samples\hello_world

## Note: 
- Currently board support em-lb525, 
- Firmware Download tool currently only support Window platform. Use zephyrproject\modules\hal\sifli\zephyr\scripts\sfflash.bat to download firmware to board.
