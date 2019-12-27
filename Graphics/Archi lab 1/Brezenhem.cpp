#include "Brezenhem.h"

void Brezenhem::line(int x0, int y0, int x1, int y1) {
	const int deltaX = abs(x1 - x0);
	const int deltaY = abs(y1 - y0);
	const int signX = x0 < x1 ? 1 : -1;
	const int signY = y0 < y1 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	gotoxy(x1, y1);
	std::cout << "*";
	while (x0 != x1 || y0 != y1)
	{
		gotoxy(x0, y0);
		std::cout << "*";
		const int error2 = error * 2;
		//
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x0 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y0 += signY;
		}
	}
}

void Brezenhem::circle(int x0, int y0, int radius) {
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		gotoxy(x0 + x, y0 + y);
		std::cout << "*";
		gotoxy(x0 + x, y0 - y);
		std::cout << "*";
		gotoxy(x0 - x, y0 + y);
		std::cout << "*";
		gotoxy(x0 - x, y0 - y);
		std::cout << "*";
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}