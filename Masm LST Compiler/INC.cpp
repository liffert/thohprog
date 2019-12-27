#include "INC.h"



INC::INC()
{
}


INC::~INC()
{
}
std::string INC::RM(std::string name) {
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
void INC::Display() {
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
		std::cout << "FE ";
		file << "FE ";
	}
	else {
		std::cout << "FF ";
		file << "FF ";
	}
	if (get_pointer(F_operand)!= NULL) {
		std::cout << "05 ";
		file << "05 ";
	}
	else {
		if (!ES) {
			std::cout << "84 " << RM(F_operand);
			file << "84 " << RM(F_operand);
		}
		else {
			std::string w;
			for (int i = 3; i < F_operand.length(); i++) {
				w = w + F_operand[i];
			}
			if (get_pointer(w) == NULL) {
				std::cout << "84 " << RM(F_operand);
				file << "84 " << RM(F_operand);
			}
			else {
				std::cout << "05 ";
				file << "05 ";
			}
		}
	}
	std::cout << "\t" << lex << "\t" << F_operand << "\t" << conv.convertation(address, true) + "r";
	file << "\t" << lex << "\t" << F_operand << "\t" << conv.convertation(address, true) + "r";
}

int INC::control() {
	current_offset = offset;
	offset = offset + 2 + reconstruction(F_operand, code, DW, ES, DB, address);
	if (DW) {
		offset = offset + 2;
	}
	if (second_entry) {
		Display();
		if (!check_operands_error(count_of_operands)) {
			std::cout << "\nERROR\n";
			file << "\nERROR\n";
		}
	}
	return offset;
}
