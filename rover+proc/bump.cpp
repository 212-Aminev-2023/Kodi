#include "bump.h"

bump::bump(double x, double y, double dispx, double dispy, double h) {
	this->x = x;
	this->y = y;
	this->dispx = dispx;
	this->dispy = dispy;
	this->dispxy = double(rand() % 10000) / 20000 * dispx * dispy;
	this->h = h;
}

double bump::gauss(double x0, double y0) {
	double r = dispxy / (dispx * dispy);
	return h * exp(((x - x0) * (x - x0) / (dispx * dispx) + (y - y0) * (y - y0) / (dispy * dispy) - 2 * r * (x - x0) * (y - y0) / (dispx * dispy)) / (2 * r * r - 2));
}