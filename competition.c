#pragma config(I2C_Usage, I2C1, i2cSensors)
<<<<<<< HEAD
#pragma config(Sensor, in1,    pot_fourbar,    sensorPotentiometer)
#pragma config(Sensor, in2,    pot_chainbar,   sensorPotentiometer)
=======
#pragma config(Sensor, in1,    pot_fourbar_left, sensorPotentiometer)
#pragma config(Sensor, in3,    pot_fourbar_right, sensorPotentiometer)
#pragma config(Sensor, in5,    pot_chainbar,   sensorPotentiometer)
>>>>>>> NotWorking
#pragma config(Sensor, dgtl2,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           mb_left,       tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_5)
#pragma config(Motor,  port2,           front_left,    tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port3,           front_right,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           fb_left,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           fb_right,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           roller,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           chainbar,      tmotorVex393_MC29, openLoop, reversed)
<<<<<<< HEAD
#pragma config(Motor,  port8,           back_left,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port9,           back_right,    tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
=======
#pragma config(Motor,  port8,           back_left,     tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port9,           back_right,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
>>>>>>> NotWorking
#pragma config(Motor,  port10,          mb_right,      tmotorVex393_HBridge, openLoop, encoderPort, I2C_6)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define competition

#pragma platform(VEX2)


#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

#include "Driver.h"


void pre_auton()
{

<<<<<<< HEAD
  bStopTasksBetweenModes = true;
#include "pre_auton.h"
=======
	bStopTasksBetweenModes = true;
//#include "pre_auton.h"
>>>>>>> NotWorking

}


task autonomous()
{/*
	clearTimer(T1);
	while (time1(T1)<5000){
		moveLeftWheels(50);
		moveRightWheels(50);

}*/
#include "Autonomous.h"
}

task usercontrol()
{
//	stopTask(autonomous);
#include "UserControls.h"
}
