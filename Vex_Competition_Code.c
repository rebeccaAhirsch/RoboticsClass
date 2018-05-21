#pragma config(Motor,  port1,           intakeMotor,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightShooterMotors, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftShooterMotors, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           treadMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           treadMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightDriveMotors, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftDriveMotors, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           innerWheelMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//our functions
void runDriveMotors(int Lspeed, int Rspeed){
	motor[leftDriveMotors] = Lspeed;
	motor[rightDriveMotors] = Rspeed;
}
void runShooter( int speed) {
	motor[leftShooterMotors] = speed;
	motor[rightShooterMotors] = speed;
}
void intakeAndShoot(int speed) {
	runShooter(speed);
	motor[intakeMotor] = speed;
	motor[treadMotor] = speed;
}
void turnAllOff() {
	motor[intakeMotor] = 0;
	runDriveMotors(0,0);
	runShooter(0);
	motor[treadMotor] = 0;
	motor[innerWheelMotor] = 0;
}

int nBtn6U;
int nBtn6D;
int nBtn8U;
int nBtn7U;
int nBtn8R;
int nBtn7L;
int	nBtn8D;

//intake - 6U 6D
//innerWheel - 7U
//tread - 7L
//shooter - 8U full 8r half
//intake all - 8D


/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
 turnAllOff();
 intakeAndShoot(127);
 wait1Msec(500);
 motor[innerWheelMotor] = 127;
 wait1Msec(10000);
 turnAllOff();
 runDriveMotors(-127, -100);
 wait1Msec(1000);
 runDriveMotors(0,0);
 runDriveMotors(20,-127);
 wait1Msec(500);
 runDriveMotors(0,0);
 runDriveMotors(-40,0);
 wait1Msec(1000);
 runDriveMotors(0,0);
 motor[intakeMotor] = 127;
 wait1Msec(500);
 runDriveMotors(0,0);
 runDriveMotors(70,70);
 intakeAndShoot(127);
 wait1Msec(1000);
 runDriveMotors(0,0);
 turnAllOff();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
    //Right side of the robot is controlled by the right joystick, Y-axis
    motor[leftDriveMotors] = vexRT[Ch3];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[rightDriveMotors] = vexRT[Ch2];
    //Intake is controlled by top bumpers

//intake backwards
    if (vexRT[Btn6U] == 1) {
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

 //intake and shoot
  	if(vexRT[Btn8D] == 1) {
   	nBtn8D += 1;
	    if (nBtn8D % 2 == 0) {
	    	intakeAndShoot(0);
	  	}else{
	  		intakeAndShoot(127);
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
	    	runShooter(0);
	  	}else{
	  		runShooter(127);
	  	}
	  	wait1Msec(200);
		}

//run shooter at half
  	if (vexRT[Btn8R] == 1) {
  		nBtn8R += 1;
	    if (nBtn8R % 2 == 0) {
	    	runShooter(0);
	  	}else{
	    	runShooter(60);
	  	}
	  	wait1Msec(200);
  	}

//scoot scoot left
  	if (vexRT[Btn8L] == 1) {
  		runDriveMotors(0, 127);
  		wait1Msec(30);
  		runDriveMotors(127, -1);
  		wait1Msec(10);
  		runDriveMotors(0, 0);
  	}

//scoot scoot right
  	if (vexRT[Btn7R] == 1) {
  		runDriveMotors(127, 0);
  		wait1Msec(30);
  		runDriveMotors(-1, 127);
  		wait1Msec(10);
  		runDriveMotors(0, 0);
  	}
	}
}
