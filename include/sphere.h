#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "vect.h"
#include <cmath>
#include <iostream>
#include <fstream>

class Sphere {
	public:
		Sphere();
		Sphere(double x, double y, double z, double r, double theta, double phi);
		double getX() const;
		double getY() const;
		double getZ() const;
		double getR() const;
		double getTheta() const;
		double getPhi() const;
		
		void setX(double x);
		void setY(double y);
		void setZ(double z);
		void setR(double r);
		void setTheta(double theta);
		void setPhi(double phi);
		
		void translate(double dx, double dy, double dz);
		void rotate(double dtheta, double dphi);
		
		Color uv_map(Vect collision, int x_size, int y_size, std::ofstream& err);
		
		Color** texture;
		
	private:
		double x;
		double y;
		double z;
		double r;
		double theta;
		double phi;
};

#endif