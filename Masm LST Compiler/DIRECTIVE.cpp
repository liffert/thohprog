#include "DIRECTIVE.h"



DIRECTIVE::DIRECTIVE()
{
}


DIRECTIVE::~DIRECTIVE()
{
}

void DIRECTIVE::Display() {
	if (lex == "END") {
		std::cout << "\t" << F_operand << "\t" << lex;
		file << "\t" << F_operand << "\t" << lex;
		return;
	}
	ToHEX conv;
	std::cout << conv.convertation(offset, true) << "\t" << F_operand << "\t" << lex;
	file << conv.convertation(offset, true) << "\t" << F_operand << "\t" << lex;
}

int DIRECTIVE::control() {
	if (second_entry) {
		Display();
	}
	if (lex == "ENDS") {
		offset = 0;
	}
	list* temp = get_pointer(F_operand);
	if (temp != NULL){
		temp->segment = true;
	}
	return offset;
}
