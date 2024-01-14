#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

class wood {
private:
	double x1;
	double y1;
	double x2;
	double y2;
	double R;
public:
	wood() = default;
	wood(double x1, double y1, double x2, double y2, double R);
	double cylinder(double x0, double y0);
};