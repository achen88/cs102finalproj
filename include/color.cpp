#include "color.h"

//**************** Color class ****************

//******** class constructors ********
Color::Color() {
	r = 0;
	g = 0;
	b = 0;
}

Color::Color(double r, double g, double b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color(const Color& c) {
	r = c.getR();
	g = c.getG();
	b = c.getB();
}

//******** scale color ********
void Color::scale(double factor) {
	r *= factor;
	g *= factor;
	b *= factor;
}

//******** class mutators/accessors ********
double Color::getR() const { return r; }
double Color::getG() const { return g; }
double Color::getB() const { return b; }
void Color::setR(double r) { this->r = r; }
void Color::setG(double g) { this->g = g; }
void Color::setB(double b) { this->b = b; }