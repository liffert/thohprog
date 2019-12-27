#include "DDA.h"

void DDA::line(double x1, double y1, double x2, double y2) {
	int i, L, xstart, ystart, xend, yend;
	float dX, dY, x[1000], y[1000];
	xstart = roundf(x1);
	ystart = roundf(y1);
	xend = roundf(x2);
	yend = roundf(y2);
	L = max(abs(xend - xstart), abs(yend - ystart));
	dX = (x2 - x1) / L;
	dY = (y2 - y1) / L;
	i = 0;
	x[i] = x1;
	y[i] = y1;
	i++;
	while (i < L) {
		x[i] = x[i - 1] + dX;
		y[i] = y[i - 1] + dY;
		i++;
	}
	x[i] = x2;
	y[i] = y2;
	i = 0;
	while (i <= L) {
		gotoxy(roundf(x[i]), roundf(y[i]));
		std::cout << "*";
		i++;
	}
}