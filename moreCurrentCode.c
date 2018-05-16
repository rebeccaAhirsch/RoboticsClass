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

task main()
{
  while(true)
  {
    //Right side of the robot is controlled by the right joystick, Y-axis
    motor[leftDriveMotors] = vexRT[Ch3];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[rightDriveMotors] = vexRT[Ch2];
    //Intake is controlled by top bumpers



    //run auto
    if ((vexRT[Btn6U] == 1) && (vexRT[Btn6D] == 1) && (vexRT[Btn5U] == 1) && (vexRT[Btn5D] == 1)) {
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
