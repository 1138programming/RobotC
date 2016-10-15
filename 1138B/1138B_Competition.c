#pragma config(Sensor, dgtl2,  catapultLimitSwitch, sensorTouch)
#pragma config(Motor,  port1,           collectorLeft, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           liftLeft,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           shooterLeft,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           shooterRight,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          collectorRight, tmotorVex393_HBridge, openLoop)
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void base(int left, int right, int time)
{
	motor[frontLeft] = left;
	motor[backLeft] = left;
	motor[frontRight] = right;
	motor[backRight] = right;
	wait1Msec(time);
}


void strafing(int speed, int time, int position = 1) // 0 is right, 1 is left
{
	motor[frontLeft] = position == 1 ? speed : -1 * speed;
	motor[frontRight] = position == 1 ? -1 * speed : speed;
	motor[backLeft] = position == 1 ? -1 * speed : speed;
	motor[backRight] = position == 1 ? speed : -1 * speed;
	wait1Msec(time);
}

void collector(int speed, int time)
{
	motor[collectorLeft] = speed;
	motor[collectorRight] = speed;
	wait1Msec(time);
}

void launcher(int speed, int time)
{
	motor[shooterLeft] = speed;
	motor[shooterRight] = speed;
	wait1Msec(time);
}

task autonomous()
{
	launcher(127, 5000);//shoot the preload
	/*launcher(0, 500);
	base(127, -127, 500);//turn right
	base(0, 0, 500);
	base(127, 127, 800);//move forward
	base(0, 0, 500);
	collector(127, 500);//collect star
	collector(-127, 500);
	collector(0, 500);
	base(-127, 127, 500);//turn left
	base(0, 0, 500);
	launcher(127, 800);//launch the star
	launcher(0, 500);
	base(127, 127, 900);//move forward
	base(0, 0, 500);
	strafing(127, 2000, 1);//straf left
	strafing(0, 0);
	collector(127, 500);//collect the cube
	collector(-127, 500);
	launcher(127, 800);//launch the cube
	launcher(0, 500);*/
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int threshold(int number, int threshold = 50)
{// Returns a value constrained to a threshold defined by the optional threshold parameter to this function, or 50 if no value is
	return (abs(number) <= threshold) ? 0 : number;
}

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
    motor[frontRight] = threshold(vexRT[Ch2]);
		motor[backRight] = threshold(vexRT[Ch2]);
		motor[frontLeft] = threshold(vexRT[Ch3]);
		motor[backLeft] = threshold(vexRT[Ch3]);

		//Strafing
		while(vexRT[Btn6U] == 1)
		{
			motor[frontLeft] = 127;
			motor[frontRight] = 127;
			motor[backLeft] = -127;
			motor[backRight] = 127;
		}

		while(vexRT[Btn5U] == 1)
		{
			motor[frontLeft] = -127;
			motor[frontRight] = -127;
			motor[backLeft] = 127;
			motor[backRight] = -127;
		}

		//collector
				motor[collectorRight] = threshold(vexRT[Ch3Xmtr2]);
				motor[collectorLeft] = threshold(vexRT[Ch3Xmtr2]);

		//lift
		if(vexRT[Btn5UXmtr2] == 1)
		{
			motor[liftLeft] = 127;
			motor[liftRight] = 127;
		}
		else if (vexRT[Btn5DXmtr2] == 1)
		{
			motor[liftLeft] = -127;
			motor[liftRight] = -127;
		}
		else
		{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}

		// Catapult code
		if(vexRT[Btn8DXmtr2] == 1)
		{
			motor[shooterLeft] = -127;
			motor[shooterRight] = -127;
			wait1Msec(5);
			while(SensorValue[catapultLimitSwitch] != 1)
			{
				motor[shooterRight] = -127;
				motor[shooterLeft] = -127;
			}
			motor[shooterRight] = 0;
			motor[shooterLeft] = 0;
		}

		if(vexRT[Btn6UXmtr2] == 1)
		{
			motor[shooterRight] = 127;
			motor[shooterLeft] = 127;
		}
		else
		{
			motor[shooterRight] = 0;
			motor[shooterLeft] = 0;
		}
    UserControlCodePlaceholderForTesting();
  }
}
