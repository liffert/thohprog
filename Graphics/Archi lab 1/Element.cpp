#include "Element.h"

void Kva::print() {
	Brezenhem temp;
	temp.line(Bias, YBias, Bias + 10, YBias);
	temp.line(Bias, YBias, Bias, YBias + 15);
	temp.line(Bias, YBias + 15 , Bias + 10, YBias + 15);
	temp.line(Bias + 10, YBias, Bias + 10, YBias + 15);


	int bias = (11 - name.length())/2;
	gotoxy(Bias + bias, YBias + 7);
	std::cout << name;
}

void Element::on() {
	SetConsoleTextAttribute(hStdOut, on_color);
	this->print();
	SetConsoleTextAttribute(hStdOut, stop_color);
}

void Element::stop() {
	this->print();
}

void Element::blink() {
	bool flag = true;
	int start = clock();
	while (1) {
		if ((clock() - start) / CLOCKS_PER_SEC > 1) {
			start = clock();
			if (flag) {
				flag = false;
				this->on();
			}
			else {
				this->stop();
				flag = true;
			}
		}
	}
}

void Line::on() {
	SetConsoleTextAttribute(hStdOut, on_color);
	this->print();
	if (right) {
		this->right_arrow();
	}
	if (left) {
		this->left_arrow();
	}
	SetConsoleTextAttribute(hStdOut, stop_color);
}

void Line::stop() {
	this->print();
	if (right) {
		this->right_arrow();
	}
	if (left) {
		this->left_arrow();
	}
}

void Line::print() {
	Brezenhem temp;
	if (Horizontal) {
		temp.line(startX, startY, startX + length, startY);
		gotoxy(startX + (length - name.length()) / 2, startY - 1);
		std::cout << name;
	}
	else {
		temp.line(startX, startY, startX, startY + length);
		gotoxy(startX + 1, startY + (length - name.length()) / 2);
		std::cout << name;
	}
}

void Line::left_arrow() {
	if (Horizontal) {
		gotoxy(startX + 1, startY - 1);
		std::cout << "*";
		gotoxy(startX + 1, startY + 1);
		std::cout << "*";
	}
	else {
		gotoxy(startX - 1, startY + 1);
		std::cout << "*";
		gotoxy(startX + 1, startY + 1);
		std::cout << "*";
	}
	left = true;
}

void Line::right_arrow() {
	if (Horizontal) {
		gotoxy(startX + length - 1, startY - 1);
		std::cout << "*";
		gotoxy(startX + length - 1, startY + 1);
		std::cout << "*";
	}
	else {
		gotoxy(startX - 1, startY + length - 1);
		std::cout << "*";
		gotoxy(startX + 1, startY + length - 1);
		std::cout << "*";
	}
	right = true;
}
