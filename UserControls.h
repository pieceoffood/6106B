#ifndef userControls
#define userControls

// ------------Driver Control Codes-------------
/*
while(not((vexRT[Btn7UXmtr2]==1)&(vexRT[Btn5DXmtr2]==1)&(vexRT[Btn6DXmtr2]==1)&(vexRT[Btn8UXmtr2]==1)))
{

}
while(not((vexRT[Btn5UXmtr2]==1)&(vexRT[Btn6UXmtr2]==1)))
{

}
&*/
//startTask (SpecialControls);
startTask (WheelControls);
startTask (MobileGoalControls);
startTask (LiftControls);
startTask (RollerControls);
startTask (FourBarControls);

while (true)
{
//so the task doesn't stop
}


// ------------END Driver Control Main Codes-----------

#endif
