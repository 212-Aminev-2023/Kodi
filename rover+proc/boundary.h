#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "control.h"
using namespace std;

class boundary {
private:
	string cmd;
	string logb;
	control server;
	int time;
	int date;
public:
	boundary(string cmd, string logb, string logc, int time, int date);
	void body();
};