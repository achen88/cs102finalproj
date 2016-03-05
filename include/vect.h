#ifndef VECT_H
#define VECT_H

#include <cmath>

class Vect {
	public:
		Vect();
		Vect(double x, double y, double z);
		void add(Vect v);
		void mult(Vect v);
		void invert();
		double magnitude();
		void normalize();
		double dot_product(Vect v);
		double angle(Vect v);
		Vect cross_product(Vect v);
		
		double getX() const;
		double getY() const;
		double getZ() const;
		
		void setX(double x);
		void setY(double y);
		void setZ(double z);
		
	private:
		double x;
		double y;
		double z;
};

#endif