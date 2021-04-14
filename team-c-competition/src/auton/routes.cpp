#include "vex.h"
#include "robot-config.h"
#include "motors.h"

#define rot_LB chassisLB.rotation(vex::rotationUnits::raw)
#define rot_RB chassisRB.rotation(vex::rotationUnits::raw)

void chassis_stop()
{
  chassis_set(0);
}
void chassis_reset()
{
  chassisLF.resetRotation();
  chassisLB.resetRotation();
  chassisRF.resetRotation();
  chassisRB.resetRotation();
}

// pause in ms
void pause(int input)
{
  vex::task::sleep(input);
}

void routes ()
{
  rollerB_set(100);
  waitUntil(rollerB.rotation(vex::rotationUnits::deg) > 180);
  rollerB_set(0);

  // go forward 400
  chassis_set(30);
  waitUntil(rot_LB > 200);
  chassis_set(60);
  waitUntil(rot_LB > 400);
  // intake until 750
  intake_set(100);
  waitUntil(rot_LB > 2000);
  // stop
  chassis_stop();
  intake_set(20);

  pause(500);

  chassis_reset();

  // turn left
  chassisL_set(-2);
  chassisR_set(20);
  waitUntil(rot_RB > 950);
  chassis_stop();

  pause(500);

  // forward to the goal (time)
  chassis_set(40);
  pause(1000);
  chassis_stop();

  // shoot (time)
  intake_set(100);
  roller_set(100);
  pause(600);
  // remove blue balls
  rollerT_set(-5);
  rollerB_set(60);
  pause(400);
  // stop (intake out to avoid descore)
  intake_set(-20);
  roller_set(0);
  // reset encoders
  chassis_reset();
  // back away
  chassis_set(-40);
  waitUntil(rot_LB < -400);
  roller_set(-100);
  intake_set(-100);
  waitUntil(rot_LB < -1000);
  // stop
  chassis_stop();
  // outake a bit more
  pause(500);
  // stop outaking
  roller_set(0);
  intake_set(0);

  // reset
  pause(500);
  chassis_reset();

  // turn right
  chassisL_set(5);
  chassisR_set(-30);
  waitUntil(rot_RB < -1000);
  chassisR_set(-20);
  waitUntil(rot_RB < -1500);
  chassis_stop();

  // pause
  pause(500);
  chassis_reset();

  // forward
  chassis_set(20);
  waitUntil(rot_LB > 500);
  chassis_set(40);
  waitUntil(rot_LB > 1500);
  // intake
  intake_set(100);
  waitUntil(rot_LB > 2500);
  chassis_set(20);
  waitUntil(rot_LB > 3000);
  // stop
  intake_set(10);
  chassis_stop();

  // turn left
  // chassisL_set()
}