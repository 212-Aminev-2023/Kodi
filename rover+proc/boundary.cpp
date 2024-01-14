#include "boundary.h"

boundary::boundary(string cmd, string logb, string logc, int time, int date) {
	this->cmd = cmd;
	this->logb = logb;
	this->time = time;
	this->date = date;
	this->server = control(logc, time, date);
}

void boundary::body() {
	string str,line;
	double x = 10, y = 10, alpha = 0, beta = 0;
	int g = 0, k = 0, b = 0, i = 0;
	int heading = 0, clearance = 0, speed = 0, A1 = 0, A2 = 0, B1 = 0, B2 = 0;
	ofstream logb(this->logb);
	ifstream cmd(this->cmd);
	while (getline(cmd, line)) {
		istringstream iss(line);
		iss >> str;
		if (str == "field") {
			iss >> x;
			iss >> y;
			logb << "sent field" << endl;
			i++;
		}
		if (str == "generate") {
			iss >> g;
			iss >> k;
			iss >> b;
			logb << "sent generate" << endl;
			i++;
		}
		if (str == "calculate") {
			logb << "sent calculate" << endl;
			i++;
		}
		if (str == "rover") {
			iss >> heading;
			iss >> clearance;
			iss >> alpha;
			iss >> beta;
			iss >> speed;
			logb << "sent rover" << endl;
			i++;
		}
		if (str == "processor") {
			iss >> A1;
			iss >> A2;
			iss >> B1;
			iss >> B2;
			logb << "sent processor" << endl;
			i++;
		}
	}
	if (i < 5) {
		logb << "ERROR: in command file not enough commands" << endl;
	}
	server.body(x, y, g, k, b, heading, clearance, alpha, beta, speed, A1, A2, B1, B2);
}