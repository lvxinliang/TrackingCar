/***************************************************
 * Title: 障碍赛小车代码
 * Author: lvxinliang
 * Date: 2016-07-11
 **************************************************/

#include <Wire.h>
#include <HMC5883L.h>

/**
 * 电机驱动数字引脚
 * 左边电机
 */
const int E1 = 3;   //PWMA
const int M1 = 12;  //DIRA
const int BRAKEA = 9;   //BRAKEA
/**
 * 电机驱动数字引脚
 * 右边电机
 */
const int E2 = 11;  //PWMB
const int M2 = 13;  //DIRB
const int BRAKEB = 8;   //BRAKEB

const int DELAY_TIME = 250;

/**
 * 小车距离前方20cm进入避障程序
 */
const int MIN_DIST = 10;

/**
 * 巡线模块通道个数
 */
const int SENSOR_CNT= 8;
/**
 * 传感器引脚定义
 */
const int Sensor1 = 2;
const int Sensor2 = 4;
const int Sensor3 = 5;
const int Sensor4 = 6;
const int Sensor5 = 7;
const int Sensor6 = 10;
const int Sensor7 = 16;
const int Sensor8 = 17;

/**
 * 传感器返回的颜色
 */
const int WHITE = 1;
const int BLACK = 0;
 
/**
 * 定义传感器回传得到的数据
 */
int sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8;

/**
 * 传感器的总和, 表示读到白色的条数
 */
int totalVal = 0;
int leftTotalVal = 0;
int rightTotalVal = 0;
/**
 * 测距模块返回值
 */
float volts = 0.3;
float distance = 100;
/**
 * 电子罗盘对象
 */
HMC5883L compass;
/**
 * 固定角度转向最大误差
 */
const int MAX_TURN_ERROR = 5;
    
/**
 * 获取小车距离障碍的距离
 */
int getDist() {
    volts = analogRead(A0)*0.00469727;
//  volts = analogRead(A0)*0.0048828125;
    distance = 6*pow(volts, -1.228);
    return distance;
}

/**
 * setMotor(int MOTORA,int MOTORB)参数说明：
 * MOTORA>0,A电机正转,0<MOTORA<255
 * MOTORA<0,A电机反转
 * MOTORB>0,B电机正转,0<MOTORB<255
 * MOTORB<0,B电机反转
 * 正负表示转向, 数值表示转速
 */
void setMotor(int MOTORA, int MOTORB) {
    if(MOTORA > 0) {
      digitalWrite(BRAKEA, LOW);
      digitalWrite(M1, LOW);     //正转
      analogWrite(E1, MOTORA);
    } else if(MOTORA < 0) {
      digitalWrite(BRAKEA, LOW);
      digitalWrite(M1, HIGH);    //反转
      analogWrite(E1, 0 - MOTORA);
    } else {
      digitalWrite(BRAKEA, HIGH);
      digitalWrite(M1, HIGH);
      analogWrite(E1, LOW);
    }

    if(MOTORB > 0) {
      digitalWrite(BRAKEB, LOW);
      digitalWrite(M2, LOW);     //正转
      analogWrite(E2, MOTORB);
    } else if(MOTORB < 0) {
      digitalWrite(BRAKEB, LOW);
      digitalWrite(M2, HIGH);      //反转
      analogWrite(E2, 0 - MOTORB);
    } else {
      digitalWrite(BRAKEB, HIGH);
      digitalWrite(M2, HIGH);
      analogWrite(E2, LOW);
    }
}

/**
 * 初始化 HMC5883L芯片
 */
void compassSetup() {
    Serial.println("Initialize HMC5883L");
    while (!compass.begin()) {
      Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
      delay(100);
    }
  
    // 设置测量精度
    compass.setRange(HMC5883L_RANGE_1_3GA);
    // 设置测量模式
    compass.setMeasurementMode(HMC5883L_CONTINOUS);
    // 设置速率
    compass.setDataRate(HMC5883L_DATARATE_30HZ);
    // 设置采样率
    compass.setSamples(HMC5883L_SAMPLES_8);
    // 设置测量偏差(参见 HMC5883L_calibration.ino)
    compass.setOffset(0, 0);
}

/**
 * 获取电子罗盘的角度
 * 电子罗盘X轴朝向正北,返回角度为0或360
 */
float getCompassDegress() {
    Vector norm = compass.readNormalize();
  
    // Calculate heading
    float heading = atan2(norm.YAxis, norm.XAxis);
  
    float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
    heading += declinationAngle;
  
    // Correct for heading < 0deg and heading > 360deg
    if (heading < 0) {
      heading += 2 * PI;
    }
  
    if (heading > 2 * PI) {
      heading -= 2 * PI;
    }
  
    // Convert to degrees
    return heading * 180/M_PI;
}

/**
 * 打印电子罗盘角度
 */
void printHeadingDegrees(double headingDegrees) {
    Serial.print(headingDegrees);
    Serial.println();
}

/**
 * 躲避障碍代码
 */
void runAround() {
    Serial.println("runAround.");
    // 向左
    setMotor(-255,255);
    delay(DELAY_TIME);
    // 向前
    setMotor(210,210);
    delay(1000);
    // 向右
    setMotor(255,-255);
    delay(DELAY_TIME);
    // 向前
    setMotor(210,210);
    delay(1000);
    // 向右
    setMotor(255,-255);
    delay(DELAY_TIME);
    // 向前
    setMotor(210,210);
    delay(1000);
    // 向左
    setMotor(-255,255);
    delay(DELAY_TIME);
    // 向前
    setMotor(210,210);
    delay(1000);
}
/**
 * 右转一些
 */
void turnRightLittle() {
    setMotor(210,-210);
    delay(10);
    setMotor(0,0);
}
/**
 * 左转一些
 */
void turnLeftLittle() {
    setMotor(-210,210);
    delay(10);
    setMotor(0,0);
}
/**
 * 顺时针转angle°
 */
void turnClockwise(int angle){
    double val = getCompassDegress();
    double targetVal = val + angle;
    boolean isCarry = false; // 表示经过一圈,经过北极
    if(targetVal > 360) {
      targetVal -= 360;
      isCarry = true;
    }
    double tmp = 0.0;
    while(true) {
      tmp = getCompassDegress();
      if(!isCarry) {
        if(targetVal - tmp > MAX_TURN_ERROR){
          turnRightLittle();
        }else if(tmp - targetVal > MAX_TURN_ERROR) {
          turnLeftLittle();
        }else{
          break;
        }
      }else{
        if(tmp > targetVal && 360 - tmp + targetVal > MAX_TURN_ERROR) {
          turnRightLittle();
        }else if(targetVal > tmp && targetVal - tmp > MAX_TURN_ERROR){
          turnRightLittle();
        }else{
          break;
        }
      }
    }
}
/**
 * 逆时针转angle°
 */
void turnAnticlockwise(int angle) {
    double val = getCompassDegress();
    double targetVal = val - angle;
    boolean isCarry = false; // 表示经过一圈,经过北极
    if(targetVal < 0) {
      targetVal += 360;
      isCarry = true;
    }
    double tmp = 0.0;
    while(true) {
      tmp = getCompassDegress();
      if(!isCarry) {
        if(targetVal - tmp < -MAX_TURN_ERROR){
          // 逆时针转
          turnLeftLittle();
        }else if(targetVal - tmp > MAX_TURN_ERROR) {
          // 顺时针转
          turnRightLittle();
        }else {
          break;
        }
      }else{
        if(targetVal > tmp && 360 - targetVal + tmp > MAX_TURN_ERROR) {
          // 逆时针
          turnLeftLittle();
        }else if(targetVal < tmp &&targetVal - tmp < -MAX_TURN_ERROR){
          // 逆时针
          turnLeftLittle();
        }else{
          break;
        }
      }
    }
}

/**
 * 读取寻线传感器值
 */
void sensorRead() {
    sensor1 = digitalRead(Sensor1);
    sensor2 = digitalRead(Sensor2);
    sensor3 = digitalRead(Sensor3);
    sensor4 = digitalRead(Sensor4);
    sensor5 = digitalRead(Sensor5);
    sensor6 = digitalRead(Sensor6);
    sensor7 = digitalRead(Sensor7);
    sensor8 = digitalRead(Sensor8);
}

/**
 * 打印寻线传感器值
 */
void printSensor() {
    Serial.print("sensor1:");
    Serial.print(sensor1);
    Serial.print(",sensor2:");
    Serial.print(sensor2);
    Serial.print(",sensor3:");
    Serial.print(sensor3);
    Serial.print(",sensor4:");
    Serial.print(sensor4);
    Serial.print(",sensor5:");
    Serial.print(sensor5);
    Serial.print(",sensor6:");
    Serial.print(sensor6);
    Serial.print(",sensor7:");
    Serial.print(sensor7);
    Serial.print(",sensor8:");
    Serial.print(sensor8);
    Serial.println(".");
}

/**
 * 判断是否需要停止
 */
void checkStop() {
    if( SENSOR_CNT - totalVal> 5) {  // 5个以上传感器检测到黑色
        setMotor(0,0);
        while(true);
    }
}

/**
 * 延时并检测是否是停车
 */
void delayAndCheckBack() {
    delayMicroseconds(1);
    sensorRead();
    checkStop();
}

/**
 * 检测是否要倒车
 */
void checkBack() {
    if(SENSOR_CNT ==  totalVal) {  // 5个以上传感器检测到黑色
        setMotor(-200,-200);
        delay(2000);
    }
}

/**
 * 检测左转90°
 */
void checkTurnLeft() {
    // 左侧至少有三个检测到黑线,并且右侧最多有一个检测到黑线
    if( leftTotalVal <=1 && rightTotalVal >=3) {  // 5个以上传感器检测到黑色
        delayAndCheckBack();
        Serial.println("checkTurnLeft");
        setMotor(-200,200);
        delay(600);
        while(true) {
          sensorRead();
          if(sensor2 + sensor3 + sensor4 + sensor5 + sensor6 + sensor7 == 5){
              Serial.println("checkTurnLeft break.");
              break;
          }
          setMotor(-200,200);
          delay(10);
        }
    }
}

/**
 * 检测右转90°
 */
void checkTurnRight() {
    // 检测右边至少有三个sersor检测到黑线,并且左边最多有一个检测到黑线
    if( rightTotalVal <=1 && leftTotalVal >=3) {
        // 延时并检测是否是停车
        delayAndCheckBack();
        Serial.println("checkTurnRight");
        setMotor(200,-200);
        delay(600);
        while(true) {
          sensorRead();
          if(sensor2 + sensor3 + sensor4 + sensor5 + sensor6 + sensor7 == 5){
              Serial.println("checkTurnRight break.");
              break;
          }
          setMotor(200,-200);
          delay(10);
        }
    }
}

/**
 * 自动快速寻线程序
 */
void tracking() {
    if(sensor1 == BLACK){
      Serial.println("turn1R");
      setMotor(250, -250);
      delayMicroseconds(32);
    } else if(sensor2 == BLACK){
      Serial.println("turn2R");
      setMotor(250, -250);
      delayMicroseconds(16);
    } else if(sensor3 == BLACK) {
      Serial.println("turn3R");
      setMotor(200, -200);
      delayMicroseconds(8);
    } else if(sensor4 == BLACK) {
      Serial.println("turn4R");
      setMotor(200, -200);
      delayMicroseconds(4);
    } else if(sensor5 == BLACK) {
      Serial.println("turn5L");
      setMotor(-200,200);
      delayMicroseconds(4);
    } else if(sensor6 == BLACK) {
      Serial.println("turn6L");
      setMotor(-200,200);
      delayMicroseconds(8);
    } else if(sensor7 == BLACK) {
      Serial.println("turn7L");
      setMotor(-250,250);
      delayMicroseconds(16);
    } else if(sensor8 == BLACK) {
      Serial.println("turn8L");
      setMotor(-250,250);
      delayMicroseconds(32);
    } else {
      //Serial.println("Forward");
      setMotor(200,200);
      delayMicroseconds(1);
    }
}

/**
 * 上电初始化
 */
void setup() {
    // 电机引脚配置
    pinMode(E1,OUTPUT);
    pinMode(M1,OUTPUT);
    pinMode(E2,OUTPUT);
    pinMode(M2,OUTPUT);
    pinMode(BRAKEA,OUTPUT);
    pinMode(BRAKEB,OUTPUT);

    // 灰度传感器引脚配置
    pinMode(Sensor1,INPUT);
    pinMode(Sensor2,INPUT);
    pinMode(Sensor3,INPUT);
    pinMode(Sensor4,INPUT);
    pinMode(Sensor5,INPUT);
    pinMode(Sensor6,INPUT);
    pinMode(Sensor7,INPUT);
    pinMode(Sensor8,INPUT);

    // 电子罗盘初始化 传感器连接后打开该代码
    compassSetup();

    pinMode(A0, INPUT);

    Serial.begin(9600);
}

/**
 * 循环体,主函数
 */
void loop1() {
    sensorRead();
    getDist();

    totalVal = sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6 + sensor7 + sensor8;
    leftTotalVal = sensor5 + sensor6 + sensor7 + sensor8;
    rightTotalVal = sensor1 + sensor2 + sensor3 + sensor4;

    checkStop();

    checkTurnLeft();

    checkTurnRight();

    if(distance > MIN_DIST) {
      Serial.print("distance:");
      Serial.println(distance);
      //runAround();
    }

    tracking();
}

//-----------------------------------------------TEST-----------------------------------------//
/**
 * 测试电子罗盘
 */
void loop15() {
    printHeadingDegrees(getCompassDegress());
    delay(1);
}
/**
 * 测试避障
 */
void loop6() {
    setMotor(95,80);
    delay(50);
    int dist = getDist();
    if (dist < MIN_DIST) {
        Serial.print("dist:");
        Serial.println(dist);
        runAround();

        setMotor(0,0);
        while(true){
            delay(100000);
        }
    }
}

/**
 * 测试直线
 */
void loop5() {
    Serial.println("aaaaaaa");
    setMotor(210,210);
    while(true){
        delay(100000);
    }
}
/**
 * 测试电机
 */
void loop9(){
    setMotor(180,210);
    Serial.println("Forward");
    delay(2000);
    setMotor(0,180);
    Serial.println("turnL50");
    delay(2000);
    setMotor(180,0);
    Serial.println("turnR50");
    delay(2000);
}

/**
 * 测试测距
 */
void loop2() {
    int dist = getDist();
    Serial.print("dist:");
    Serial.println(dist);
}

/**
 * 测试倒车
 */
void loop12() {
    setMotor(-255,-255);
    while(true){
        delay(100000);
    }
}

/**
 * 测试传感器读值
 */
void loop11() {
    sensorRead();
    printSensor();
}

void loop3() {
    int val = analogRead(A0);
    Serial.print("A0:");
    Serial.println(val);
}

void loop() {
  turnAnticlockwise(90);
  delay(2000);
  turnClockwise(90);
  while(true);
}

