#include "CMP.h"



CMP::CMP()
{
}


CMP::~CMP()
{
}
std::string CMP::RM(std::string name, std::string name2) {
	std::string word;
	ModRM temp;
	word = word + temp.get_MOD(name2) + temp.get_REG(name) + temp.get_R_M(name2) + "B";
	ToHEX conv;
	word = conv.operand(word);
	return word;
}
void CMP::Display() {
	bool error = false;
	ToHEX conv;
	std::string word;
	std::string word2;
	std::string temp;
	
	std::cout << conv.convertation(offset, true) << "\t";
	file << conv.convertation(offset, true) << "\t";

	if (!check_reg_error(F_operand)) {
		if (is_8_reg(S_operand)) {
			reconstruction(F_operand, code, DW, ES, DB, address);
			if (!DB) {
				std::cout << "\nERROR\n";
				file << "\nERROR\n";
				return;
			}
			std::cout << "38 ";
			for (int i = 0; i < F_operand.length(); i++) {
				if (F_operand[i] == '[') {
					i++;
					while (F_operand[i] != ']') {
						temp = temp + F_operand[i];
						i++;
					}
					break;
				}
			}
			word = word + temp[0] + temp[1] + temp[2];
			word2 = word2 + temp[4] + temp[5] + temp[6] + temp[7] + temp[8];
			if (word == "EBP") {
				std::cout << "3E: ";
			}
			std::cout << RM(S_operand, "SI+disp16") << " ";
			std::string temp_2;
			ModRM temp;
			temp_2 = word + temp.get_MOD(word2) + temp.get_R_M(word2) + temp.get_REG(word) + "B";
			temp_2 = conv.operand(temp_2);
			std::cout << temp_2 << " " << conv.convertation(address, true) << "r ";
			
		}
		else if (is_32_reg(S_operand)) {
			reconstruction(F_operand, code, DW, ES, DB, address);
			if (DW) {
				std::cout << "\nERROR\n";
				file << "\nERROR\n";
				return;
			}
			else if (DB) {
				std::cout << "\nERROR\n";
				file << "\nERROR\n";
				return;
			}
			std::cout << "39 ";
			for (int i = 0; i < F_operand.length(); i++) {
				if (F_operand[i] == '[') {
					i++;
					while (F_operand[i] != ']') {
						temp = temp + F_operand[i];
						i++;
					}
					break;
				}
			}
			word = word + temp[0] + temp[1] + temp[2];
			word2 = word2 + temp[4] + temp[5] + temp[6] + temp[7] + temp[8];
			if (word == "EBP") {
				std::cout << "3E: ";
			}
			std::cout << RM(S_operand, "SI+disp16") << " ";
			std::string temp_2;
			ModRM temp;
			temp_2 = word + temp.get_MOD(word2) + temp.get_R_M(word2) + temp.get_REG(word) + "B";
			temp_2 = conv.operand(temp_2);
			std::cout << temp_2 << " " << conv.convertation(address, true) << "r";
		}
	}
	else {
		if (is_32_reg(F_operand) && is_32_reg(S_operand)) {
			std::cout << "3B ";
			file << "3B ";
		}
		else if (is_8_reg(F_operand) && is_8_reg(S_operand)) {
			std::cout << "3A ";
			file << "3A ";
		}
		else {
			error = true;
		}
		std::cout << RM(F_operand, S_operand) << "\t";
		file << RM(F_operand, S_operand) << "\t";

	}
	std::cout << lex << "\t" << F_operand << ", " << S_operand;
	file << lex << "\t" << F_operand << ", " << S_operand;
	if (!check_operands_error(count_of_operands)) {
		error = true;
	}
	if (error) {
		std::cout << "\nERROR\n";
		file << "\nERROR\n";
	}
}

int CMP::control() {
	if (second_entry) {
		Display();
	}
	if (!check_operands_error(count_of_operands) || !check_reg_error(S_operand)) {
		std::cout << "\nERORR";
		file << "\nERROR\n";
	}
	if (!check_reg_error(F_operand)) {
		offset = offset + 2 + reconstruction(F_operand);
	}
	offset = offset + 2;//add check ES:
	return offset;
}
