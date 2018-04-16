#ifndef drivers
#define drivers



// -----------------BEGIN Global Constants Configuration-------------------
const int MG_POWER = 127; // power to mobile goal lift
const int LIFT_POWER = 127; //power to lift
const int FOURBAR_POWER = 127; // power to fourbar
const int ROLLER_POWER = 100; // power to roller
const int LIFT_ANTIGRAVITY = 10; //power to lift when it is in the "stop" position
const int MG_ANTIGRAVITY = 0; //power to mobile goal lift when it is in the "stop" position
const int FOURBAR_ANTIGRAVITY = 0;
const int ROLLER_ANTIGRAVITY = 25;

//POT_MIN is the value when the lift is physically at its physical lowest location. MIN may be larger than MAX in value.
//POT_DIRECTION can be either -1 or 1. 1 if the potentiometer reading increase when the structure moves up, -1 otherwise
const int POT_FOURBAR_LEFT_MIN = 1200;
const int POT_FOURBAR_LEFT_MAX = 4095;
const int POT_FOURBAR_LEFT_DIRECTION=1;

const int POT_FOURBAR_RIGHT_MIN = 1200;
const int POT_FOURBAR_RIGHT_MAX = 4095;
const int POT_FOURBAR_RIGHT_DIRECTION=1;

const int POT_LIFT_LEFT_DIRECTION = 1;
const int POT_LIFT_LEFT_MAX = 3882;
const int POT_LIFT_LEFT_MIN = 2150;

const int POT_LIFT_RIGHT_DIRECTION = 1;
const int POT_LIFT_RIGHT_MAX = 3703;
const int POT_LIFT_RIGHT_MIN = 2060;

const int MG_MIN = 883;
const int MG_MAX = 3260;

const int RIGHT_DIRECTION = 1;
const int LEFT_DIRECTION = 1;


const int EN_LEFT_DIRECTION = 1;
const int EN_RIGHT_DIRECTION = 1;

// ------------------END Global Constants Configuration----------------------
// -----------------BEGIN Keymap Configuration------------------

//#include "KeymapSinglePlayer.h"
#include "KeymapSinglePlayer.h"

// -----------------END Keymap Configuration----------------
// ------------------BEGIN Utility Functons---------------

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))
#define and &&
#define or ||
#define not !
#ifndef ever
#define ever ;; //for(ever)
#endif



bool approxEq(const float a, const float b, const float tolerance)
{ //tolerance should always be positive
	return abs(a-b)<=tolerance;
}


void moveLeftWheels(const int power)
{
	motor[left_base] = power;
}

void moveRightWheels(const int power)
{
	motor[right_base] = power;

}

void mobileGoalUp()
{
	motor[mg] = MG_POWER;
}


void mobileGoalDown()
{
	motor[mg] = -MG_POWER;
}

void mobileGoalStop()
{
	motor[mg] = 0;
}

void moveMobileGoal(const int power)
{
	motor[mg] = power;
}

void liftLeftUp()
{
	motor[left_lift_1] = LIFT_POWER + LIFT_ANTIGRAVITY;
	motor[left_lift_2] = LIFT_POWER + LIFT_ANTIGRAVITY;
}

void liftRightUp()
{
	motor[right_lift_1] = LIFT_POWER + LIFT_ANTIGRAVITY;
	motor[right_lift_2] = LIFT_POWER + LIFT_ANTIGRAVITY;
}

void liftMove(const int powerLeft, const int powerRight)
{
	motor[left_lift_1] = powerLeft;
	motor[left_lift_2] = powerLeft;
	motor[right_lift_1] = powerRight;
	motor[right_lift_2] = powerRight;

}

void liftDown()
{
	motor[left_lift_1] = -LIFT_POWER + LIFT_ANTIGRAVITY;
	motor[left_lift_2] = -LIFT_POWER + LIFT_ANTIGRAVITY;
	motor[right_lift_1] = -LIFT_POWER + LIFT_ANTIGRAVITY;
	motor[right_lift_2] = -LIFT_POWER + LIFT_ANTIGRAVITY;
}

void liftStop()
{
	motor[left_lift_1] = LIFT_ANTIGRAVITY;
	motor[left_lift_2] = LIFT_ANTIGRAVITY;
	motor[right_lift_1] = LIFT_ANTIGRAVITY;
	motor[right_lift_2] = LIFT_ANTIGRAVITY;
}

void rollerIn()
{
	clearTimer(T1);
	while (time1(T1) < 500) motor[roller] = ROLLER_POWER;
}



void rollerOut()
{
	motor[roller] = -ROLLER_POWER;
	//clearTimer(T1);
	//while (time1(T1) < 2500) motor[roller] = -ROLLER_POWER;
}

void rollerStop()
{
	motor[roller] = ROLLER_ANTIGRAVITY;
}

void rollerZero()
{
	motor[roller] = 0;
}

void fourBarUp()
{
	motor[left_fourbar] = FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
	motor[right_fourbar] = FOURBAR_POWER + FOURBAR_ANTIGRAVITY;

}

void fourBarMove(const int powerLeft, const int powerRight)
{
	motor[left_fourbar] = powerLeft;
	motor[right_fourbar] = powerRight;
}

void fourBarDown()
{
	motor[left_fourbar] = -FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
	motor[right_fourbar] = -FOURBAR_POWER + FOURBAR_ANTIGRAVITY;
}

void fourBarStop()
{
	motor[left_fourbar] = FOURBAR_ANTIGRAVITY;
	motor[right_fourbar] = FOURBAR_ANTIGRAVITY;
}

bool userIntervention(){
	return
	vexRT[Btn5U] or
	vexRT[Btn5D] or
	vexRT[Btn6U] or
	vexRT[Btn6D] or
	vexRT[Btn7U] or
	vexRT[Btn7D] or
	vexRT[Btn7L] or
	vexRT[Btn7R] or
	vexRT[Btn8U] or
	vexRT[Btn8D] or
	vexRT[Btn8L] or
	vexRT[Btn8R] or
	not approxEq(vexRT[Ch1],0,10) or
	not approxEq(vexRT[Ch2],0,10) or
	not approxEq(vexRT[Ch3],0,10) or
	not approxEq(vexRT[Ch4],0,10) or
	vexRT[Btn5UXmtr2] or
	vexRT[Btn5DXmtr2] or
	vexRT[Btn6UXmtr2] or
	vexRT[Btn6DXmtr2] or
	vexRT[Btn7UXmtr2] or
	vexRT[Btn7DXmtr2] or
	vexRT[Btn7LXmtr2] or
	vexRT[Btn7RXmtr2] or
	vexRT[Btn8UXmtr2] or
	vexRT[Btn8DXmtr2] or
	vexRT[Btn8LXmtr2] or
	vexRT[Btn8RXmtr2] or
	not approxEq(vexRT[Ch1Xmtr2],0,10) or
	not approxEq(vexRT[Ch2Xmtr2],0,10) or
	not approxEq(vexRT[Ch3Xmtr2],0,10) or
	not approxEq(vexRT[Ch4Xmtr2],0,10);
}

int fourbarTarget = 0;
int liftTarget = 0;
bool isLiftLocked = false;
bool isFourBarLocked = false;


task lockFourbar()
{ // hold the fourbar in place. Call stoptask to release it
#define currLocLeft (SensorValue[pot_fourbar_left]-POT_FOURBAR_LEFT_MIN)*POT_FOURBAR_LEFT_DIRECTION
#define currLocRight (SensorValue[pot_fourbar_right]-POT_FOURBAR_RIGHT_MIN)*POT_FOURBAR_RIGHT_DIRECTION

	const float kp = 0.1; // proportional constant
	const float ki = 0;
	const float kd = 0; // derivatie constant
	int lastErrLeft, lastErrRight = 0;
	int powerOutputLeft, powerOutputRight = 0;
	int errLeft, errRight = 0;

	for (ever)
	{
		errLeft = fourbarTarget - currLocLeft;
		errRight = fourbarTarget - currLocRight;

		powerOutputLeft = FOURBAR_ANTIGRAVITY + //Base power
		errLeft * kp + // Proportional
		(lastErrLeft - errLeft) * kd;

		powerOutputRight = FOURBAR_ANTIGRAVITY + //Base power
		errRight * kp + // Proportional
		(lastErrRight - errRight) * kd;


		lastErrLeft = errLeft;
		lastErrRight = errRight;

		fourBarMove(powerOutputLeft, powerOutputRight);
		abortTimeslice();
	}
#undef currLocLeft
#undef currLocRight
}


task lockLift()
{ // hold the lift in place. Call stoptask to release it

#define currLocLeft (SensorValue[pot_lift_left] - POT_LIFT_LEFT_MIN) * POT_LIFT_LEFT_DIRECTION
#define currLocRight (SensorValue[pot_lift_right]-POT_LIFT_RIGHT_MIN) * POT_LIFT_RIGHT_DIRECTION
	const float kp = 0.25; // proportional constant
	const float kd = 0; // derivatie constant
	int lastErrLeft, lastErrRight = 0;
	int powerOutputLeft, powerOutputRight = 0;
	int errLeft, errRight = 0;

	for (ever)
	{
		//POT_MIN is the value when the lift is physically at its lowest location
		errLeft = liftTarget - currLocLeft;
		errRight = liftTarget - currLocRight;

		powerOutputLeft = LIFT_ANTIGRAVITY + //Base power
		errLeft * kp + // Proportional
		(lastErrLeft - errLeft) * kd;

		powerOutputRight = LIFT_ANTIGRAVITY + //Base power
		errRight * kp + // Proportional
		(lastErrRight - errRight) * kd;

		lastErrLeft = errLeft;
		lastErrRight = errRight;
		liftMove(powerOutputLeft, powerOutputRight);
		abortTimeslice();
	}
#undef currLocLeft
#undef currLocRight
}

void releaseFourBar()
{
	isFourBarLocked = false;
	stopTask(lockFourbar);
}

void releaseLift()
{
	isLiftLocked = false;
	stopTask(lockLift);
}


void holdFourBar(const int target)
{
	fourbarTarget = target;
	if (isFourBarLocked)
	{
		stopTask(lockFourbar);
	} else
	{
		isFourBarLocked = true;
	}
	startTask(lockFourbar);
	return;

}

void holdFourBar(const int target, const float tolerance)
{
#define currLocLeft SensorValue[pot_fourbar_left] - POT_FOURBAR_LEFT_MIN
#define currLocRight SensorValue[pot_fourbar_right] - POT_FOURBAR_RIGHT_MIN
	fourbarTarget = target;
	if (isFourBarLocked)
	{
		stopTask(lockFourbar);
	} else
	{
		isFourBarLocked = true;
	}
	startTask(lockFourbar);
	while (not(approxEq(target,currLocRight , tolerance) and approxEq(target,
		currLocLeft,
	tolerance)))
	{
		//blocks
	};
	return;
#undef currLocLeft
#undef currLocRight
}

void holdLift(const int target)
{
	liftTarget = target;
	if (isLiftLocked)
	{
		stopTask(lockLift);
	} else
	{
		isLiftLocked = true;
	}
	startTask(lockLift);
	return;

}

void holdLift(const int target, const float tolerance)
{
#define currLocLeft (SensorValue[pot_lift_left]-POT_LIFT_LEFT_MIN)*POT_LIFT_LEFT_DIRECTION
#define currLocRight (SensorValue[pot_lift_right]-POT_LIFT_RIGHT_MIN)*POT_LIFT_RIGHT_DIRECTION
	liftTarget = target;
	if (isLiftLocked)
	{
		stopTask(lockLift);
	} else
	{
		isLiftLocked = true;
	}
	startTask(lockLift);
	while (not(approxEq(target,currLocRight , tolerance) and approxEq(target,
		currLocLeft,
	tolerance)))
	{
		//blocks
	};
	return;
#undef currLocLeft
#undef currLocRight
}

void readyForDroppingCone(const int count){
	switch (count)
			{
			case 0:
				holdLift(50);
				holdFourBar(2850);
				break;
			case 1:
				holdLift(50);
				holdFourBar(2850);
				break;
			case 2:
				holdLift(100);
				holdFourBar(2850);
				break;
			case 3:
				holdLift(230);
				holdFourBar(2850);
				break;
			case 4:
				holdFourBar(1450, 50);
				holdFourBar(2850);
				holdLift(300);
				break;
			case 5:
				holdFourBar(1450, 50);
				holdLift(425);
				holdFourBar(2850);

				break;
			case 6:
				holdFourBar(1450, 50);
				holdLift(515);
				holdFourBar(2850);

				break;
			case 7:
				holdFourBar(1450, 50);
				holdLift(600);
				holdFourBar(2850);

				break;
			case 8:
				holdFourBar(1450, 50);
				holdLift(700);
				holdFourBar(2850);

				break;
			case 9:
				holdFourBar(1450, 50);
				holdLift(900);
				holdFourBar(2850);
				break;
			}
		}

//----------------END Utility Functions------------

task WheelControls()
{
	for (ever) // a foreverloop
	{
		moveLeftWheels(min(120,AxisLeftWheels));
		moveRightWheels(min(120,AxisRightWheels));
		abortTimeslice();

	}
}

task MobileGoalControls()
{

	for (ever)
	{

		if (ButtonMobileGoalUp)
		{
			mobileGoalUp();
		} else if (ButtonMobileGoalDown)
		{
			mobileGoalDown();
		} else
		{
			mobileGoalStop();
		}


		abortTimeslice();
	}

}

task LiftControls()
{
	for (ever)
	{
		while (ButtonLiftUp)
		{
			if (isLiftLocked) releaseLift();
			liftLeftUp();
			liftRightUp();
		}
		while (ButtonLiftDown)
		{
			if (isLiftLocked) releaseLift();
			liftDown();
		}
		if (!isLiftLocked) liftStop();
		abortTimeslice();
	}
}

task RollerControls()
{
	bool shouldStop = true;
	for (ever)
	{

		if (ButtonRollerOut)
		{
			rollerOut();
			shouldStop = true;

		} else if (ButtonRollerIn)
		{
			rollerIn();
			shouldStop = false;
		} else
		{
			if (shouldStop) rollerZero();
			else rollerStop();
		}
		abortTimeslice();
	}
}

task FourBarControls()
{
	for (ever)
	{

		while (ButtonFourBarUp)
		{
			if (isFourBarLocked) releaseFourBar();
				fourBarUp();
		}
		while (ButtonFourBarDown)
		{
			if (isFourBarLocked) releaseFourBar();
			fourBarDown();
		}

		if (!isFourBarLocked) fourBarStop();
		abortTimeslice();
	}
}

int coneCount = 0;

/*task SpecialControls()
{
	bool wasPressedIncrement = false;
	bool wasPressedDecrement = false;
	for (ever)
	{
		if (ButtonSpecialPickUp) //aka flat
		{
			holdFourBar(1400);
		}
#ifdef ButtonSpecialDropOffLow
		if (ButtonSpecialDropOffLow)
		{
			holdFourBar(750);
		}
#endif
#ifdef ButtonSpecialDropOffHigh
		if (ButtonSpecialDropOffHigh)
		{
			holdFourBar(2850);
		}
#endif


#ifdef ButtonConeCountIncrement //Added this bunch of ifdef so that even if those buttons are not bound to anything, there is no compiler error
#ifdef ButtonConeCountDecrement


		if (ButtonConeCountIncrement)
		{
			if (!wasPressedIncrement)
			{
				if (coneCount < 10)coneCount++;
				wasPressedIncrement = true;
			}

		} else { wasPressedIncrement = false; }

		if (ButtonConeCountDecrement)
		{
			if (!wasPressedDecrement)
			{
				if (coneCount > 0)
					coneCount--;
				wasPressedDecrement = true;
			}
		} else
		{
			wasPressedDecrement = false;

		}

#ifdef ButtonConeCountReset
		if (ButtonConeCountReset) coneCount = 0;
#endif
#ifdef ButtonSpecialDropOffAdapt
		if (ButtonSpecialDropOffAdapt)
		{
			readyForDroppingCone(coneCount);
		}
#endif
#endif
#endif

		abortTimeslice();
	}
}
*/

#endif
