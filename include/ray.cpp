#include "ray.h"

//**************** Ray class ****************

//******** class constructors ********
Ray::Ray(double x, double y, double z, Vect u) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->u = u;
}

Ray::Ray(Vect u, Vect v) {
	this->x = u.getX();
	this->y = u.getY();
	this->z = u.getZ();
	this->u = v;
}

//******** class mutators/accessors ********
double Ray::getX() const { return x; }
double Ray::getY() const { return y; }
double Ray::getZ() const { return z; }
Vect Ray::getU() const { return u; }

void Ray::setX(double x) { this->x = x; }
void Ray::setY(double y) { this->y = y; }
void Ray::setZ(double z) { this->z = z; }
void Ray::setU(Vect u) { this->u = u; }