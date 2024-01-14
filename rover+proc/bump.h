#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

class bump {
private:
	double x;
	double y;
	double dispx;
	double dispy;
	double dispxy;
	double h;
public:
	bump() = default;
	bump(double x, double y, double dispx, double dispy, double h);
	double gauss(double x0, double y0);
};