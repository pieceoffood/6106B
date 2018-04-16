#ifndef autonomousHelpers
#define autonomousHelpers

#include "Driver.h"
//#define DEBUG
void resetEncoders()
{
	SensorValue[en_left_base] = 0;
	SensorValue[en_right_base] = 0;
}

int gyroTarget = 0;

int gyro()
{

	return (SensorValue[gyro_left] + SensorValue[gyro_right]) / 2;

}

void resetGyro()
{
	SensorValue[gyro_left] = 0;
	SensorValue[gyro_right] = 0;
}


task tTurn()
{
	const float kp = 0.35; // proportional constant
	const float ki = 0;
	const float kd = -20; // derivatie constant
	static int lastMeasure=nSysTime;
	int lastErr, allErr, powerOutput = 0;
	int err = 0;
	for(ever)
	{
		wait1Msec(25);
		float dt=nSysTime-lastMeasure;
		err = gyroTarget - gyro();
		powerOutput = err * kp + // Proportional
		(lastErr - err)/dt * kd;
		lastErr = err;
		moveLeftWheels(-powerOutput);
		moveRightWheels(powerOutput);

#ifdef DEBUG
		//formatted as Error P I D dt
		writeDebugStreamLine("Turn at %d", nSysTime);
		writeDebugStreamLine("Data: %d | %d | %d | %d | %d |",err, err*kp, 0, (lastErr - err)/dt * kd, dt);
		writeDebugStreamLine("Gyro: %d",gyro());
		writeDebugStreamLine("Output: %d", powerOutput);
		writeDebugStreamLine("--------------------");
#endif
		lastMeasure=nSysTime;
		abortTimeslice();
	}

}


float wheelsTarget = 0;
bool correctDirection = false;
bool shouldResetGyro = false;
/*
float velocity(const bool init=false){
static int previousReadingTime[200];
static int previousReading[200];


if (init){
for (int ii=0;ii<200;ii++){

previousReadingTime[ii]=nSysTime;
previousReading[ii];

}
}

}
*/
task tMoveWheels()
{ //distance in inches
#define currLocLeft (SensorValue[en_left_base])
#define currLocRight (-SensorValue[en_right_base])
	int lastMeasure=nSysTime;
	const float distance = wheelsTarget;
	static const float ticksPerInches = 360 / (PI * 4);
	float dt=nSysTime-lastMeasure;
	resetEncoders();
	if (correctDirection) { if (shouldResetGyro) resetGyro(); }

	long sumLeft = 0, sumRight = 0;
	float kp = 1; // proportional constant
	const float ki = 0;//0.000025;
	const float kd = -15; // derivatie constant
	static int lastErrLeft, lastErrRight = 0;
	int powerOutputLeft, powerOutputRight = 0;
	int errLeft, errRight = 0;

	for(ever)
	{
		wait1Msec(25);
		kp=0.52/*-(nImmediateBatteryLevel/1000-7)/4*/;
		errLeft = distance * ticksPerInches - currLocLeft * EN_LEFT_DIRECTION;
		errRight = distance * ticksPerInches - currLocRight * EN_RIGHT_DIRECTION;
		sumLeft += errLeft*dt;
		sumRight += errRight*dt;
		dt=nSysTime-lastMeasure;

		powerOutputLeft = errLeft * kp + // Proportional
		(sumLeft+errLeft*dt) * ki + // Integral
		(lastErrLeft - errLeft)/dt * kd;

		powerOutputRight = errRight * kp + // Proportional
		sumRight * ki + // Integral
		(lastErrRight - errRight)/dt * kd;

		if (correctDirection)
		{
			powerOutputLeft += gyro();
			powerOutputRight -= gyro();
		}




		//formatted as Error P I D dt
#ifdef DEBUG
		writeDebugStreamLine("Wheels at %d", nSysTime);
		writeDebugStreamLine("Left: %d | %d | %d | %d | %d |",errLeft, errLeft*kp, sumLeft*ki, (lastErrLeft - errLeft)/dt * kd, dt);
		writeDebugStreamLine("Right: %d | %d | %d | %d | %d |",errRight, errRight*kp, sumRight*ki, (lastErrRight - errRight)/dt * kd, dt);
		writeDebugStreamLine("Gyro: %d",gyro());
		writeDebugStreamLine("Output: L: %d | R: %d",powerOutputLeft,powerOutputRight);
		writeDebugStreamLine("--------------------");
#endif

		lastErrLeft = errLeft;
		lastErrRight = errRight;
		moveLeftWheels(powerOutputLeft);
		moveRightWheels(powerOutputRight);
		lastMeasure=nSysTime;
		abortTimeslice();
	}

}

int mobileGoalTarget = 0;

task tMoveMobileGoal()
{
	const float kp = -1; // proportional constant
	const float ki = 0;
	const float kd = 0; // derivatie constant
	int lastErr, allErr, powerOutput = 0;
	int err = 0;

	for(ever)
	{
		err = mobileGoalTarget - SensorValue[pot_mg];
		powerOutput = err * kp + // Proportional
		allErr * ki + (lastErr - err) * kd;
		lastErr = err;
		allErr += err;
		moveMobileGoal(powerOutput);
		abortTimeslice();
	}

}


void releaseWheels()
{
	stopTask(tTurn);
	stopTask(tMoveWheels);
}


void moveWheels(const float distance, const bool straight = true, const float tolerance = 0.5,
const bool shouldResetGyroscope = true)
{
	static const float ticksPerInches = 360 / (PI * 4);

	correctDirection = straight;
	shouldResetGyro = shouldResetGyroscope;
	wheelsTarget = distance;
	releaseWheels();
	startTask(tMoveWheels);


	while (not(
		approxEq(currLocLeft * EN_LEFT_DIRECTION, distance * ticksPerInches, tolerance * ticksPerInches) and
	approxEq(currLocRight * EN_RIGHT_DIRECTION, distance * ticksPerInches,
	tolerance * ticksPerInches))) {} //blocks when target not reached
	#ifdef DEBUG
	for (int ii=0;ii<100;ii++){
		writeDebugStreamLine("!!!!!!!!Target %d reached at %d.", wheelsTarget,nSysTime);
		writeDebugStreamLine("!!!!!!!!Current reading: L: %d | R: %d",currLocLeft * EN_LEFT_DIRECTION, currLocRight * EN_RIGHT_DIRECTION);
	}
#endif
	return;


}


#undef currLocLeft
#undef currLocRight

void turn(const int degrees, int tolerance = 10) //positive numger for turning clockwise
{
	resetGyro();
	if (degrees > 360 or degrees < -360) return; // Cannot throw an exception in robotC. Just return
		releaseWheels();

	gyroTarget = -degrees * 10;
	startTask(tTurn);

	while (not approxEq(gyro(), -degrees * 10, tolerance)) {} //blocks when target not reached
#ifdef DEBUG
	for (int ii=0;ii<10;ii++)
		writeDebugStreamLine("!!!!!Target %d reached at %d. Current reading: %d ", gyroTarget,nSysTime,gyro());
#endif
}

void mobileGoal(const int target, bool block = false, int tolerance = 30, int delay=0)
{
	stopTask(tMoveMobileGoal);
	mobileGoalTarget = target;
	startTask(tMoveMobileGoal);
	if (block)
	{
		while (not approxEq(target, SensorValue[pot_mg], tolerance)) {} //blocks when target not reached

	}

}

void mg_in(bool block, int delay=0){
	mobileGoal(900,block,60,delay);
}

void mg_mid(bool block, int delay=0){
	mobileGoal(2000,block,60,delay);
}

void mg_out(bool block, int delay=0){
	mobileGoal(3300,block,80,delay);
}
/*
void outOfSize(int fourBar, int chainBar){
	holdFourBar(fourBar);
	while (SensorValue[pot_chainbar] > 3600){
		chainBarMove(-120);
	}
	holdChainBar(chainBar);
}*/

#endif
