
motor[roller]=ROLLER_POWER;


mg_out(false);
wait1Msec(500);
moveWheels(49.5,true,2.2);
wait1Msec(200);
mg_in(true);
motor[roller]=-ROLLER_POWER; // drop first cone

moveWheels(5,true,1);

motor[roller]=ROLLER_POWER;
//holdLift(75,30);
fourbarDown();
wait1Msec(100);
motor[roller]=ROLLER_ANTIGRAVITY;
//holdLift(110);
//holdFourBar(2895,70);
motor[roller]=-ROLLER_POWER; //drop second cone


moveWheels(-48.5,true,1.5);//if 2 cones
wait1Msec(200);
motor[roller]=0;

turn(-135);



//holdLift(600);

moveWheels(21.5,true,2.5);
wait1Msec(200);

turn(-92);
wait1Msec(200);

//mobileGoal(2070,false,50,200);

moveWheels(26,true,5);
//mg_mid(false);

wait1Msec(500);


mg_out(false);
moveWheels(-18,true,4);
