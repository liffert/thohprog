#include "ToHEX.h"
#include <string>
#include <sstream>
#include <math.h>

ToHEX::ToHEX() {}


ToHEX::~ToHEX(){}

std::string ToHEX::convertation(int num, bool flag) {
	std::ostringstream word;
	word << std::hex << num;
	if (flag) {
		switch (word.str().length()) {
		case 1:
			hex_num = "000" + word.str();
			break;
		case 2:
			hex_num = "00" + word.str();
			break;
		case 3:
			hex_num = "0" + word.str();
			break;
		case 4:
			hex_num = word.str();
			break;
		default:
			hex_num = word.str();
		}
	}
	else {
		if (word.str().length() == 1) {
			hex_num = "0" + word.str();
		}
		else {
			hex_num = word.str();
		}
	}
	return hex_num;
}

std::string ToHEX::bin_to_hex(std::string num) {
	int number = 0;
	for (int i = 0; i < num.length(); i++) {
		std::string temp;
		temp = temp + num[i];
		int a = atoi(temp.c_str());
		if (a == 1) {
			number = number + pow(2, (num.length() - 1 - i));
		}
		temp.clear();
	}
	std::string temp = convertation(number, false);
	return temp;
}

std::string ToHEX::operand(std::string num) {
	std::string word;
	if (num[num.length() - 1] == 'H') {
		if (num[0] == '0') {
			for (int i = 1; i < num.length() - 1; i++) {
				word = word + num[i];
			}
			return word;
		}
		else {
			return num;
		}
	}
	if (num[num.length() - 1] == 'B') {
		for (int i = 0; i < num.length() - 1; i++) {
			word = word + num[i];
		}
		word = bin_to_hex(word);
		return word;
	}
	word = convertation(atoi(num.c_str()), false);
	return word;
}
int ret_ekw_16_to_10(char s) {
	switch (s) {
	case 'F':
		return 15;
	case 'E':
		return 14;
	case 'D':
		return 13;
	case 'C':
		return 12;
	case 'B':
		return 11;
	case 'A':
		return 10;
	default:
		int a = 0;
		std::string temp;
		temp = temp + s;
		a = atoi(temp.c_str());
		return a;
	}
}
int ToHEX::to10(std::string num) {
	if (num[num.length() - 1] == 'B') {
		int number = 0;
		for (int i = 0; i < num.length() - 1; i++) {
			std::string temp;
			temp = temp + num[i];
			int a = atoi(temp.c_str());
			if (a == 1) {
				number = number + pow(2, (num.length() - 2 - i));
			}
			temp.clear();
		}
		return number;
	}
	else if(num[num.length() - 1] == 'H') {
		int number = 0;
		for (int i = 0; i < num.length() - 1; i++) {
			char temp;
			temp = num[i];
			int a = ret_ekw_16_to_10(temp);
			number = number + a * (pow(16, (num.length() - 2 - i)));
		}
		return number;
	}
	else {
		return atoi(num.c_str());
	}
}

