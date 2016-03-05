#include "sphere.h"

//**************** Sphere class ****************

//******** class constructors ********
Sphere::Sphere() {
	x = 0;
	y = 0;
	z = 0;
	r = 0;
	theta = 0;
	phi = 0;
}

Sphere::Sphere(double x, double y, double z, double r, double theta, double phi) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->theta = theta;
	this->phi = phi;
}

//******** class mutators/accessors ********
double Sphere::getX() const { return x; }
double Sphere::getY() const { return y; }
double Sphere::getZ() const { return z; }
double Sphere::getR() const { return r; }
double Sphere::getTheta() const { return theta; }
double Sphere::getPhi() const { return phi; }

void Sphere::setX(double x) { this->x = x; }
void Sphere::setY(double y) { this->y = y; }
void Sphere::setZ(double z) { this->z = z; }
void Sphere::setR(double r) { this->r = r; }
void Sphere::setTheta(double theta) { this->theta = theta; }
void Sphere::setPhi(double phi) {this->phi = phi; }

//******** move Sphere ********
void Sphere::translate(double dx, double dy, double dz) {
	x += dx;
	y += dy;
	z += dz;
}

//******** rotate Sphere ********
void Sphere::rotate(double dtheta, double dphi) {
	theta += dtheta;
	phi += dphi;
}

//******** uv map texture to sphere, switches from 3D(xyz) to 2D(uv) ********
Color Sphere::uv_map(Vect collision, int x_size, int y_size, std::ofstream& errr) {
	double center_x = x - collision.getX();
	double center_y = y - collision.getY();
	double center_z = z - collision.getZ();
	Vect tmp(center_x, center_y, center_z);
	tmp.normalize();

	Vect rotated_z(0, sin(phi), cos(phi));
	Vect rotated_y(0, cos(phi), -sin(phi));
	Vect rotated_x(1, 0, 0);

	double v = rotated_z.angle(tmp)/M_PI;
	double u = 0.5 + (atan2(rotated_x.dot_product(tmp), rotated_y.dot_product(tmp))+theta)/(2*M_PI);
	u = u - (int) u;
	v = v - (int) v;
	if(u < 0) u += 1;
	if(v < 0) v += 1;

	int X = (int)(u * (x_size));
	int Y = (int)(v * (y_size));
	if((int)(u * (x_size)-.5) <= 0) X++;
	if((int)(v * (y_size)-.5) <= 0) Y++;
	if((int)(u * (x_size)+.5) >= x_size) X--;
	if((int)(v * (y_size)+.5) >= y_size) Y--;

	return texture[Y][X];
}