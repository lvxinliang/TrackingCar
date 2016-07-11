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

/**
 * 传感器引脚定义
 */
int SensorA = 4;
int SensorB = 5;
int SensorC = 6;
int SensorD = 7;

/**
 * 上电初始化
 */
void setup() { 
  pinMode(E1,OUTPUT);      //PIN模式
  pinMode(M1,OUTPUT);
  pinMode(E2,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(BRAKEA,OUTPUT);
  pinMode(BRAKEB,OUTPUT);
  
  pinMode(SensorA,INPUT);
  pinMode(SensorB,INPUT);
  pinMode(SensorC,INPUT);
  pinMode(SensorD,INPUT);
  
  Serial.begin(9600);
}

/**
 * 测试电机
 */
void loop(){
    setMotor(100,100);
    Serial.println("Forward");
    delay(2000);
    setMotor(0,80);
    Serial.println("turnL50");
    delay(2000);
    setMotor(80,0);
    Serial.println("turnR50");
    delay(2000);
}

/**
 * 循环体,主函数
 */
void loop1() {
  char sensorA,sensorB,sensorC,sensorD;
  sensorA = digitalRead(SensorA);
  sensorB = digitalRead(SensorB);
  sensorC = digitalRead(SensorC);
  sensorD = digitalRead(SensorD);
  
  if(sensorA == 1)
  {
    setMotor(-50,50);
    Serial.println("turnL100");
  }
  else if(sensorB == 1)
  {
    setMotor(-80,0);
    Serial.println("turnL50");
  }
  else if(sensorC == 1)
  {
    setMotor(0,-80);
    Serial.println("turnR50");
  }
  else if(sensorD == 1)
  {
    setMotor(50,-50);
    Serial.println("turnR100");
  }
  else
  {
    setMotor(100,100);
    Serial.println("Forward");
  }
}
/********************************************************
setMotor(int MOTORA,int MOTORB)参数说明：
MOTORA>0,A电机正转,0<MOTORA<255
MOTORA<0,A电机反转
MOTORB>0,B电机正转,0<MOTORB<255
MOTORB<0,B电机反转
*********************************************************/
void setMotor(int MOTORA,int MOTORB) //电机驱动函数
{
  if(MOTORA>0)
  {
    digitalWrite(BRAKEA,LOW);
    digitalWrite(M1,LOW);     //正转
    analogWrite(E1,255-MOTORA);
  }
  else if(MOTORA<0)
  {
    digitalWrite(BRAKEA,LOW);
    digitalWrite(M1,HIGH);    //反转
    analogWrite(E1,MOTORA+255);
  }
  else
  {
    digitalWrite(BRAKEA,HIGH);
    digitalWrite(M1,HIGH);   
    analogWrite(E1,LOW);
  }
  if(MOTORB>0)
  {
    digitalWrite(BRAKEB,LOW);
    digitalWrite(M2,LOW);     //正转
    analogWrite(E2,255-MOTORB);
  }
  else if(MOTORB<0)
  {
    digitalWrite(BRAKEB,LOW);
    digitalWrite(M2,HIGH);      //反转
    analogWrite(E2,255+MOTORB);
  }
  else
  {
    digitalWrite(BRAKEB,HIGH);
    digitalWrite(M2,HIGH);  
    analogWrite(E2,LOW);
  }
}



