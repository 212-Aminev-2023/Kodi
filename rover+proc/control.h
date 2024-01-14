#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "field.h"
#include "rover.h"
#include "processor.h"
using namespace std;

class control {
private:
	string logc;
	int time;
	int date;
	field* swamp;
	rover* turtle;
	processor* brain;
public:
	control();
	control(string logc, int time, int date);
	void body(double x, double y, int g, int k, int b, int heading, int clearance, double alpha, double beta, int speed, int A1, int A2, int B1, int B2);
};