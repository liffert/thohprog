#include "JNZ.h"



JNZ::JNZ()
{
}


JNZ::~JNZ()
{
}

void JNZ::Display() {
	ToHEX conv;
	std::cout << conv.convertation(offset, true) << "\t";
	file << conv.convertation(offset, true) << "\t";

	std::cout << "75 ";
	file << "75 ";
	if (get_pointer(F_operand)->addres > offset) {
		int a = get_pointer(F_operand)->addres - offset - 2;
		std::cout << conv.convertation(a, false) << " 90 90 90 90";
		file << conv.convertation(a, false) << " 90 90 90 90";
	}
	else {
		int a = 266 - (offset + get_pointer(F_operand)->addres) + 14;
		std::cout << conv.convertation(a, false);
		file << conv.convertation(a, false);
	}

	std::cout << "\t" << lex << "\t" << F_operand;
	file << "\t" << lex << "\t" << F_operand;
}

int JNZ::control() {
	if (second_entry) {
		if (chek_ava(F_operand) == 0) {
			std::cout << "\t" << lex << "\t" << F_operand;
			file << "\t" << lex << "\t" << F_operand;
			std::cout << "\nERROR";
			file << "\nERROR\n";
		}
		else {
			Display();
			if (offset < get_pointer(F_operand)->addres) {
				offset = offset + 6;
			}
			else {
				offset = offset + 2;
			}
		}
	}
	else {
		if (chek_ava(F_operand) == 0) {
			offset = offset + 6;
		}
		else {
			offset = offset + 2;
		}
	}
	return offset;
}
