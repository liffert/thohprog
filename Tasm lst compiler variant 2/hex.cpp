#include "hex.h"
#include <string>
#include <sstream>
#include <math.h>

Hex::Hex() {}


Hex::~Hex(){}

std::string Hex::conv(int number, int zero) {
	hex_num.clear();
	std::ostringstream word;
	word << std::hex << number;
	if (zero != 0) {
		zero = zero - word.str().length();
		for (int i = 0; i < zero; i++) {
			hex_num += "0";
		}
	}
	hex_num += word.str();
	if (hex_num.length() == 1) {
		hex_num.insert(0, "0");
	}
	return hex_num;
}

string Hex::conv_string(string number) {
	int num = 0;
	if (number[number.length() - 1] == 'B') {
		int step = 0;
		for (int i = number.length() - 2; i >= 0; i--) {
			if (number[i] == '1') {
				num = num + pow(2, step);
			}
			step++;
		}
	}
	else if (number[number.length() - 1] == 'H') {
		string c;
		int i = 0;
		if (number[0] == '0') {
			i = 1;
		}
		for (i; i < number.length() - 1; i++) {
			c += number[i];
		}
		for (int i = c.length() - 1; i < 8; i++) {
			c.insert(0, "0");
		}
		return c;
	}
	else if (number[number.length() - 1] == '\'') {
		string c;
		for (int i = 1; i < number.length() - 1; i++) {
			c += conv(number[i]) + " ";
		}
		return c;
	}
	else {
		return conv(atoi(number.c_str()));
	}
	return conv(num);
}
