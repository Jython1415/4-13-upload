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

// controlled forward/backward movement
void f_c(int dist, int max_pwr)
{
  // forward movement
  if (dist > 0)
  {
    // acc 1
    chassis_set(int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB > int(dist/6) * 1);
    chassis_set(int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB > int(dist/6) * 2);
    chassis_set(max_pwr);

    // decc 1
    waitUntil(rot_LB > int(dist/6) * 4);
    chassis_set(int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB > int(dist/6) * 5);
    chassis_set(int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB > dist);
    chassis_stop();
  }
  // backward movement
  else
  {
    // acc 1
    chassis_set(-int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB < int(dist/6) * 1);
    chassis_set(-int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB < int(dist/6) * 2);
    chassis_set(-max_pwr);

    // decc 1
    waitUntil(rot_LB < int(dist/6) * 4);
    chassis_set(-int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB < int(dist/6) * 5);
    chassis_set(-int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB < dist);
    chassis_stop();
  }
}

// controlled turn
void t_c(int dist, int max_pwr)
{
  // forward movement
  if (dist > 0)
  {
    // acc 1
    chassis_set_turn(int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB < -int(dist/6) * 1);
    chassis_set_turn(int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB < -int(dist/6) * 2);
    chassis_set_turn(max_pwr);

    // decc 1
    waitUntil(rot_LB < -int(dist/6) * 4);
    chassis_set_turn(int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB < -int(dist/6) * 5);
    chassis_set_turn(int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB < -dist);
    chassis_stop();
  }
  // backward movement
  else
  {
    // acc 1
    chassis_set_turn(-int(max_pwr/3) * 1);

    // acc 2
    waitUntil(rot_LB > -int(dist/6) * 1);
    chassis_set_turn(-int(max_pwr/3) * 2);

    // cruise
    waitUntil(rot_LB > -int(dist/6) * 2);
    chassis_set_turn(-max_pwr);

    // decc 1
    waitUntil(rot_LB > -int(dist/6) * 4);
    chassis_set_turn(-int(max_pwr/3) * 2);

    // decc 2
    waitUntil(rot_LB > -int(dist/6) * 5);
    chassis_set_turn(-int(max_pwr/3) * 1);

    // stop
    waitUntil(rot_LB > -dist);
    chassis_stop();
  }
}

// pause and reset chassis encoders
void p_r()
{
  pause(500);
  chassis_reset();
}

// score the 1st tower and back up
void route_p1 ()
{
  // score preload
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
  waitUntil(rot_LB > 1250);
  chassis_set(20);
  waitUntil(rot_LB > 2500);
  // stop
  chassis_stop();
  intake_set(20);

  pause(500);

  chassis_reset();

  // turn left
  chassisL_set(-2);
  chassisR_set(20);
  waitUntil(rot_RB > 1000);
  chassis_stop();

  pause(500);

  // forward to the goal (time)
  chassis_set(40);
  pause(1250);
  chassis_stop();

  // shoot (time)
  intake_set(100);
  roller_set(100);
  pause(600);
  // remove blue balls
  rollerT_set(-5);
  rollerB_set(60);
  pause(600);
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
}

// score the 2nd tower and back up
void route_p2 ()
{
  // turn right
  // chassisL_set(5);
  // chassisR_set(-30);
  // waitUntil(rot_RB < -1000);
  // chassisR_set(-20);
  // waitUntil(rot_RB < -1550);
  // chassis_stop();
  t_c(-1000, 50);

  // pause
  pause(500);
  chassis_reset();

  // forward
  f_c(1750, 60);

  p_r(); // reset
  
  // intake
  intake_set(100);
  chassis_set(20);
  waitUntil(rot_LB > 1000);
  // stop
  intake_set(10);
  chassis_stop();

  p_r(); // reset

  // turn left
  t_c(1000, 50);

  // forward to goal
  chassis_set(40);
  pause(1000);
  chassis_stop();

  p_r(); // reset

  // shoot (time)
  intake_set(100);
  roller_set(100);
  pause(600);
  // remove blue balls
  rollerT_set(-5);
  rollerB_set(60);
  pause(250);
  // stop (intake out to avoid descore)
  intake_set(-20);
  roller_set(0);
  // reset encoders
  chassis_reset();
  // back away
  chassis_set(-20);
  waitUntil(rot_LB < -400);
  roller_set(-100);
  intake_set(-100);
  f_c(-1000, 60);
  // outake a bit more
  pause(500);
  // stop outaking
  roller_set(0);
  intake_set(0);
}

void route_1 ()
{
  route_p1();

  p_r(); // reset

  route_p2();

  p_r(); // reset

  // turn right
  t_c(-1000, 50);

  p_r(); // reset

  // forward
  f_c(2500, 60);

  p_r(); // reset

  // forward and intake

}

void route_2 ()
{
  f_c(1000, 60);
}