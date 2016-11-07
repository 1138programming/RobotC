#pragma config(Sensor, dgtl2,  catapultLimitSwitch, sensorTouch)
#pragma config(Motor,  port1,           collectorLeft, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           liftLeft,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           shooterLeft,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           shooterRight,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          collectorRight, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
int autonNumber = 0;

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

void pre_auton()
{
	bStopTasksBetweenModes = true;

	/*------------------------LCD Program Start Here--------------------------*/
	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery, backupBattery;
	clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
	clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

	//Display the Primary Robot battery voltage
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	//Display the Backup battery voltage
	displayLCDString(1, 0, "Backup: ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
	displayNextLCDString(backupBattery);

	//Short delay for the LCD refresh rate
	wait1Msec(5000);

	//Declare count variable to keep track of our choice
	int count = 0;

	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count)
		{
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Driver Control");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
				} else if(nLCDButtons == centerButton) {
				startTask(usercontrol);
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Autonomous 1");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
				} else if(nLCDButtons == centerButton) {
				autonNumber = 0;
				startTask(autonomous);
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Autonomous 2");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
				} else if(nLCDButtons == centerButton) {
				autonNumber = 1;
				startTask(autonomous);
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Autonomous 3");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
				} else if(nLCDButtons == centerButton) {
				autonNumber = 2;
				startTask(autonomous);
			}
			break;
		default:
			count = 0;
			break;
		}
	}
}
/*----------------------LCD Program Ends Here--------------------------*/

/*---------------------Autonomous Starts Here--------------------------*/
void base(int left, int right, int time)//A function for tank drive
{
	motor[frontLeft] = left;
	motor[backLeft] = left;
	motor[frontRight] = right;
	motor[backRight] = right;
	wait1Msec(time);
}

void strafing(int speed, int time, int position = 1) //A function for strafing, 0 is right, 1 is left
{
	motor[frontLeft] = position == 1 ? speed : -1 * speed;
	motor[frontRight] = position == 1 ? -1 * speed : speed;
	motor[backLeft] = position == 1 ? -1 * speed : speed;
	motor[backRight] = position == 1 ? speed : -1 * speed;
	wait1Msec(time);
}

void collector(int speed, int time)//a function for collector
{
	motor[collectorLeft] = speed;
	motor[collectorRight] = speed;
	wait1Msec(time);
}

void launcher(int speed, int time)//a function for launcher
{
	motor[shooterLeft] = speed;
	motor[shooterRight] = speed;
	wait1Msec(time);
}

task autonomous()//Tasks for autonomous
{
	switch(autonNumber) {
	case 0://First Autonomous
		while(true)
		{
			clearLCDLine(0);
			displayLCDCenteredString(0, "Auton 1 Selected");
			/*collector(-127, 2000);
			launcher(127, 2000);//shoot the preload
			launcher(0, 1300);
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
		}
		break;
	case 1://Second Autonomous
		while(true)
		{
			clearLCDLine(0);
			displayLCDCenteredString(0, "Auton 2 Selected");
		}
		break;
	case 2://Third Autonomous
		while(true)
		{
			clearLCDLine(0);
			displayLCDCenteredString(0, "Auton 3 Selected");
		}
		break;
	}
	AutonomousCodePlaceholderForTesting();
}

/*-------------------Driver Controll Starts Here-----------------*/
int threshold(int number, int threshold = 50)
{// Returns a value constrained to a threshold defined by the optional threshold parameter to this function, or 50 if no value is
	return (abs(number) <= threshold) ? 0 : number;
}

task usercontrol()
{
	while (true)
	{//tank drive
		motor[frontRight] = threshold(vexRT[Ch2]);
		motor[backRight] = threshold(vexRT[Ch2]);
		motor[frontLeft] = threshold(vexRT[Ch3]);
		motor[backLeft] = threshold(vexRT[Ch3]);

		//Strafing
		while(vexRT[Btn6U] == 1)//strafing right
		{
			motor[frontLeft] = 127;
			motor[frontRight] = -127;
			motor[backLeft] = -127;
			motor[backRight] = 127;
		}

		while(vexRT[Btn5U] == 1)//strafing left
		{
			motor[frontLeft] = -127;
			motor[frontRight] = 127;
			motor[backLeft] = 127;
			motor[backRight] = -127;
		}

		//collector
		motor[collectorRight] = threshold(vexRT[Ch3Xmtr2]);
		motor[collectorLeft] = threshold(vexRT[Ch3Xmtr2]);

		//lift
		if(vexRT[Btn5UXmtr2] == 1)//if 5U is pressed, lift go up
		{
			motor[liftLeft] = -127;
			motor[liftRight] = -127;
		}
		else if (vexRT[Btn5DXmtr2] == 1)//if 5D is pressed, lift go down
		{
			motor[liftLeft] = 127;
			motor[liftRight] = 127;
		}
		else//if nothing is pressed, freeze all motor
		{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}

		// Catapult code
		if(vexRT[Btn8DXmtr2] == 1)//if 8D is press
		{
			motor[shooterLeft] = 127;//move up the launcher for 5 milliseconds
			motor[shooterRight] = 127;
			wait1Msec(5);
			while(SensorValue[catapultLimitSwitch] != 1)//if the limit switch is not pressed
			{
				motor[shooterRight] = 127;//launcher keep going
				motor[shooterLeft] = 127;
				if(vexRT[Btn7LXmtr2] == 1)//if 7L is pressed, stop shooter motors
				{
					motor[shooterRight] = 0;
					motor[shooterLeft] = 0;
				}
			}
			motor[shooterRight] = 0;//if the limit switch is press, stop all shooter motors
			motor[shooterLeft] = 0;
		}

		if(vexRT[Btn6UXmtr2] == 1 && vexRT[Btn6DXmtr2] == 0)//if partner controller 6U is pressed
		{
			motor[shooterRight] = 127;//start shooter
			motor[shooterLeft] = 127;
		}
		else if(vexRT[Btn6UXmtr2] == 0 && vexRT[Btn6DXmtr2] == 1)//if partner controller 6D is pressed
		{
			motor[shooterRight] = -127;//shooter go backwards
			motor[shooterLeft] = -127;
		}
		else//if nothing is press
		{
			motor[shooterRight] = 0 ;//stop all shooter motors
			motor[shooterLeft] = 0 ;
		}

		if(vexRT[Btn7LXmtr2] == 1)//stop shooter motors
		{
			motor[shooterRight] = 0;
			motor[shooterLeft] = 0;
		}
		UserControlCodePlaceholderForTesting();
	}
}