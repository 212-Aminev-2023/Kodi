#pragma once
#include <time.h>
#include <fstream>
#include <vector>
#include "stone.h"
#include "wood.h"
#include "bump.h"
using namespace std;

class field {
private:
	double x;
	double y;
public:
	vector <bump> G;
	vector <stone> K;
	vector <wood> B;
	int Pixel[128][128];
	field();
	field(double x, double y);
	void generate(int g, int k, int b);
	void calculate();
};