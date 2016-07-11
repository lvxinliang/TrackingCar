/*
 * 逻辑最大值
 */
const int ANALOG_MAX_VAL = 255;
/*
 * 每个电机需要两个GPIO控制
 */
const int leftWheelPin1 = 3;
const int leftWheelPin2 = 5;  // PWM Pin
const int rightWheelPin1 = 6;
const int rightWheelPin2 = 9;  // PWM Pin

/*
 * 左侧轮子
 */
const int LEFT_WHEEL = 0;
/*
 * 右侧轮子
 */
const int RIGHT_WHEEL = 1;

/*
 * 轮子正转
 */
const int FORWARD = 1;
/*
 * 轮子反转
 */
const int BACK = 2;
/*
 * 轮子停止
 */
const int STOP = 0;

/*
 * 控制单个电机
 */
void setMotor(int pin, int pwmPin, int motorState, int speed) {
	if(motorState == 1) {  
		analogWrite(pwmPin, speed);
		digitalWrite(pin, 1);
	} else if (motorState == 2) {
		analogWrite(pwmPin, speed);
		digitalWrite(pin, 0);
	} else if (motorState == 0) {
		analogWrite(pwmPin, 0);
		digitalWrite(pin, 0);
	}
}

/*
 * 控制单个轮子方向
 */
void setWheel(int wheel, int motorState, int speed) {
	// 控制左轮
	int pin = leftWheelPin1;
	int pwmPin = leftWheelPin2;

	if(wheel == RIGHT_WHEEL) { // 控制右轮
		pin = rightWheelPin1;
		pwmPin = rightWheelPin2;
	}
	setMotor(int pin, int pwmPin, motorState, speed);
}

/*
 * 小车停止
 */
void stopCar() {
	setWheel(LEFT_WHEEL, STOP, 0);
	setWheel(RIGHT_WHEEL, STOP, 0);
}

/*
 * 小车前进
 */
void runFoward (int speed) {
	setWheel(LEFT_WHEEL, FORWARD, speed);
	setWheel(RIGHT_WHEEL, FORWARD, speed);
}
/*
 * 小车后退
 */
void runBack (int speed) {
	setWheel(LEFT_WHEEL, BACK, speed);
	setWheel(RIGHT_WHEEL, BACK, speed);
}
/*
 * 小车左转
 */
void runLeft (int speed) {
	setWheel(LEFT_WHEEL, STOP, speed);
	setWheel(RIGHT_WHEEL, FORWARD, speed);
}

/*
 * 小车右转
 */
void runRight (int speed) {
	setWheel(LEFT_WHEEL, FORWARD, speed);
	setWheel(RIGHT_WHEEL, STOP, speed);
}

/*
 * 上电初始化代码
 */
void setup() {
	pinMode(leftWheelPin1,OUTPUT);
	pinMode(leftWheelPin2,OUTPUT);
	pinMode(rightWheelPin1,OUTPUT);
	pinMode(rightWheelPin2,OUTPUT);
	stopCar();

	pinMode(A0,INPUT);
	pinMode(A1,INPUT);
	pinMode(A2,INPUT);
	pinMode(A3,INPUT);
	pinMode(A4,INPUT);
	pinMode(A5,INPUT);
	pinMode(A6,INPUT);

	// Start Serial
	Serial.begin(9600);
}

/*
 * 循环主函数
 */
void loop() {

}

/*
 * 方向测试
 */
void test1() {
	runFoward(250);
	delay(2000);
	runBack(250);
	delay(2000);

	runLeft(100);
	delay(1000);
	runRight(100);
	delay(1000);

	stopCar();
	delay(10000);
}
