#ifndef Autonomous
#define Autonomous

#define mb_in(block) mobileGoal(940,block,50)
#define mb_mid(block) mobileGoal(2000,block)
#define mb_out(block) mobileGoal(3290,block)

holdChainBar(600);
holdFourBar(150);
motor[roller]=ROLLER_ANTIGRAVITY;

//mobileGoal(3290);
mb_out(false);

turn(45,5);
wait1Msec(400);
moveWheels(48.5,true,1.25);

wait1Msec(700);

//mobileGoal(940,true);
mb_in(true);
turn(-178,5);
moveWheels(35,true,3); //move back
wait1Msec(300);

turn(45);
wait1Msec(200);

moveWheels(30);
turn(-95);


//mobileGoal(2000,false,50);
mb_mid(false);
wait1Msec(300);
moveWheels(24,true,4);
wait1Msec(200);

moveWheels(-20,5);
wait1Msec(200);
releaseWheels();
#endif
