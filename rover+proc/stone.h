#pragma once
#include <cmath>
using namespace std;

class stone {
private:
	double x;
	double y;
	double R;
public:
	stone() = default;
	stone(double x, double y, double R);
	double sphere(double x0, double y0);
};