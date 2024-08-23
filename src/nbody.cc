
#include "nbody.h"


Body::Body(){
	pos_x = 0.0;
	pos_y = 0.0;
	pos_z = 0.0;
	vel_x = 0.0;
	vel_y = 0.0;
	vel_z = 0.0;
	acc_x = 0.0;
	acc_y = 0.0;
	acc_z = 0.0;

	n_pos_x = 0.0;
	n_pos_y = 0.0;
	n_pos_z = 0.0;
	n_vel_x = 0.0;
	n_vel_y = 0.0;
	n_vel_z = 0.0;
	n_acc_x = 0.0;
	n_acc_y = 0.0;
	n_acc_z = 0.0;

	mass = 0.0;	
}
	
Body::Body(double x, double y, double z, 
		 double vx, double vy, double vz, 
		 double ax, double ay, double az, double m){
	pos_x = x;
	pos_y = y;
	pos_z = z;
	vel_x = vx;
	vel_y = vy;
	vel_z = vz;
	acc_x = ax;
	acc_y = ay;
	acc_z = az;

	n_pos_x = 0.0;
	n_pos_y = 0.0;
	n_pos_z = 0.0;
	n_vel_x = 0.0;
	n_vel_y = 0.0;
	n_vel_z = 0.0;
	n_acc_x = 0.0;
	n_acc_y = 0.0;
	n_acc_z = 0.0;

	mass = m;
}

uint32_t getRandomNumber(uint32_t n){
	return rand() % n;
}

void Body::randInit(uint32_t width, uint32_t height, uint32_t depth){
	pos_x = (double)getRandomNumber(width);
	pos_y = (double)getRandomNumber(height);
	pos_z = (double)getRandomNumber(depth);

	// mass = (double)getRandomNumber(10000);
	mass = 1.1e+8; // set mass to 1.1 x 100000000 = 110000000Kg = 110000ton = 110Kton
}

void Body::set_pos(double x, double y, double z){
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

void Body::set_vel(double vx, double vy, double vz){
	vel_x = vx;
	vel_y = vy;
	vel_z = vz;
}

void Body::set_acc(double ax, double ay, double az){
	acc_x = ax;
	acc_y = ay;
	acc_z = az;
}

void Body::set_mass(double m){
	mass = m;
}

double Body::get_pos_x(){
	return pos_x;
}

double Body::get_pos_y(){
	return pos_y;
}

double Body::get_pos_z(){
	return pos_z;
}

double Body::get_vel_x(){
	return vel_x;
}

double Body::get_vel_y(){
	return vel_y;
}

double Body::get_vel_z(){
	return vel_z;
}

double Body::get_acc_x(){
	return acc_x;
}

double Body::get_acc_y(){
	return acc_y;
}

double Body::get_acc_z(){
	return acc_z;
}

double Body::get_mass(){
	return mass;
}

void Body::update_pos(){
	pos_x = n_pos_x;
	pos_y = n_pos_y;
	pos_z = n_pos_z;
}

void Body::update_vel(){
	vel_x = n_vel_x;
	vel_y = n_vel_y;
	vel_z = n_vel_z;
}

void Body::update_acc(){
	acc_x = n_acc_x;
	acc_y = n_acc_y;
	acc_z = n_acc_z;
}

void Body::calc_force(Body *target){
	double dx = target->get_pos_x() - pos_x;
	double dy = target->get_pos_y() - pos_y;
	double dz = target->get_pos_z() - pos_z;
	double r = sqrt(dx*dx + dy*dy + dz*dz);
	double f = G * mass * target->get_mass() / (r*r);
	double fx = f * dx / r;
	double fy = f * dy / r;
	double fz = f * dz / r;

	n_acc_x += fx / mass;
	n_acc_y += fy / mass;
	n_acc_z += fz / mass;
}

void Body::update_next_pos(double dt){
	n_pos_x = pos_x + vel_x * dt + 0.5 * acc_x * dt * dt;
	n_pos_y = pos_y + vel_y * dt + 0.5 * acc_y * dt * dt;
	n_pos_z = pos_z + vel_z * dt + 0.5 * acc_z * dt * dt;
}

void Body::update_next_vel(double dt){
	n_vel_x = vel_x + 0.5 * (acc_x + n_acc_x) * dt;
	n_vel_y = vel_y + 0.5 * (acc_y + n_acc_y) * dt;
	n_vel_z = vel_z + 0.5 * (acc_z + n_acc_z) * dt;
}

void Body::print(FILE *fp){
	fprintf(fp, 
			"[Position] x: %f, y: %f, z: %f\n"
			"[Velocity] x: %f, y: %f, z: %f\n"
			"[Acceleration] x: %f, y: %f, z: %f\n"
			"[Mass] %f\n",
			pos_x, pos_y, pos_z,
			vel_x, vel_y, vel_z, acc_x, acc_y, acc_z, mass);
}


