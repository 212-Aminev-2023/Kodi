#include "control.h"

control::control() {
	date = 0;
	time = 0;
}

control::control(string logc, int time, int date) {
	this->logc = logc;
	this->time = time;
	this->date = date;
}

void control::body(double x, double y, int g, int k, int b, int heading, int clearance, double alpha, double beta, int speed, int A1, int A2, int B1, int B2) {
	ofstream logc(this->logc);
	logc << "launched field" << endl;
	swamp = new field(x, y);
	logc << "launched generate" << endl;
	(*swamp).generate(g, k, b);
	logc << "launched calculate" << endl;
	(*swamp).calculate();
	logc << "launched rover" << endl;
	turtle = new rover(heading, clearance, alpha, beta, speed, *swamp);
	logc << "launched processor" << endl;
	brain = new processor(A1, A2, B1, B2, *turtle);
	(*brain).route();
	delete swamp;
	delete turtle;
	delete brain;
}