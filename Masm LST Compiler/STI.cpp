#include "STI.h"


STI::STI() {
}


STI::~STI() {
}

void STI::Display() {
	ToHEX conv;
	std::cout << conv.convertation(offset, true) << "\t" << "FB\t" << lex;
	file << conv.convertation(offset, true) << "\t" << "FB\t" << lex;
}

int STI::control() {
	if (second_entry) {
		Display();
		if (!check_operands_error(count_of_operands)) {
			std::cout << "\nERROR\n";
			file << "\nERROR\n";
		}
	}
	offset++;
	return offset;
}
