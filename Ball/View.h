#pragma once
#include "Header.h"

sf::View view;

void camera(double x, double y) {//������� ������������ ������
	view.setCenter(x + 100, y);
}