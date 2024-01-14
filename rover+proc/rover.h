#pragma once
#include "field.h"

class rover {
private:
	int heading;
	int clearance;
	double alpha;
	double beta;
	int speed;
public:
	field swamp;
	rover(int heading, int clearance, double alpha, double beta, int speed, field& swamp);
	rover();
	int sensor(int x0, int y0, int x, int y);
	int angles(int x0, int y0, int x, int y);
};