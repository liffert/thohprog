#include "Woo.h"

void Woo::line(int x0, int y0, int x1, int y1) {
	int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
	int dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
	if (dx == 0) {
		while (y0 != y1) {
			gotoxy(x0, y0);
			std::cout << "*";
			y0++;
		}
		return;
	}
	if (dy == 0) {
		while (x0 != x1) {
			gotoxy(x0, y0);
			std::cout << "*";
			x0++;
		}
		return;
	}

	if (dy < dx) {
		if (x1 < x0) {
			x1 += x0; x0 = x1 - x0; x1 -= x0;
			y1 += y0; y0 = y1 - y0; y1 -= y0;
		}
		float grad = (float)dy / dx;
		float intery = y0 + grad;
		gotoxy(x0, y0);
		std::cout << "*";

		for (int x = x0 + 1; x < x1; x++) {
			gotoxy(x, intery);
			std::cout << "*";
			gotoxy(x, intery + 1);
			std::cout << "*";
			intery += grad;
		}
		gotoxy(x1, y1);
		std::cout << "*";
	}
	else {
		if (y1 < y0) {
			x1 += x0; x0 = x1 - x0; x1 -= x0;
			y1 += y0; y0 = y1 - y0; y1 -= y0;
		}
		float grad = (float)dx / dy;
		float interx = x0 + grad;
		gotoxy(x0, y0);
		std::cout << "*";

		for (int y = y0 + 1; y < y1; y++) {
			gotoxy(interx, y);
			std::cout << "*";
			gotoxy(interx + 1, y);
			std::cout << "*";
			interx += grad;
		}
		gotoxy(x1, y1);
		std::cout << "*";
	}
}