
motor[roller]=ROLLER_POWER;

mg_out(false);
holdLift(225);
moveWheels(47.5,true,1);
holdFourBar(1700);
wait1Msec(400);
motor[roller]=-ROLLER_POWER;
wait1Msec(200);
mg_in(true);

moveWheels(3,true,1);

motor[roller]=ROLLER_POWER;

holdLift(50);
fourbarBottom(true);
wait1Msec(200);
holdLift(250);
fourbarTop(true);
wait1Msec(100);
motor[roller]=-ROLLER_POWER;
moveWheels(7,true,1);

motor[roller]=ROLLER_POWER;

holdLift(50);
fourbarBottom(true);
wait1Msec(200);

moveWheels(-10,true,1.5);
holdLift(350);
fourbarTop(true);


moveWheels(-52,true,1.5);//if 2 cones
wait1Msec(200);
fourbarTop();
motor[roller]=-ROLLER_POWER;

turn(135);
motor[roller]=0;




//holdLift(600);

moveWheels(22,true,2.5);
wait1Msec(200);

turn(92);
wait1Msec(200);
holdLift(450);
//mobileGoal(2070,false,50,200);

moveWheels(26,true,10);
mg_mid(false);

wait1Msec(1000);


mg_out(false);
moveWheels(-18,true,4);
