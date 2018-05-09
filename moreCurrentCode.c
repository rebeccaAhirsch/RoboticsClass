#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           intakeMotor,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           frontRightMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           frontLeftMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           backLeftMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           backRightMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           ShooterMotors, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           treadMotor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          innerWheelMotor, tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                              - Dual Joystick Control with 4 Motors -                               *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses both the Left and the Right joysticks to run the robot using "tank control".    *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing both right-side motors (ports 2 and 3) in the "Motors and Sensors Setup" is       *|
|*        needed with the "VEX Tumbler" model, but may not be needed for all robot configurations.    *|
|*    2)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    3)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]                [Type]                [Description]                   *|
|*    Motor Port 2        frontRightMotor       VEX 3-wire module     Right side motor                *|
|*    Motor Port 3        backRightMotor        VEX 3-wire module     Right side motor                *|
|*    Motor Port 4        frontLefttMotor       VEX 3-wire module     Left side motor                 *|
|*    Motor Port 5        backLeftMotor         VEX 3-wire module     Left side motor                 *|
\*----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
void allDriveMotors(int speed) {
	motor[frontLeftMotor] = speed;
  motor[backLeftMotor]  = speed;
  motor[frontRightMotor] = speed;
  motor[backRightMotor]  = speed;
}

void leftDriveMotors(int speed){
	motor[frontLeftMotor] = speed;
  motor[backLeftMotor]  = speed;
}

void rightDriveMotors(int speed) {
	motor[frontRightMotor] = speed;
  motor[backRightMotor]  = speed;
}

int nBtn6U;
int nBtn6D;
int nBtn8U;
int nBtn7U;
int nBtn8R;
int nBtn7L;

//intake - 6U 6D
//innerWheel - 7U
//tread - 7L
//shooter - 8U full 8r half

task main()
{
  while(true)
  {
    //Right side of the robot is controlled by the right joystick, Y-axis
    motor[frontLeftMotor] = vexRT[Ch2];
    motor[backLeftMotor]  = vexRT[Ch2];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[frontRightMotor] = vexRT[Ch3];
    motor[backRightMotor]  = vexRT[Ch3];
    //Intake is controlled by top bumpers

//intake backwards
    if(vexRT[Btn6U] == 1) {
    	nBtn6U += 1;
	    if (nBtn6U % 2 == 0) {
	    	motor[intakeMotor] = 0;
	  	}else{
	  		motor[intakeMotor] = -127;
	  	}
	  	wait1Msec(200);
		}

//intake forwards
    if(vexRT[Btn6D] == 1) {
   	nBtn6D += 1;
	    if (nBtn6D % 2 == 0) {
	    	motor[intakeMotor] = 0;
	  	}else{
	  		motor[intakeMotor] = 127;
	  	}
	  	wait1Msec(200);
  	}

//run Inner Wheel
  	if (vexRT[Btn7U] == 1) {
  	nBtn7U += 1;
	    if (nBtn7U % 2 == 0) {
	    	motor[innerWheelMotor] = 0;
	  	}else{
	  		motor[innerWheelMotor] = 127;
	  	}
	  	wait1Msec(200);
  	}

//run tread
  	if (vexRT[Btn7L] == 1) {
  		nBtn7L += 1;
	    if (nBtn7L % 2 == 0) {
	    	motor[treadMotor] = 0;
	  	}else{
	  		motor[treadMotor] = 127;
	  	}
	  	wait1Msec(200);
		}

//run shooter at full
  	if (vexRT[Btn8U] == 1) {
  		nBtn8U += 1;
	    if (nBtn8U % 2 == 0) {
	    	motor[ShooterMotors] = 0;
	  	}else{
	  		motor[ShooterMotors] = 127;
	  	}
	  	wait1Msec(200);
		}

//run shooter at half
  	if (vexRT[Btn8R] == 1) {
  		nBtn8R += 1;
	    if (nBtn8R % 2 == 0) {
	    	motor[ShooterMotors] = 0;
	  	}else{
	    	motor[ShooterMotors] = 60;
	  	}
	  	wait1Msec(200);
  	}

//scoot scoot left
  	if (vexRT[Btn7L] == 1) {
  		rightDriveMotors(127);
  		wait1Msec(30);
  		rightDriveMotors(-1);
  		leftDriveMotors(127);
  		wait1Msec(10);
  		allDriveMotors(0);
  	}

//scoot scoot right
  	if (vexRT[Btn7R] == 1) {
  		leftDriveMotors(127);
  		wait1Msec(30);
  		leftDriveMotors(-1);
  		rightDriveMotors(127);
  		wait1Msec(10);
  		allDriveMotors(0);
  	}
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++