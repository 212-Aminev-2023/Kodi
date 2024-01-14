#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include "rover.h"

class processor {
private:
	int A1;
	int A2;
	int B1;
	int B2;
	rover turtle;
public:
	processor(int A1, int A2, int B1, int B2, rover& turtle);
	processor();
	void route();
};