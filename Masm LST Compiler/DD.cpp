#include "DD.h"



DD::DD() {
}


DD::~DD() {
}

void DD::Display() {
	ToHEX conv;
	std::cout << conv.convertation(offset, true) << "\t" << conv.operand(S_operand) << "\t" << F_operand << "\t" << lex << " " << S_operand;
	file << conv.convertation(offset, true) << "\t" << conv.operand(S_operand) << "\t" << F_operand << "\t" << lex << " " << S_operand;
}

int DD::control() {
	if (second_entry) {
		Display();
		if (!check_operands_error(count_of_operands) || !check_NUM_error(S_operand) || !check_LEN_error(F_operand)) {
			std::cout << "\nERROR\n";
			file << "\nERROR\n";
		}
	}
	offset = offset + 4;
	return offset;
}
