#pragma once
#include "Header.h"
class Brezenhem {
public:
	Brezenhem() {};
	~Brezenhem() {};
	void line(int x0, int y0, int x1, int y1);
	void circle(int x0, int y0, int radius);
	void set_color();

private:
	int color;
};