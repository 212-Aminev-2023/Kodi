#include <iostream>
#include <sstream>
#include <string>
#include "field.h"
#include "boundary.h"
#include "bump.h"
#include "control.h"
#include "stone.h"
#include "wood.h"
#include "rover.h"
#include "processor.h"
using namespace std;

//212-Аминев-Рамазан

int main() {
	int time = 0, date = 0;
	string str, line, cmd, logb, logc;
	cout << "Здравствуй, пользователь! Данная программа производит расчет поля и строит маршрут ровера." << endl;
	cout << "Введите имя конфигурационного файла: ";
	cin >> str;
	ifstream cfg(str);
	while (getline(cfg, line)) {
		istringstream iss(line);
		iss >> str;
		if (str == "command_file") {
			iss >> str;
			if (str == "=") {
				iss >> cmd;
			}
		}
		if (str == "log_boundary") {
			iss >> str;
			if (str == "=") {
				iss >> logb;
			}
		}
		if (str == "log_control") {
			iss >> str;
			if (str == "=") {
				iss >> logc;
			}
		}
		if (str == "time") {
			iss >> str;
			if (str == "=") {
				iss >> time;
			}
		}
		if (str == "date") {
			iss >> str;
			if (str == "=") {
				iss >> date;
			}
		}
	}
	boundary *interface = new boundary(cmd, logb, logc, time, date);
	(*interface).body();
	delete interface;
}