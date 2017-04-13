#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  leftBumper,     sensorTouch)
#pragma config(Sensor, dgtl2,  rightBumper,    sensorTouch)
#pragma config(Sensor, I2C_1,  backLeftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  liftLeft1Encoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  liftRight1Encoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  backRightEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           backLeft,      tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           liftLeft1,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port4,           collectorRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftLeft2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRight1,    tmotorVex393_MC29, openLoop, reversed, driveRight, encoderPort, I2C_3)
#pragma config(Motor,  port7,           collectorLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           liftRight2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          backRight,     tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_4)

void base(int left, int right, int time)//base function for autonomous
{
	motor[backLeft] = left;
	motor[backRight] = right;
	motor[frontLeft] = left;
	motor[frontRight] = right;
	wait1Msec(time);
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
}

void baseEncoder(int left, int right)//base encoder function for autonomous
{
	motor[backLeft] = left;
	motor[backRight] = right;
	motor[frontLeft] = left;
	motor[frontRight] = right;
}

void lift(int speed, int time)//lift function
{
	motor[liftLeft1] = speed;
	motor[liftLeft2] = speed;
	motor[liftRight1] = speed;
	motor[liftRight2] = speed;
	wait1Msec(time);
	motor[liftLeft1] = 0;
	motor[liftLeft2] = 0;
	motor[liftRight1] = 0;
	motor[liftRight2] = 0;
}

void liftEncoder(int speed)//lift encoder function
{
	motor[liftLeft1] = speed;
	motor[liftLeft2] = speed;
	motor[liftRight1] = speed;
	motor[liftRight2] = speed;
}

void claw(int speed, int time)//claw function
{
	motor[collectorLeft] = speed;
	motor[collectorRight] = speed;
	wait1Msec(time);
	motor[collectorLeft] = 0;
	motor[collectorRight] = 0;
}

void holding(int speed, int lift, int time)//function for collecting and lifting at the same time
{
	motor[collectorLeft] = -speed;
	motor[collectorRight] = -speed;
	motor[liftLeft1] = lift;
	motor[liftLeft2] = lift;
	motor[liftRight1] = lift;
	motor[liftRight2] = lift;
	wait1Msec(time);
}

void holdingEncoder(int speed, int lift)//function for holding of encoders
{
	motor[collectorLeft] = -speed;
	motor[collectorRight] = -speed;
	motor[liftLeft1] = lift;
	motor[liftLeft2] = lift;
	motor[liftRight1] = lift;
	motor[liftRight2] = lift;
}

void threestar(int move, int lift, int claw, int time)
{
	motor[backLeft] = move;
	motor[backRight] = move;
	motor[frontLeft] = move;
	motor[frontRight] = move;
	motor[liftLeft1] = lift;
	motor[liftLeft2] = lift;
	motor[liftRight1] = lift;
	motor[liftRight2] = lift;
	motor[collectorLeft] = -claw;
	motor[collectorRight] = -claw;
	wait1Msec(time);
}
