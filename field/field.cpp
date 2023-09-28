#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

// 212-Aminev-Ramazan

class bump {
private:
	double x;
	double y;
	double dispx;
	double dispy;
	double dispxy;
	double h;
public:
	bump() = default;
	bump(double x, double y, double dispx, double dispy, double h);
	double gauss(double x0, double y0);
};

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

class wood {
private:
	double x1;
	double y1;
	double x2;
	double y2;
	double R;
public:
	wood() = default;
	wood(double x1, double y1, double x2, double y2, double R);
	double cylinder(double x0, double y0);
};

class field {
private:
	double x;
	double y;
public:
	vector <bump> G;
	vector <stone> K;
	vector <wood> B;
	field(double x, double y);
	void generate(int g, int k, int b);
	void calculate();
};

int main() {
	double x0, y0;
	int g, k, b;
	setlocale(LC_ALL, "Russian");
	cout << "Здравствуй, пользователь! Данная пораграмма производит расчет поля." << endl;
	cout << "Введите размер поля по x: ";
	cin >> x0;
	cout << "Введите размер поля по y: ";
	cin >> y0;
	cout << "Введите количество горок: ";
	cin >> g;
	cout << "Введите количество камней: ";
	cin >> k;
	cout << "Введите количество бревен: ";
	cin >> b;
	field F(x0, y0);
	F.generate(g, k, b);
	F.calculate();
	cout << "Поверхность находится в файле out.txt";
}

bump::bump(double x, double y, double dispx, double dispy, double h) {
	srand(time(NULL));
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

field::field(double x, double y) {
	this->x = x;
	this->y = y;
}

stone::stone(double x, double y, double R) {
	this->x = x;
	this->y = y;
	this->R = R;
}

double stone::sphere(double x0, double y0) {
	if (R * R - (x - x0) * (x - x0) - (y - y0) * (y - y0) > 0) {
		return sqrt(R * R - (x - x0) * (x - x0) - (y - y0) * (y - y0));
	}
	return 0;
}

wood::wood(double x1, double y1, double x2, double y2, double R) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->R = R;
}

double wood::cylinder(double x0, double y0) {
	double k = (y2 - y1) / (x2 - x1);
	double b = -x1 * k + y1;
	double A = y2 - y1;
	double B = x1 - x2;
	double D = A * A + B * B;
	double C1 = (-y1 * B - x1 * A);
	double C2 = B * (x1 + x2) / 2 - A * (y1 + y2) / 2;
	double d1 = abs(A * x0 + B * y0 + C1) / sqrt(D);
	double d2 = abs(-B * x0 + A * y0 + C2) / sqrt(D);
	if (R * R > d1 * d1 && D / 4 > d2 * d2) {
		return sqrt(R * R - d1 * d1);
	}
	return 0;
}

void field::generate(int g, int k, int b) {
	double x, y, dispx, dispy, h, R, x2, y2;
	int i;
	srand(time(NULL));
	for (i = 0; i < g; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		dispx = double(rand() % 10000) / 10000;
		dispy = double(rand() % 10000) / 10000;
		h = (double(rand() % 10000) / 10000 - 0.3) * sqrt(this->x * this->y);
		G.push_back(bump(x, y, dispx, dispy, h));
	}
	for (i = 0; i < k; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		R = double(rand() % 10000) / 10000;
		K.push_back(stone(x, y, R));
	}
	for (i = 0; i < b; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		x2 = double(rand() % 10000) / 10000 * this->x;
		y2 = double(rand() % 10000) / 10000 * this->y;
		R = double(rand() % 10000) / 10000 + 0.1;
		B.push_back(wood(x, y, x2, y2, R));
	}
}

void field::calculate() {
	int k;
	double h;
	ofstream fout("out.txt");
	for (double i = 0.0; i <= x; i += x / 100) {
		for (double j = 0.0; j <= y; j += y / 100) {
			h = 0;
			for (k = 0; k < G.size(); k++) {
				h += G[k].gauss(i, j);
			}
			for (k = 0; k < K.size(); k++) {
				h += K[k].sphere(i, j);
			}
			for (k = 0; k < B.size(); k++) {
				h += B[k].cylinder(i, j);
			}
			fout << i << " " << j << " " << h << endl;
		}
		fout << endl;
	}
}
