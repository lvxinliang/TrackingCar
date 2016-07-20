/***************************************************
 * Title: 障碍赛小车代码
 * Author: lvxinliang
 * Date: 2016-07-11
 **************************************************/

/**
 * 电机驱动数字引脚
 * 左边电机
 */
int E1 = 3;   //PWMA
int M1 = 12;  //DIRA
int BRAKEA = 9;   //BRAKEA
/**
 * 电机驱动数字引脚
 * 右边电机
 */
int E2 = 11;  //PWMB
int M2 = 13;  //DIRB
int BRAKEB = 8;   //BRAKEB

const int DELAY_TIME = 250;

/**
 * 设定超声波引脚
 */
const int TrigPin = 12;
const int EchoPin = 10;
/**
 * 小车距离前方20cm进入避障程序
 */
const int MIN_DIST = 20;
/**
 * 传感器引脚定义
 */
int Sensor1 = 16;
int Sensor2 = 17;
int Sensor3 = 2;
int Sensor4 = 4;
int Sensor5 = 5;
int Sensor6 = 6;
int Sensor7 = 7;
int Sensor8 = 18;
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

const int SENSOR_CNT= 8;
    
/**
 * 获取小车距离障碍的距离
 */
int getDist() {
    // 产生一个10us的高脉冲去触发TrigPin
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    return pulseIn(EchoPin, HIGH) / 58.00;
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

    // 超声波模块引脚配置
    pinMode(TrigPin, OUTPUT);
    // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    pinMode(EchoPin, INPUT);

    // 灰度传感器引脚配置
    pinMode(Sensor1,INPUT);
    pinMode(Sensor2,INPUT);
    pinMode(Sensor3,INPUT);
    pinMode(Sensor4,INPUT);
    pinMode(Sensor5,INPUT);
    pinMode(Sensor6,INPUT);
    pinMode(Sensor7,INPUT);
    pinMode(Sensor8,INPUT);

    Serial.begin(9600);
}

/**
 * 测试测距
 */
void loop5() {
    int dist = getDist();
    Serial.print("dist:");
    Serial.println(dist);
}

void loop12() {

    // 
    setMotor(-255,-255);
    while(true){
        delay(100000);
    }
}

/**
 * 测试传感器读值
 */
void loop14() {
    sensor1 = digitalRead(Sensor1);
    sensor2 = digitalRead(Sensor2);
    sensor3 = digitalRead(Sensor3);
    sensor4 = digitalRead(Sensor4);
    sensor5 = digitalRead(Sensor5);
    sensor6 = digitalRead(Sensor6);
    sensor7 = digitalRead(Sensor7);
    sensor8 = digitalRead(Sensor8);
    printSensor();
}

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
void loop7() {
    int sensor1 = digitalRead(Sensor1);
    Serial.println(sensor1);
}

/**
 * 测试直线
 */
void loop1() {
    setMotor(180,210);
    while(true){
        delay(100000);
    }
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
 * 延时并检测是否是停车
 */
void delayAndCheckBack() {
    delayMicroseconds(1);
    sensorRead();
    checkStop();
}

void checkBack() {
    if(SENSOR_CNT ==  totalVal) {  // 5个以上传感器检测到黑色
        setMotor(-200,-200);
        delay(2000);
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
 * 循环体,主函数
 */
void loop() {
    sensorRead();

    totalVal = sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6 + sensor7 + sensor8;
    leftTotalVal = sensor5 + sensor6 + sensor7 + sensor8;
    rightTotalVal = sensor1 + sensor2 + sensor3 + sensor4;

    checkStop();

    checkTurnLeft();

    checkTurnRight();

    tracking();
}

