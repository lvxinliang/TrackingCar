/*
 * 逻辑最大值
 */
const int ANALOG_MAX_VAL = 255;
/*
 * 每个电机需要两个GPIO控制
 */
const int leftWheelPin1 = 3;
const int leftWheelPin2 = 5;
const int rightWheelPin1 = 6;
const int rightWheelPin2 = 9;
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
const int FORWARD = 0;
/*
 * 轮子反转
 */
const int BACK = 1;

/*
 * 小车向前命令
 */
const int TURN_FORWARD = 0;
/*
 * 小车向后命令
 */
const int TURN_BACK = 1;
/*
 * 小车向左90°命令
 */
const int TURN_LEFT = 2;
/*
 * 小车向右90°命令
 */
const int TURN_RIGHT = 3;
/*
 * 控制单个轮子方向
 */
void setWheel(int wheel, int isForward) {
	// 控制左轮
	if(wheel == LEFT_WHEEL) {
		if(isForward == FORWARD){
			digitalWrite(leftWheelPin1, LOW);
			analogWrite(leftWheelPin2, 80);
		}else{
			digitalWrite(leftWheelPin2, LOW);
			analogWrite(leftWheelPin1, 80);
		}
	}else if(wheel == RIGHT_WHEEL) { // 控制右轮
		if(isForward == FORWARD){
			digitalWrite(rightWheelPin1, LOW);
			analogWrite(rightWheelPin2, 80);
		}else{
			digitalWrite(rightWheelPin2, LOW);
			analogWrite(rightWheelPin1, 80);
		}
	}
}

void runCommand()
