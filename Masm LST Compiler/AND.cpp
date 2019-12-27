#include "AND.h"



AND::AND(){}


AND::~AND(){}
std::string AND::RM(std::string name) {
	ModRM t;
	ToHEX conv;
	std::string temp;
	std::string word;
	std::string word2;
	for (int i = 0; i < name.length(); i++) {
		if (name[i] == '[') {
			i++;
			while (name[i] != ']') {
				temp = temp + name[i];
				i++;
			}
			break;
		}
	}
	word = word + temp[0] + temp[1] + temp[2];
	word2 = word2 + temp[4] + temp[5] + temp[6] + temp[7] + temp[8];
	temp = t.get_MOD(word2) + t.get_R_M(word2) + t.get_REG(word) + "B";
	temp = conv.operand(temp);
	return temp;
}
void AND::Display() {
	ModRM t;
	ToHEX conv;
	std::cout << conv.convertation(current_offset, true) << "\t";
	file << conv.convertation(current_offset, true) << "\t";
	if (DW) {
		std::cout << "66| ";
		file << "66| ";
	}
	if (ES) {
		std::cout << "26: ";
		file << "26: ";
	}
	if (code) {
		std::cout << "2E: ";
		file << "2E: ";
	}
	if (DB) {
		std::cout << "20 ";
		file << "20 ";
	}
	else {
		std::cout << "21 ";
		file << "21 ";
	}
	if (get_pointer(F_operand) == NULL) {
		if (!ES) {
			if (is_8_reg(S_operand) && DB) {
				if (S_operand != "AL") {
					std::string temp;
					temp = temp + t.get_MOD("DI") + t.get_REG(S_operand) + t.get_R_M("DI") + "B";
					std::cout << conv.operand(temp) << " ";
					file << conv.operand(temp) << " ";
				}
				else {
					std::string temp;
					temp = temp + t.get_MOD("SI+disp16") + t.get_REG(S_operand) + t.get_R_M("SI+disp16") + "B";
					std::cout << conv.operand(temp) << " ";
					file << conv.operand(temp) << " ";
				}
			}
			else {
				std::string temp;
				temp = temp + t.get_MOD("SI+disp16") + t.get_REG(S_operand) + t.get_R_M("SI+disp16") + "B";
				std::cout << conv.operand(temp) << " ";
				file << conv.operand(temp) << " ";
			}
			std::cout << RM(F_operand);
			file << RM(F_operand);
		}
		else {
			std::string w;
			for (int i = 3; i < F_operand.length(); i++) {
				w = w + F_operand[i];
			}
			if (get_pointer(w) == NULL) {
				if (is_8_reg(S_operand) && DB) {
					if (S_operand != "AL") {
						std::string temp;
						temp = temp + t.get_MOD("DI") + t.get_REG(S_operand) + t.get_R_M("DI") + "B";
						std::cout << conv.operand(temp) << " ";
						file << conv.operand(temp) << " ";
					}
					else {
						std::string temp;
						temp = temp + t.get_MOD("SI+disp16") + t.get_REG(S_operand) + t.get_R_M("SI+disp16") + "B";
						std::cout << conv.operand(temp) << " ";
						file << conv.operand(temp) << " ";
					}
				}
				else {
					std::string temp;
					temp = temp + t.get_MOD("SI+disp16") + t.get_REG(S_operand) + t.get_R_M("SI+disp16") + "B";
					std::cout << conv.operand(temp) << " ";
					file << conv.operand(temp) << " ";
				}
				std::cout << RM(F_operand);
				file << RM(F_operand);
			}
			else {
				if (is_8_reg(S_operand) && DB) {
					if (S_operand != "AL") {
						std::string temp;
						temp = temp + t.get_MOD("DI") + t.get_REG(S_operand) + t.get_R_M("DI") + "B";
						std::cout << conv.operand(temp) << " ";
						file << conv.operand(temp) << " ";
					}
					else {
						std::cout << "05 ";
						file << "05 ";
					}
				}
				else {
					std::string temp;
					temp = temp + t.get_MOD("DI") + t.get_REG(S_operand) + t.get_R_M("DI") + "B";
					std::cout << conv.operand(temp) << " ";
					file << conv.operand(temp) << " ";
				}
			}
		}
	}
	else {
		if (is_8_reg(S_operand) && DB) {
			if (S_operand != "AL") {
				std::string temp;
				temp = temp + t.get_MOD("DI") + t.get_REG(S_operand) + t.get_R_M("DI") + "B";
				std::cout << conv.operand(temp) << " ";
				file << conv.operand(temp) << " ";
			}
			else {
				std::cout << "05 ";
				file << "05 ";
			}
		}
		else {
			std::string temp;
			temp = temp + t.get_MOD("DI") + t.get_REG(S_operand) + t.get_R_M("DI") + "B";
			std::cout << conv.operand(temp) << " ";
			file << conv.operand(temp) << " ";
		}
	}
	std::cout << "\t" << lex << "\t" << F_operand << ", " << S_operand << " " << conv.convertation(address, true) << "r";
	file << "\t" << lex << "\t" << F_operand << ", " << S_operand << " " << conv.convertation(address, true) << "r";
}

int AND::control() {
	current_offset = offset;
	offset = offset + 2 + reconstruction(F_operand, code, DW, ES, DB, address);//S_operand 0
	if (second_entry) {
		Display();
		if (!check_operands_error(count_of_operands) || !check_reg_error(S_operand)) {
			std::cout << "\nERROR\n";
			file << "\nERROR\n";
		}
	}
	return offset;
}
