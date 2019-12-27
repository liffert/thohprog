#include "OR.h"



OR::OR() {
}


OR::~OR() {
}
std::string OR::RM(std::string name) {
	std::string word;
	ModRM temp;
	word = word + temp.get_MOD(name) + temp.get_REG("CL") + temp.get_R_M(name) + "B";
	ToHEX conv;
	word = conv.operand(word);
	return word;
}
void OR::Display() {
	ToHEX conv;
	Get_imm_value get;
	std::cout << conv.convertation(offset, true) << "\t";
	file << conv.convertation(offset, true) << "\t";

	if (is_32_reg(F_operand)) {
		if (F_operand == "EAX") {
			std::cout << "0D ";
			file << "0D ";
		}
		else {
			std::cout << "81 ";
			file << "81 ";
		}
	}
	else if (is_8_reg(F_operand)) {
		if (F_operand == "AL") {
			std::cout << "0C ";
			file << "0C ";
		}
		else {
			std::cout << "80 ";
			file << "80 ";
		}
	}
	else {

	}
	if (F_operand != "AL") {
		std::cout << RM(F_operand);
		file << RM(F_operand);
	}
	std::cout << "\t" << lex << "\t" << F_operand << ", " << S_operand << "\t" << conv.convertation(get.get(S_operand), false);
	file << "\t" << lex << "\t" << F_operand << ", " << S_operand << "\t" << conv.convertation(get.get(S_operand), false);;
}

int OR::control(){
	if (second_entry) {
		Display();
		if (!check_operands_error(count_of_operands) || !check_reg_error(F_operand)) {
			std::cout << "\nERORR";
			file << "\nERROR\n";
		}
	}
	if (is_32_reg(F_operand)) {
		offset = offset + 2 + 4;
	}
	else {
		if (F_operand != "AL") {
			offset = offset + 3;
		}
		else {
			offset = offset + 2;
		}
	}
	return offset;
}
