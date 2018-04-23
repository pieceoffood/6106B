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
	const float kp = -1; // proportional constant
	const float ki = 0.0000;
	const float kd = 60; // derivatie constant
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
#define currLocRight (SensorValue[en_right_base])
	int lastMeasure=nSysTime;
	const float distance = wheelsTarget;
	static const float ticksPerInches = 360 / (PI * 4);
	float dt=nSysTime-lastMeasure;
	resetEncoders();
	if (correctDirection) { if (shouldResetGyro) resetGyro(); }

	long sumLeft = 0, sumRight = 0;
	const float kp = 2; // proportional constant
	const float ki = 0;//0.000025;
	const float kd = -150;//-15; // derivatie constant
	static int lastErrLeft, lastErrRight = 0;
	int powerOutputLeft, powerOutputRight = 0;
	int errLeft, errRight = 0;

	for(ever)
	{
		wait1Msec(25);

		errLeft = distance * ticksPerInches - currLocLeft * EN_LEFT_DIRECTION;
		errRight = distance * ticksPerInches - currLocRight * EN_RIGHT_DIRECTION;
		sumLeft += errLeft*dt;
		sumRight += errRight*dt;
		dt=nSysTime-lastMeasure;

		powerOutputLeft = errLeft * kp + // Proportional
		(sumLeft+errLeft*dt) * ki  + // Integral
		(lastErrLeft - errLeft)/dt * kd / max(abs(errLeft)*0.5,0.01);

		powerOutputRight = errRight * kp + // Proportional
		sumRight * ki + // Integral
		(lastErrRight - errRight)/dt * kd / max(abs(errRight)*0.5,0.01);

		if (correctDirection)
		{
			powerOutputLeft -=0.5* gyro();
			powerOutputRight +=0.5* gyro();
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
	wheelsTarget = distance*0.92;
	releaseWheels();
	startTask(tMoveWheels);


	while (not(
		approxEq(currLocLeft * EN_LEFT_DIRECTION, distance *0.92 * ticksPerInches, tolerance * ticksPerInches) and
	approxEq(currLocRight * EN_RIGHT_DIRECTION, distance *0.92 * ticksPerInches,
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

void turn(const int degrees, int tolerance = 20) //positive numger for turning clockwise
{
	resetGyro();
	if (degrees > 360 or degrees < -360) return; // Cannot throw an exception in robotC. Just return
		releaseWheels();

	gyroTarget = degrees * 10;
	startTask(tTurn);

	while (not approxEq(gyro(), degrees * 10, tolerance)) {} //blocks when target not reached
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
	mobileGoal(1250,block,60,delay);
}

void mg_mid(bool block, int delay=0){
	mobileGoal(2000,block,60,delay);
}

void mg_out(bool block, int delay=0){
	mobileGoal(3150,block,80,delay);
}
/*
void outOfSize(int fourBar, int chainBar){
	holdFourBar(fourBar);
	while (SensorValue[pot_chainbar] > 3600){
		chainBarMove(-120);
	}
	holdChainBar(chainBar);
}*/

task tFourbarUp(){
	while (not approxEq(SensorValue[pot_fourbar_left],POT_FOURBAR_LEFT_MAX,75) and not approxEq(SensorValue[pot_fourbar_right],POT_FOURBAR_RIGHT_MAX,75))
	{
		motor[left_fourbar]=100;
		motor[right_fourbar]=100;
	}
	motor[left_fourbar]=0;
	motor[right_fourbar]=0;
}

task tFourbarDown(){
	while (not approxEq(SensorValue[pot_fourbar_left],POT_FOURBAR_LEFT_MIN,75) and not approxEq(SensorValue[pot_fourbar_right],POT_FOURBAR_RIGHT_MIN,75))
	{
		motor[left_fourbar]=-100;
		motor[right_fourbar]=-100;
	}
	motor[left_fourbar]=0;
	motor[right_fourbar]=0;
}

void FourbarUp(){
	startTask(tFourbarUp);
}

void FourbarUp(bool block){
	if (block){
		while (not approxEq(SensorValue[pot_fourbar_left],POT_FOURBAR_LEFT_MAX,75) and not approxEq(SensorValue[pot_fourbar_right],POT_FOURBAR_RIGHT_MAX,75)){}
	} else { return;}
}

void fourbarDown(){
	startTask(tFourbarDown);
}

void fourbarDown(bool block){
	startTask(tFourbarDown);
	if (block){
while (not approxEq(SensorValue[pot_fourbar_left],POT_FOURBAR_LEFT_MIN,75) and not approxEq(SensorValue[pot_fourbar_right],POT_FOURBAR_RIGHT_MIN,75)){}
}}
#endif
