#ifndef __ROUTES_H__
#define __ROUTES_H__

void chassis_stop();
void chassis_reset();

// pause in ms
void pause(int input);

// controlled forward/backward movement
void f_c(int dist, int max_pwr);

// controlled turn
void t_c(int dist, int max_pwr);

// pause and reset chassis encoders
void p_r();

// score the first tower and back up
void route_p1 ();

// score the 2nd tower and back up
void route_p2 ();

void routes () ;

#endif