#include "field.h"

field::field() {
	x = 0;
	y = 0;
	Pixel[0][0] = 0;
}

field::field(double x, double y) {
	this->x = x;
	this->y = y;
	Pixel[0][0] = 0;
}

void field::generate(int g, int k, int b) {
	double x, y, dispx, dispy, h, R, x2, y2;
	int i;
	srand(time(NULL));
	for (i = 0; i < g; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		dispx = double(rand() % 10000) / 10000 + 0.1;
		dispy = double(rand() % 10000) / 10000 + 0.1;
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
		R = double(rand() % 10000) / 20000 + 0.1;
		B.push_back(wood(x, y, x2, y2, R));
	}
}

void field::calculate() {
	unsigned int k;
	double h;
	ofstream fout("field.txt");
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			double x = i * this->x / 128;
			double y = j * this->y / 128;
			h = 0;
			for (k = 0; k < G.size(); k++) {
				h += G[k].gauss(x, y);
			}
			for (k = 0; k < K.size(); k++) {
				h += K[k].sphere(x, y);
			}
			for (k = 0; k < B.size(); k++) {
				h += B[k].cylinder(x, y);
			}
			fout << x << " " << y << " " << h << endl;
			Pixel[i][j] = 128 * h / sqrt(this->x * this->y);
		}
		fout << endl;
	}
}