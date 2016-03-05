#include "project_math.h"

//**************** project math functions ****************

//******** test collision ********
bool collision(Ray r, Sphere s) {
	double a, b, c;
	double x1 = s.getX() - r.getX();
	double y1 = s.getY() - r.getY();
	double z1 = s.getZ() - r.getZ();
	a = r.getU().getX()*r.getU().getX() + r.getU().getY()*r.getU().getY() + r.getU().getZ()*r.getU().getZ();
	b = -2 * x1 * r.getU().getX() - 2 * y1 * r.getU().getY() - 2 * z1 * r.getU().getZ();
	c = x1*x1 + y1*y1 + z1*z1 - s.getR()*s.getR();
	return (b*b - 4*a*c >= 0);
}

//******** solve collision ********
std::vector<double> solve_collision(Ray r, Sphere s) { //Keeping it simple :(, wasted cycles
	std::vector<double> solution(2, 0);
	double a, b, c;
	double x1 = s.getX() - r.getX();
	double y1 = s.getY() - r.getY();
	double z1 = s.getZ() - r.getZ();
	a = r.getU().getX()*r.getU().getX() + r.getU().getY()*r.getU().getY() + r.getU().getZ()*r.getU().getZ();
	b = -2 * x1 * r.getU().getX() - 2 * y1 * r.getU().getY() - 2 * z1 * r.getU().getZ();
	c = x1*x1 + y1*y1 + z1*z1 - s.getR()*s.getR();
	solution[0] = (-b - std::sqrt(b*b - 4*a*c))/(2*a);
	solution[1] = (-b + std::sqrt(b*b - 4*a*c))/(2*a);
	return solution;
}