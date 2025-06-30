## Setup Zephyr Env
follow the https://docs.zephyrproject.org/latest/develop/getting_started/index.html

## Create repo:
- Clone this project to <zephyrproject>\modules\hal\sifli, Directory contains all the driver and devicetree provided by SiFli
- Manually add the sifli module to west.yml
```
index cb31d1022a4..79f156f906d 100644
@@ -229,6 +229,11 @@ manifest:
       revision: 7b57b24588797e6e7bf18b6bda168e6b96374264
       groups:
         - hal
+    - name: hal_sifli
+      path: modules/hal/sifli
+      revision: main
+      groups:
+        - hal
     - name: hal_silabs
       revision: 389726f350880238b9a1034f575ffd46c4309827
       path: modules/hal/silabs
```

## Build with west
```
west build -b <board> <project>
```

Validated project including:
- zephyr\samples\hello_world

## Flash
```
west flash
```

## Note:
- Currently board support em-lb525
