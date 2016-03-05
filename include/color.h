#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
	public:
		Color();
		Color(double r, double g, double b);
		Color(const Color& c);
		void scale(double factor);
		double getR() const;
		double getG() const;
		double getB() const;
		void setR(double r);
		void setG(double g);
		void setB(double b);
		
	private:
		double r;
		double g;
		double b;
};

#endif