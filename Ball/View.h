#pragma once
#include "Header.h"

sf::View view;

void camera(double x, double y) {//функція встановлення камери
	view.setCenter(x + 100, y);
}