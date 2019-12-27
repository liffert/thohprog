#include "Get_imm_value.h"
#include <ctype.h>
#include "ToHEX.h"


Get_imm_value::Get_imm_value() {
}


Get_imm_value::~Get_imm_value() {
}

int Get_imm_value::get(std::string num) {
	return reconstruction(num);
}

int Get_imm_value::reconstruction(std::string num) {
	ToHEX conv;
	int a = 0;
	int t = 0;
	char op;
	bool flag_t = false;
	bool flag_a = false;
	std::string temp;
	for (int i = 0; i < num.length(); i++) {
		if (num[i] == '(') {
			i++;
			while (num[i] != ')') {
				temp = temp + num[i];
				i++;
			}
			if (!flag_a) {
				a = reconstruction(temp);
				flag_a = true;
			}
			else {
				t = reconstruction(temp);
				flag_t = true;
			}
			temp.clear();
		}
		if (isxdigit(num[i])) {
			while (isxdigit(num[i])) {
				temp = temp + num[i];
				i++;
			}
			if (num[i] == 'H') {
				temp = temp + num[i];
			}
			else {
				i--;
			}
			if (!flag_a) {
				a = conv.to10(temp);
				flag_a = true;
			}
			else {
				t = conv.to10(temp);
				flag_t = true;
			}
			temp.clear();
		}
		if (flag_t) {
			switch (op) {
			case '+':
				a = a + t;
				flag_t = false;
				break;
			case '-':
				a = a - t;
				flag_t = false;
				break;
			case '*':
				a = a * t;
				flag_t = false;
				break;
			case '/':
				a = a / t;
				flag_t = false;
				break;
			}
		}
		else if (!isspace(num[i]) && !isxdigit(num[i])) {
			op = num[i];
		}
	}
	return a;
}
