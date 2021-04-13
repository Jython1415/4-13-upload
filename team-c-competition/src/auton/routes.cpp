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

  vex::task::sleep(500);

  chassis_reset();

  // turn left
  chassisL_set(-5);
  chassisR_set(40);
  waitUntil(rot_RB > 1000);
  chassis_stop();

  vex::task::sleep(500);

  // forward to the goal
  chassis_set(40);
  waitUntil(rot_LB > 1000);
  chassis_stop();
}