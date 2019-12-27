#pragma once
#include "Header.h"
#include <ctime>


class Test {
public:
	Test() {}
	~Test() {}
	std::vector<double> test();

private:
	int times[12];
	double get_avarage();
	int get_max(int Array[], int N);
	int get_min(int Array[], int N);
};

