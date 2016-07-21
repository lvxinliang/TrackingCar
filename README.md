# TrackingCar

1. 使用三轮差数转向
2. 通过电子罗盘控制旋转角度
3. 通过超声波测距区分桥和墙
3. 使用多通道灰度传感器进行寻线

## 材料准备
1. Arduino Uno
2. Arduino Motor Shield
3. SEN2020 8通道选线模块
4. 4轮小车底盘

## 注意事项
1. 电池选择, 选择续航好的航模电池
2. 小车后轮驱动，这样可以预留出小车的转弯半径

## 参考场地
![image](https://github.com/lvxinliang/TrackingCar/blob/master/doc/area.png?raw=true)

## 连线参考
巡线传感器
```
int Sensor1 = 2;
int Sensor2 = 4;
int Sensor3 = 5;
int Sensor4 = 6;
int Sensor5 = 7;
int Sensor6 = 16;
int Sensor7 = 17;
int Sensor8 = 18;
```


