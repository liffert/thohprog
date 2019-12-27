#pragma once
#include <iostream>
class ToHEX {
public:
	ToHEX();
	~ToHEX();
	std::string convertation(int num, bool flag);
	std::string bin_to_hex(std::string num);
	std::string operand(std::string num);
	int to10(std::string num);
private:
	std::string hex_num;
};

