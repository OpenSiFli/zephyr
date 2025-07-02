## Setup Zephyr Env

```
pip install west

west init -m https://github.com/OpenSiFli/zephyr.git zephyr_sifli

cd zephyr_sifli

west update
west zephyr-export
west packages pip --install
west sdk install -t arm-zephyr-eabi
 ```
see more via https://docs.zephyrproject.org/latest/develop/getting_started/index.html

## Build with west
```
cd zephyr # make sure in this directory

west build -b <board> <project>
```
eg
```
west build -p auto -b em-lb525 samples/hello_world
```

## Flash
```
west flash or

west flash --port <your serial port> # COM3 in windows for example
```

## Note:
- Currently board only support em-lb525
