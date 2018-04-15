
motor[roller]=ROLLER_POWER;


mg_out(false);
outOfSize(500,1805);
moveWheels(49,true,2.2);
wait1Msec(200);
motor[roller]=-ROLLER_POWER; // drop first cone

mobileGoal(900,true,200);

moveWheels(5,true,1);

motor[roller]=ROLLER_POWER;
//holdLift(70,25);
holdFourBar(1400,50);
wait1Msec(100);
motor[roller]=ROLLER_ANTIGRAVITY;
holdLift(110);
holdFourBar(2895,120);
motor[roller]=-ROLLER_POWER; //drop second cone
//releaseLift();

moveWheels(-48,true,1.5);//if 2 cones
wait1Msec(200);
motor[roller]=0;

turn(135);



//holdLift(600);

moveWheels(22.5,true,2.5);
wait1Msec(200);

turn(97);
wait1Msec(200);

mobileGoal(2070,false,50,200);
moveWheels(26,true,4);
//mg_mid(false);
mobileGoal(2500);
wait1Msec(300);


moveWheels(-18,true,2);
//finish first mobile goal (22 points)

mg_mid(false);
wait1Msec(400);
turn(90);
wait1Msec(200);

moveWheels(15,true,2); // move in 5 point zone
wait1Msec(300);
mg_out(false);
turn(90);

wait1Msec(300);

//mg_out(true);
moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mg_in(true);  // take the mobile goal
wait1Msec(200);

turn(-180);
wait1Msec(500);
mg_mid(false);
moveWheels(30,true,1.5);
mobileGoal(1800,false);
//wait1Msec(600);
//finish second mobile goal (32 points)
moveWheels(-7,true,1,false);
wait1Msec(400);

turn(182);
wait1Msec(500);
mg_out(false);
moveWheels(42*sqrt(2)-4,true,2);

mg_in(true); // take the mobile goal
mg_mid(false);
moveWheels(36*sqrt(2)-2,true,2);
mobileGoal(1800,false);
//finish third mobile goal (42 points)

moveWheels(-3,true,1);
wait1Msec(200);
turn(-124);

mg_out(false);
wait1Msec(300);

moveWheels(51,true,2);
wait1Msec(400);
//turn(-10);
//wait1Msec(500);
//moveWheels(12,true,2);
mg_in(true);
wait1Msec(200);

moveWheels(-54,true,5);
wait1Msec(400);

turn(47,40);
moveWheels(-12*sqrt(2)+8,true,1.5);

//holdFourBar(600);

wait1Msec(300);
//holdLift(400);
turn(90,20);

mobileGoal(2270,false,80);
moveWheels(25.5,true,4.5);
mg_mid(false);

wait1Msec(400);


mg_out(false);
moveWheels(-18,true,2);
// finish fourth mobile goal (62 points)


mg_mid(false);
wait1Msec(400);
turn(90);
wait1Msec(300);

moveWheels(12.75,true,2); // move in 5 point zone
wait1Msec(400);
mg_out(false);
turn(90);

wait1Msec(400);

moveWheels(24,false,2); // go to mobile goal
wait1Msec(300);
mg_in(true);  // take the mobile goal
wait1Msec(300);

turn(-182,20);
wait1Msec(400);
mg_mid(false);
moveWheels(30,true,1.5);
mobileGoal(1800,false);
//wait1Msec(600);
//finish fifth mobile goal (72 points)
moveWheels(-7,true,1,false);
wait1Msec(200);

turn(182);
wait1Msec(400);
mg_out(false);
moveWheels(42*sqrt(2)-2,true,2);

//mg_in(true); // take the mobile goal
mg_mid(false);
moveWheels(36*sqrt(2)-2,true,2);
mobileGoal(1800,false);
//finish sixth mobile goal (82 points)
