#include "DEC.h"

enum R32 {
	EAX, ECX, EDX, EBX, EBP, ESI, EDI
};


DEC::DEC() {
}


DEC::~DEC() {
}
std::string DEC::_32(std::string name) {
	ToHEX conv;
	int a = 72;
	if (name == "EAX") {
		a = a + EAX;
		return conv.convertation(a, false);
	}
	if (name == "ECX") {
		a = a + ECX;
		return conv.convertation(a, false);
	}
	if (name == "EDX") {
		a = a + EDX;
		return conv.convertation(a, false);
	}
	if (name == "EBX") {
		a = a + EBX;
		return conv.convertation(a, false);
	}
	if (name == "EBP") {
		a = a + EBP;
		return conv.convertation(a, false);
	}
	if (name == "ESI") {
		a = a + ESI;
		return conv.convertation(a, false);
	}
	if (name == "EDI") {
		a = a + EDI;
		return conv.convertation(a, false);
	}
	return "0";
}
std::string DEC::_8(std::string name) {
	std::string word;
	ModRM temp;
	word = word + temp.get_MOD(name) + temp.get_REG("CL") + temp.get_R_M(name) + "B";
	ToHEX conv;
	word = conv.operand(word);
	return word;
}
void DEC::Display() {
	ToHEX conv;
	if (is_8_reg(F_operand)) {
		std::cout << conv.convertation(offset, true) << "\t" << "FE " << _8(F_operand) << "\t\t" << lex << "\t" << F_operand;
		file << conv.convertation(offset, true) << "\t" << "FE \t" << _8(F_operand) << "\t\t" << lex << "\t" << F_operand;
	}
	else {
		std::cout << conv.convertation(offset, true) << "\t" << _32(F_operand) << "\t\t" << lex << "\t" << F_operand;
		file << conv.convertation(offset, true) << "\t" << _32(F_operand) << "\t\t" << lex << "\t" << F_operand;
	}
}

int DEC::control() {
	if (second_entry) {
		Display();
		if (!check_operands_error(count_of_operands) || !check_reg_error(F_operand)) {
			std::cout << "\nERORR";
			file << "\nERROR\n";
		}
	}
	if (is_32_reg(F_operand)) {
		offset = offset + 1;
	}
	else {
		offset = offset + 2;
	}
	return offset;
}
