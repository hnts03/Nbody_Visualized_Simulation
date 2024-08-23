

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


// These Macros will move to "main.cc" file
// The simulation will be created by main.cc file
#define N 1000
#define G 6.674e-11
#define deltaT 0.1			// This variable will given by argument
#define MAX_STEP 1000	// This variable will given by argument

class Body {
  public:
	Body();
	Body(double x, double y, double z, 
		 double vx, double vy, double vz, 
		 double ax, double ay, double az, double m);

	void randInit(uint32_t width, uint32_t height, uint32_t depth);

	void set_pos(double x, double y, double z);
	void set_vel(double vx, double vy, double vz);
	void set_acc(double ax, double ay, double az);
	void set_mass(double m);

	double get_acc_x();
	double get_acc_y();
	double get_acc_z();

	double get_pos_x();
	double get_pos_y();
	double get_pos_z();

	double get_vel_x();
	double get_vel_y();
	double get_vel_z();

	double get_mass();

	void update_pos();
	void update_vel();
	void update_acc();

	void update_next_pos(double dt);
	void update_next_vel(double dt);

	void calc_force(Body *target);

	void print(FILE *fp);
	

  private:
	double pos_x, pos_y, pos_z;
	double vel_x, vel_y, vel_z;
	double acc_x, acc_y, acc_z;

	double n_pos_x, n_pos_y, n_pos_z;
	double n_vel_x, n_vel_y, n_vel_z;
	double n_acc_x, n_acc_y, n_acc_z;

	double mass;

};
