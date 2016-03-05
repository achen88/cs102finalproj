#ifndef PROJECT_MATH_H
#define PROJECT_MATH_H

#include <vector>
#include <cmath>
#include "sphere.h"
#include "ray.h"

bool collision(Ray r, Sphere s);
std::vector<double> solve_collision(Ray r, Sphere s);

#endif