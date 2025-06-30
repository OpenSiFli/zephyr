## Setup Zephyr Env

```
pip install west

west init -m https://github.com/ck-telecom/zephyr-SiFli.git zephyr_sifli

cd zephyr_sifli

west update
west zephyr-export
west packages pip --install
west sdk install -t arm-zephyr-eabi
 ```
see more via https://docs.zephyrproject.org/latest/develop/getting_started/index.html

## Build with west
```
cd zephyr_sifli # make sure in this directory

west build -b <board> <project>
```

## Flash
```
west flash or

west flash --port <your serial port>
```

## Note:
- Currently board only support em-lb525
