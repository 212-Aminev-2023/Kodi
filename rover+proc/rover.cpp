#include "rover.h"

rover::rover(int heading, int clearance, double alpha, double beta, int speed, field& swamp) {
	this->heading = heading;
	this->clearance = clearance;
	this->alpha = alpha;
	this->beta = beta;
	this->speed = speed;
	this->swamp = swamp;
}

rover::rover() {
	heading = 0;
	clearance = 0;
	alpha = 0;
	beta = 0;
	speed = 0;
}

int rover::angles(int x0, int y0, int x, int y) {
    int i, j;
	int xt = (0 < x - x0) - (0 > x - x0);
	int yt = (0 < y - y0) - (0 > y - y0);
	if (xt != 0 && yt != 0) {
		for (i = x0; i <= x; i += xt) {
			for (j = x0; j <= x; j += xt) {
				if (abs(swamp.Pixel[i][j] - swamp.Pixel[i + xt][j + yt]) > alpha) {
					return 0;
				}
				if (abs(swamp.Pixel[i][j] - swamp.Pixel[i - xt][j - yt]) > alpha) {
					return 0;
				}
				if (abs(swamp.Pixel[i][j] - swamp.Pixel[i + xt][j - yt]) > beta) {
					return 0;
				}
				if (abs(swamp.Pixel[i][j] - swamp.Pixel[i - xt][j + yt]) > beta) {
					return 0;
				}
			}
		}
	}
	if (yt == 0) {
		for (i = x0; i <= x; i += xt) {
			if (abs(swamp.Pixel[i][y] - swamp.Pixel[i + xt][y]) > alpha) {
				return 0;
			}
			if (abs(swamp.Pixel[i][y] - swamp.Pixel[i - xt][y]) > alpha) {
				return 0;
			}
			if (abs(swamp.Pixel[i][y] - swamp.Pixel[i][y + 1]) > beta) {
				return 0;
			}
			if (abs(swamp.Pixel[i][y] - swamp.Pixel[i][y - 1]) > beta) {
				return 0;
			}
		}
	}
	if (xt == 0) {
		for (j = y0; j <= y; j += yt) {
			if (abs(swamp.Pixel[x][j] - swamp.Pixel[x][j + yt]) > alpha) {
				return 0;
			}
			if (abs(swamp.Pixel[x][j] - swamp.Pixel[x][j - yt]) > alpha) {
				return 0;
			}
			if (abs(swamp.Pixel[x][j] - swamp.Pixel[x + 1][j]) > beta) {
				return 0;
			}
			if (abs(swamp.Pixel[x][j] - swamp.Pixel[x - 1][j]) > beta) {
				return 0;
			}
		}
	}
        return 1;
}

int rover::sensor(int x0, int y0, int x, int y) {
    int i, j;
	int xt = (0 < x - x0) - (0 > x - x0);
	int yt = (0 < y - y0) - (0 > y - y0);
	if (yt == 0) {
		for (i = x0; i <= x; i += xt) {
			if (swamp.Pixel[i + xt][y] - swamp.Pixel[i][y] > clearance) {
				return 0;
			}
			if (swamp.Pixel[i + xt][y - 1] - swamp.Pixel[i][y - 1] > clearance) {
				return 0;
			}
			if (swamp.Pixel[i + xt][y + 1] - swamp.Pixel[i][y + 1] > clearance) {
				return 0;
			}
		}
	}
	if (xt == 0) {
		for (j = y0; j <= y; j += yt) {
			if (swamp.Pixel[x][j + yt] - swamp.Pixel[x][j] > clearance) {
				return 0;
			}
			if (swamp.Pixel[x - 1][j + yt] - swamp.Pixel[x - 1][j] > clearance) {
				return 0;
			}
			if (swamp.Pixel[x + 1][j + yt] - swamp.Pixel[x + 1][j] > clearance) {
				return 0;
			}
		}
	}
	if (xt != 0 && yt != 0) {
		for (i = x0; i <= x; i += xt) {
			for (j = x0; j <= x; j += xt) {
				if (swamp.Pixel[i - xt][j] - swamp.Pixel[i][j + yt] > clearance) {
					return 0;
				}
				if (swamp.Pixel[i][j] - swamp.Pixel[i + xt][j + yt] > clearance) {
					return 0;
				}
				if (swamp.Pixel[i][j - yt] - swamp.Pixel[i + yt][j] > clearance) {
					return 0;
				}
			}
		}
	}
        return 1;
}