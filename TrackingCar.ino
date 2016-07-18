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

const int DELAY_TIME = 350;

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
<<<<<<< HEAD
      analogWrite(E1, 0 - MOTORA);
=======
      analogWrite(E1, MOTORA + 255);
>>>>>>> f03547d524d47f8c815b29211c1eeace595a34e6
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
<<<<<<< HEAD
      analogWrite(E2, 0 - MOTORB);
=======
      analogWrite(E2, 255 + MOTORB);
>>>>>>> f03547d524d47f8c815b29211c1eeace595a34e6
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
<<<<<<< HEAD
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
=======
    setMotor(0,165);
    delay(300);
    // 向前
    setMotor(180,210);
    delay(1000);
    // 向右
    setMotor(165,0);
    delay(300);
    // 向前
    setMotor(180,210);
    delay(1000);
    // 向右
    setMotor(165,0);
    delay(300);
    // 向前
    setMotor(180,210);
    delay(1000);
    // 向左
    setMotor(0,90);
    delay(300);
    // 向前
    setMotor(180,210);
>>>>>>> f03547d524d47f8c815b29211c1eeace595a34e6
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

<<<<<<< HEAD
void loop12() {
=======
void loop4() {
    setMotor(180,210);
    delay(1000);

    runAround();
>>>>>>> f03547d524d47f8c815b29211c1eeace595a34e6

    // 
    setMotor(-255,-255);
    while(true){
        delay(100000);
    }
}

/**
 * 测试传感器读值
 */
void printSen() {
    sensor1 = digitalRead(Sensor1);
    sensor2 = digitalRead(Sensor2);
    sensor3 = digitalRead(Sensor3);
    sensor4 = digitalRead(Sensor4);
    sensor5 = digitalRead(Sensor5);
    sensor6 = digitalRead(Sensor6);
    sensor7 = digitalRead(Sensor7);
    sensor8 = digitalRead(Sensor8);
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
 * 测试电机
 */
<<<<<<< HEAD
void loop9(){
=======
void loop2(){
>>>>>>> f03547d524d47f8c815b29211c1eeace595a34e6
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
 * 循环体,主函数
 */
void loop() {
//    sensor1 = digitalRead(Sensor1);
    sensor2 = digitalRead(Sensor2);
    sensor3 = digitalRead(Sensor3);
    sensor4 = digitalRead(Sensor4);
    sensor5 = digitalRead(Sensor5);
    sensor6 = digitalRead(Sensor6);
    sensor7 = digitalRead(Sensor7);

    if(sensor1 == BLACK){
      Serial.println("turn1R");
      printSen();
      setMotor(255, -200);
      delay(DELAY_TIME);
    } else if(sensor2 == BLACK){
      Serial.println("turn2R");
      setMotor(200, -200);
      delay(DELAY_TIME);
    } else if(sensor3 == BLACK) {
      Serial.println("turn3R");
      setMotor(200, -200);
      delay(DELAY_TIME);
    } else if(sensor4 == BLACK) {
      Serial.println("turn4R");
      setMotor(200, -200);
      delay(DELAY_TIME);
    } else if(sensor5 == BLACK) {
      Serial.println("turn5L");
      setMotor(-200,200);
      delay(DELAY_TIME);
    } else if(sensor6 == BLACK) {
      Serial.println("turn6L");
      setMotor(-200,200);
      delay(DELAY_TIME);
    } else if(sensor7 == BLACK) {
      Serial.println("turn7L");
      setMotor(-200,200);
      delay(DELAY_TIME);
    } else if(sensor8 == BLACK) {
      Serial.println("turn8L");
      setMotor(-200,255);
      delay(DELAY_TIME);
    } else {
<<<<<<< HEAD
=======
      setMotor(180,210);
>>>>>>> f03547d524d47f8c815b29211c1eeace595a34e6
      Serial.println("Forward");
      setMotor(150,150);
      delay(2);
    }
}

