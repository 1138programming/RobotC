#pragma config(Sensor, dgtl3,  limitSwitchTop, sensorTouch)
#pragma config(Sensor, dgtl5,  limitSwitchBottom, sensorTouch)
#pragma config(Motor,  port1,           collector1,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           laucher1,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           laucher2,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          collector2,    tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int threshold(int number, int threshold = 50)
{// Returns a value constrained to a threshold defined by the optional threshold parameter to this function, or 50 if no value is
	return (abs(number) <= threshold) ? 0 : number;
}
task main()
{
	//x drive base
	while(true)
	{
		motor[frontRight] = threshold(vexRT[Ch2]);
		motor[backRight] = threshold(vexRT[Ch2]);
		motor[frontLeft] = threshold(vexRT[Ch3]);
		motor[backLeft] = threshold(vexRT[Ch3]);

		//Strafing
		while(vexRT[Btn6U] == 1)
		{
			motor[frontLeft] = 127;
			motor[frontRight] = -127;
			motor[backLeft] = -127;
			motor[backRight] = 127;
		}

		while(vexRT[Btn5U] == 1)
		{
			motor[frontLeft] = -127;
			motor[frontRight] = 127;
			motor[backLeft] = 127;
			motor[backRight] = -127;
		}

		//collector
		/*if(vexRT[Btn6UXmtr2] == 1)
		{
			while(SensorValue[limitSwitchTop] != 1)
			{
				motor[collector] = 127;
			}

			while(SensorValue[limitSwitchBottom] != 1)
			{
				motor[collector] = -127;
			}
			motor[collector] = 0;
		}*/

		while(vexRT[Btn6UXmtr2] == 1)
		{
			motor[collector1] = 127;
			motor[collector2] = 127;
		}

		while(vexRT[Btn6DXmtr2] == 1)
		{
			motor[collector1] = -127;
			motor[collector2] = -127;
		}

		//lift
		motor[liftLeft] = threshold(vexRT[Ch3Xmtr2]);
		motor[liftRight] = threshold(vexRT[Ch3Xmtr2]);

		//laucher
		while(vexRT[Btn5UXmtr2] == 1)
		{
			motor[laucher1] = 127;
			motor[laucher2] = 127;
		}
	}
}
