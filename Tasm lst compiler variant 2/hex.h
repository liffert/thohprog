#pragma once
#include <iostream>
using namespace std;
class Hex {
public:
	Hex();
	~Hex();
	string conv(int number, int zero = 0);
	string conv_string(string number);
private:
	std::string hex_num;
};

