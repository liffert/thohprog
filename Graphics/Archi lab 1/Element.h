#pragma once
#include "Header.h"
#include "Brezenhem.h"
#include <thread>


class Element {
public:
	virtual void on();
	virtual void print() {};
	virtual void stop();
	void blink();
protected:
	std::string name;
	int stop_color = 7;
	int on_color = 3;
};

class Kva : public Element {
public:
	Kva(int bias, int Ybias, std::string Name) {
		Bias = bias;
		YBias = Ybias;
		name = Name;
	}
	~Kva() {}
	void print() override;

private:
	int Bias;
	int YBias;
};

class Line : public Element {
public:
	Line(int X, int Y, int len, bool horizontal, std::string Name) {
		startX = X;
		startY = Y;
		length = len;
		Horizontal = horizontal;
		name = Name;
	}
	~Line() {}

	void print() override;
	void on() override;
	void stop() override;
	void left_arrow();
	void right_arrow();

private:
	int startY;
	int startX;
	int length;
	bool Horizontal;

	bool left = false;
	bool right = false;
};

