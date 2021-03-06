#pragma config(Sensor, dgtl1,  wheelEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           R1Wheel,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           L1Wheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           L2Wheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           R2Wheel,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//variables
int motorSpeed;
//int joyThresh;
//int wheelThresh;
int waitTime;
int wheelEncoderSpeed = abs(SensorValue[wheelEncoder]); // <-- SUDO CODE, replace with actual name of encoder
//int encoderTimer = time1[T1];
int dataPointOne;
int dataPointTwo;
int speed;
int minSpeed = 14700; //degrees of rotation every half a second.

//this function sets all the wheel motors to the motorSpeed
void setmotorSpeed() {
		motor[L1Wheel] = motorSpeed;
		motor[L2Wheel] = motorSpeed;
		motor[R1Wheel] = motorSpeed;
		motor[R2Wheel] = motorSpeed;
}

//this sets all the wheel motors to zero
void resetMotors() {
    motorSpeed = 0;
    setmotorSpeed();
}

void bangBang() {
    waitTime = 500;
    while (vexRT[Btn8R] == 1) {
        dataPointOne = wheelEncoderSpeed;
        wait1Msec(waitTime);
        dataPointTwo = wheelEncoderSpeed;
        // SUDO
        speed = ((dataPointTwo - dataPointOne)/waitTime);
        if (speed < minSpeed){
        	if (motorSpeed < 127) {
            motorSpeed = (motorSpeed + 3);
         	}
            setmotorSpeed();
            wait1Msec(waitTime);
       }else{
		motorSpeed = (motorSpeed - 3);
		setmotorSpeed();
		wait1Msec(waitTime);
    	 }
  	}
}

//this function lets buttons control the wheel speed
void runTestmotorSpeed() {
	while (1 == 1) {

        // full speed
        while (vexRT[Btn8U] == 1) {
            motorSpeed = 127;
            setmotorSpeed();
        }

    		resetMotors();

				 // 3/4 speed
        while (vexRT[Btn8R] == 1) {
            motorSpeed = 100;
            setmotorSpeed();
            bangBang();
        }

    		resetMotors();

        // half speed
        while (vexRT[Btn8D] == 1) {
            motorSpeed = 60;
            setmotorSpeed();
        }

				resetMotors();


        // 1/4 speed
        while (vexRT[Btn8L] == 1) {
            motorSpeed = 30;
            setmotorSpeed();
        }

    		resetMotors();

    		//

    } // end of main while loop
} // end of function


task main() {

    runTestmotorSpeed();

} //ending bracket
