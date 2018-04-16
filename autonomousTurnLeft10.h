
motor[roller]=ROLLER_POWER;


mg_out(false);
//outOfSize(500,1805);
//moveWheels(49,true,2.2);
moveWheels(26,true,2.2);
wait1Msec(500);
motor[roller]=-ROLLER_POWER; // drop first cone

mobileGoal(900,true,200);

moveWheels(5,true,1);

motor[roller]=ROLLER_POWER;
holdLift(70,25);
holdFourBar(1400,100);
wait1Msec(200);

motor[roller]=ROLLER_ANTIGRAVITY;
holdLift(125);
holdFourBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop second cone
wait1Msec(250);
moveWheels(8,true,2);
wait1Msec(250);
motor[roller]=ROLLER_POWER;

holdLift(50);

holdFourBar(1300,100);

wait1Msec(200);

motor[roller]=ROLLER_ANTIGRAVITY;
holdLift(200);
holdFourBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop third cone

wait1Msec(250);
moveWheels(8,true,1.5);
wait1Msec(250);

motor[roller]=ROLLER_POWER;

holdLift(50);
holdFourBar(1300,100);

wait1Msec(200);

motor[roller]=ROLLER_ANTIGRAVITY;
holdLift(300);
holdFourBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop fourth cone



//moveWheels(-62,true,1.5);//if 3 cones
moveWheels(-49,true,1.5);
wait1Msec(200);
motor[roller]=0;

turn(135);


moveWheels(4,true,2);
wait1Msec(200);

turn(90);
wait1Msec(100);

moveWheels(7,true,2);

mg_out(true);
moveWheels(-18,true,4);
