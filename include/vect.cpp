#include "vect.h"

//**************** Vector class ****************

//******** class constructors ********
Vect::Vect() {
	x = 0;
	y = 0;
	z = 0;
}

Vect::Vect(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

//******** adds vectors ********
void Vect::add(Vect v) {
	x += v.getX();
	y += v.getY();
	z += v.getZ();
}

//******** multiplies vectors ********
void Vect::mult(Vect v) {
	x *= v.getX();
	y *= v.getY();
	z *= v.getZ();
}

//******** flips vector ********
void Vect::invert() {
	x *= -1;
	y *= -1;
	z *= -1;
}

//******** magnitude of vector ********
double Vect::magnitude() {
	return std::sqrt(x*x + y*y + z*z);
}

//******** normalizes vector ********
void Vect::normalize() {
	double m = magnitude();
	x /= m;
	y /= m;
	z /= m;
}

//******** dot product ********
double Vect::dot_product(Vect v) {
	return x*v.getX() + y*v.getY() + z*v.getZ();
}

//******** angle between vectors ********
double Vect::angle(Vect v) {
	return std::acos(this->dot_product(v)/(this->magnitude()*v.magnitude()));
}

//******** cross product ********
Vect Vect::cross_product(Vect v) {
	Vect w(y*v.getZ() - z*v.getY(),
	       -(x*v.getZ() - z*v.getX()),
	       -(x*v.getY() - y*v.getX()));
	return w;
}

//******** class mutators/accessors ********
double Vect::getX() const { return x; }
double Vect::getY() const { return y; }
double Vect::getZ() const { return z; }

void Vect::setX(double x) { this->x = x; }
void Vect::setY(double y) { this->y = y; }
void Vect::setZ(double z) { this->z = z; }