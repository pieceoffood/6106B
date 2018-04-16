
motor[roller]=ROLLER_POWER;


mg_out(false);
//outOfSize(500,1805);
moveWheels(49,true,2.2);
wait1Msec(1000);
motor[roller]=-ROLLER_POWER; // drop first cone

mobileGoal(900,true,200);

moveWheels(5,true,1);

motor[roller]=ROLLER_POWER;
holdLift(50,10);
holdFourBar(1400,50);
wait1Msec(100);
motor[roller]=ROLLER_ANTIGRAVITY;
holdLift(110);
holdFourBar(2895,50);

motor[roller]=-ROLLER_POWER; //drop second cone
wait1Msec(150);
moveWheels(8,true,2);

motor[roller]=ROLLER_POWER;

holdLift(50);

holdFourBar(1300,100);

wait1Msec(100);

motor[roller]=ROLLER_ANTIGRAVITY;
holdLift(275);
holdFourBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop second cone



moveWheels(-40,true,1.5);//if 3 cones
//moveWheels(-48,true,1.5);//if 2 cones

wait1Msec(200);

motor[roller]=0;
turn(-45);

moveWheels(-12,true,1);
turn(-90);
//turn(-135);
//turn(-225);
moveWheels(9.5,true,1.5);

mg_out(true);
moveWheels(-18,true,4);
