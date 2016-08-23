# TrackingCar

1. 使用差速转向
2. 通过电子罗盘控制旋转角度
3. 通过夏普红外测距测量小车到障碍物的距离
4. 使用多通道灰度传感器进行寻线

## 材料准备
1. Arduino Uno
2. Arduino 引脚扩展板
3. SEN2020 8通道选线模块
4. 4轮小车底盘
5. 电机驱动模块
6. 光耦隔离板
7. 电子罗盘模块
8. 夏普红外测距模块 GP2Y0A41SK0F
9. 4节18620锂电池
10. 若干杜邦线、导线、2个电池盒

## 材料淘宝地址
1. 复制这条信息，打开手机淘宝即可看到【8路光耦隔离板/光耦隔离,光耦隔离模块/3/5/12/24V[正相放大版]】￥AAIeGxmF￥http://e22a.com/h.ZDDfoc?cv=AAIeGxmF&sm=886164
2. 复制这条信息，打开手机淘宝即可看到【智能车 小车8路灰度 巡线 寻线传感器 串口和并行双输出[SEN2020]】￥AAIeHgkT￥http://e22a.com/h.ZDDist?cv=AAIeHgkT&sm=c91c5b
3. 复制这条信息，打开手机淘宝即可看到【智能小车底盘 4驱测速小车 25MM强磁减速电机 大扭矩 竞赛专用】￥AAIeHWwI￥http://e22a.com/h.ZDDQZ3?cv=AAIeHWwI&sm=a8930d
4. 复制这条信息，打开手机淘宝即可看到【Arduino Uno R3 v5扩展板 sensor shield v5.0 电子积木 蓝色版】￥AAIeIHgW￥http://e22a.com/h.ZDDlW5?cv=AAIeIHgW&sm=e9cade
5. 复制这条信息，打开手机淘宝即可看到【GP2Y0A41SK0F 全新原装进口夏普 红外线测距传感器 4-30cm 送线】￥AAIeILUX￥http://e22a.com/h.ZDDNGy?cv=AAIeILUX&sm=eb960e
6. 复制这条信息，打开手机淘宝即可看到【GY-87 10DOF MPU6050 HMC5883L BMP180 传感器模块】￥AAIeIGWO￥http://e22a.com/h.ZDDK2N?cv=AAIeIGWO&sm=c384c5

## 注意事项
1. 灰度传感器需要使用串口配置
2. 小车使用380电机，300RPM，提高370电机提高爬坡能力
3. 电子罗盘安装远离磁场，比如电机

## 参考场地
![image](https://github.com/lvxinliang/TrackingCar/blob/master/doc/area.png?raw=true)
