#ifndef RAY_H
#define RAY_H

#include "vect.h"

class Ray {
	public:
		Ray(double x, double y, double z, Vect u);
		Ray(Vect u, Vect v);
		
		double getX() const;
		double getY() const;
		double getZ() const;
		Vect getU() const;
		
		void setX(double x);
		void setY(double y);
		void setZ(double z);
		void setU(Vect u);
		
	private:
		double x;
		double y;
		double z;
		Vect u;
};

#endif