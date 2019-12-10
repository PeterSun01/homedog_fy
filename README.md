轩辕科技看家狗网关
使用AIRBOX1硬件
使用esp-aliyun连接飞燕
ESP-IDF = v3.2.2
esp-aliyun=b2b5fb2
版本号：make menuconfig
iotkit setting

量产烧录：四元组
1、修改mfg_config.csv  
2、$IDF_PATH/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py --input mfg_config.csv --output mfg_config.bin --size 0x4000
3、$IDF_PATH/components/esptool_py/esptool/esptool.py write_flash 0x210000 mfg_config.bin

LED状态指示
1、开机初始化、开机有WIFI信息，但是没搜到（绿灯常亮）
2、连接云服务器成功（灭）     user_connected_event_handler.78: Cloud Connected
3、配网开始（红绿交替）       app main: IOTX_AWSS_START
4、密码错误（红灯闪烁）       app main: IOTX_AWSS_CONNECT_ROUTER_FAIL
5、wifi断开（红灯闪烁）      user_disconnected_event_handler.95: Cloud Disconnected
6、发送数据（绿灯快闪）       user_post_property.352: Post Property Message ID: 5
7、无四元组配网（红灯常亮）    app main: IOTX_AWSS_PASSWD_ERR
8、接收数据（绿灯快闪2次）     

