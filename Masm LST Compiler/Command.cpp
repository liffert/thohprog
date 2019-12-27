#include "Command.h"
#include "ADD.h"
#include "AND.h"
#include "CMP.h"
#include "DB.h"
#include "DD.h"
#include "DEC.h"
#include "DIRECTIVE.h"
#include "DW.h"
#include "INC.h"
#include "JNZ.h"
#include "MOV.h"
#include "OR.h"
#include "STI.h"
std::string reg[] = { "AL", "AH", "BL", "BH", "DL", "DH", "CL", "CH", "EAX", "ECX", "EBX", "EDX", "ESI", "EDI", "EBP" };
std::string ERROR;

void Command::Display() {
	std::cout << "Display all commands" << std::endl;
}
bool Command::is_8_reg(std::string name) {
	for (int i = 0; i < 8; i++) {
		if (name == reg[i]) {
			return true;
		}
	}
	return false;
}
bool Command::is_32_reg(std::string name) {
	for (int i = 8; i < 15; i++) {
		if (name == reg[i]) {
			return true;
		}
	}
	return false;
}
int Command::reconstruction(std::string operand, bool& code, bool& dw, bool& ES, bool &DB, int &address) {
	bool sib = false;
	bool const_flag = true;
	std::string word;
	int num = 0;
	for (int i = 0; i < operand.length(); i++) {
		if (isalpha(operand[i]) != 0 || operand[i] == '@') {
			const_flag = false;
			while ((isalnum(operand[i]) != 0 || operand[i] == '@') && i < operand.length()) {
				word = word + operand[i];
				i++;
			}
			i--;
			list* temp = get_pointer(word);
			if (temp != NULL) {
				code = temp->code;
				dw = temp->DW;
				DB = temp->DB;
				address = temp->addres;
				if (temp->DW) {
					num = num + temp->offset + 1;
				}
				else {
					num = num + temp->offset;
				}
			}
			word.clear();
		}
		else if (isdigit(operand[i])) {
			while (isxdigit(operand[i]) && i < operand.length()) {
				word = word + operand[i];
				i++;
			}
			if (operand[i] == 'H') {
				word = word + operand[i];
				i++;
			}
			i--;
			if (const_flag) {
				num = num + 4;
				const_flag = false;
			}
			word.clear();
		}
		else {
			if (operand[i] == '[') {
				sib = true;
			}
			else if (operand[i] == '*' && sib) {
				num++;
				sib = false;
			}
			else if (operand[i] == ']') {
				sib = false;
			}
			else if (operand[i] == ':') {
				if (i - 2 >= 0) {
					word = word + operand[i - 2] + operand[i - 1] + operand[i];
					if (word == "ES:" || word == "DS:") {
						ES = true;
						num++;
					}
					word.clear();
				}
			}
			else {

			}
		}
	}
	return num;
}
bool Command::check_operands_error(int count_of_operands) {
	if (count_of_operands == 0) {
		if (S_operand.empty() && F_operand.empty()) {
			return true;
		}
		else {
			return false;
		}
	}
	if (count_of_operands == 1) {
		if (S_operand.empty()) {
			if (!F_operand.empty()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		if (S_operand.empty() || F_operand.empty()) {
			return false;
		}
		else {
			return true;
		}
	}
}
bool Command::check_reg_error(std::string name) {
	bool flag = is_8_reg(name);
	if (!flag) {
		flag = is_32_reg(name);
	}
	return flag;
}
bool Command::check_NUM_error(std::string name) {
	if (name[name.length() - 1] == 'H') {
		for (int i = 0; i < name.length() - 1; i++) {
			if (!isxdigit(name[i])) {
				return false;
			}
		}
		return true;
	}
	if (name[name.length() - 1] == 'B') {
		for (int i = 0; i < name.length() - 1; i++) {
			if (name[i] != '0' && name[i] != '1') {
				return false;
			}
		}
		return true;
	}
	for (int i = 0; i < name.length(); i++) {
		if (!isdigit(name[i])) {
			return false;
		}
	}
	return true;
}
bool Command::check_LEN_error(std::string name) {
	if (name.length() > 8) {
		return false;
	}
	return true;
}
bool Command::chek_seg() {
	int a = 0;
	list* temp = head;
	while (temp != NULL) {
		if (temp->segment) {
			a++;
		}
		temp = temp->prew;
	}
	if (a >= 2) {
		return true;
	}
	else {
		return false;
	}
}
Command::Command() {}


Command::~Command() {}

void Command::control() {
	if (M_flag) {
		if (lex == "MOV") {
			com = new MOV();
			dynamic_cast<MOV*>(com)->lex = lex;
			dynamic_cast<MOV*>(com)->F_operand = F_operand;
			dynamic_cast<MOV*>(com)->S_operand = S_operand;
			dynamic_cast<MOV*>(com)->offset = offset;
			offset = dynamic_cast<MOV*>(com)->control();
		}
		else if (lex == "STI") {
			com = new STI();
			dynamic_cast<STI*>(com)->lex = lex;
			dynamic_cast<STI*>(com)->F_operand = F_operand;
			dynamic_cast<STI*>(com)->S_operand = S_operand;
			dynamic_cast<STI*>(com)->offset = offset;
			offset = dynamic_cast<STI*>(com)->control();
		}
		else if (lex == "DEC") {
			com = new DEC();
			dynamic_cast<DEC*>(com)->lex = lex;
			dynamic_cast<DEC*>(com)->F_operand = F_operand;
			dynamic_cast<DEC*>(com)->S_operand = S_operand;
			dynamic_cast<DEC*>(com)->offset = offset;
			offset = dynamic_cast<DEC*>(com)->control();
		}
		else if (lex == "INC") {
			com = new INC();
			dynamic_cast<INC*>(com)->lex = lex;
			dynamic_cast<INC*>(com)->F_operand = F_operand;
			dynamic_cast<INC*>(com)->S_operand = S_operand;
			dynamic_cast<INC*>(com)->offset = offset;
			offset = dynamic_cast<INC*>(com)->control();
		}
		else if (lex == "CMP") {
			com = new CMP();
			dynamic_cast<CMP*>(com)->lex = lex;
			dynamic_cast<CMP*>(com)->F_operand = F_operand;
			dynamic_cast<CMP*>(com)->S_operand = S_operand;
			dynamic_cast<CMP*>(com)->offset = offset;
			offset = dynamic_cast<CMP*>(com)->control();
		}
		else if (lex == "AND") {
			com = new AND();
			dynamic_cast<AND*>(com)->lex = lex;
			dynamic_cast<AND*>(com)->F_operand = F_operand;
			dynamic_cast<AND*>(com)->S_operand = S_operand;
			dynamic_cast<AND*>(com)->offset = offset;
			offset = dynamic_cast<AND*>(com)->control();
		}
		else if (lex == "OR") {
			com = new OR();
			dynamic_cast<OR*>(com)->lex = lex;
			dynamic_cast<OR*>(com)->F_operand = F_operand;
			dynamic_cast<OR*>(com)->S_operand = S_operand;
			dynamic_cast<OR*>(com)->offset = offset;
			offset = dynamic_cast<OR*>(com)->control();
		}
		else if (lex == "ADD") {
			com = new ADD();
			dynamic_cast<ADD*>(com)->lex = lex;
			dynamic_cast<ADD*>(com)->F_operand = F_operand;
			dynamic_cast<ADD*>(com)->S_operand = S_operand;
			dynamic_cast<ADD*>(com)->offset = offset;
			offset = dynamic_cast<ADD*>(com)->control();
		}
		else if (lex == "JNZ") {
			com = new JNZ();
			dynamic_cast<JNZ*>(com)->lex = lex;
			dynamic_cast<JNZ*>(com)->F_operand = F_operand;
			dynamic_cast<JNZ*>(com)->S_operand = S_operand;
			dynamic_cast<JNZ*>(com)->offset = offset;
			offset = dynamic_cast<JNZ*>(com)->control();
		}
	}
	else if (identificator_flag) {
		if (second_entry) {
			ToHEX conv;
			std::cout << conv.convertation(offset, true) << "\t" << lex << ":";
			file << conv.convertation(offset, true) << "\t" << lex << ":";
		}
		else {
			if (chek_ava(lex)) {
				ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
			}
			else {
				add_to_list(lex, 0);
				get_pointer(lex)->addres = offset;
			}
		}
	}
	else if (D_flag) {
		com = new DIRECTIVE();
		dynamic_cast<DIRECTIVE*>(com)->lex = lex;
		dynamic_cast<DIRECTIVE*>(com)->F_operand = F_operand;
		dynamic_cast<DIRECTIVE*>(com)->S_operand = S_operand;
		dynamic_cast<DIRECTIVE*>(com)->offset = offset;
		if (!second_entry) {
			add_to_list(F_operand, 0);
		}
		offset = dynamic_cast<DIRECTIVE*>(com)->control();
	}
	else if (T_flag) {
		if (lex == "DD") {
			com = new DD();
			dynamic_cast<DD*>(com)->lex = lex;
			dynamic_cast<DD*>(com)->F_operand = F_operand;
			dynamic_cast<DD*>(com)->S_operand = S_operand;
			dynamic_cast<DD*>(com)->offset = offset;
			if (!second_entry) {
				if (chek_seg()) {
					if (chek_ava(lex)) {
						ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
					}
					else {
						add_to_list(F_operand, 5);
						get_pointer(F_operand)->code = true;
					}
				}
				else {
					if (chek_ava(lex)) {
						ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
					}
					else {
						add_to_list(F_operand, 4);
					}
				}
				get_pointer(F_operand)->addres = offset;
			}
			offset = dynamic_cast<DD*>(com)->control();
		}
		else if (lex == "DW") {
			com = new DW();
			dynamic_cast<DW*>(com)->lex = lex;
			dynamic_cast<DW*>(com)->F_operand = F_operand;
			dynamic_cast<DW*>(com)->S_operand = S_operand;
			dynamic_cast<DW*>(com)->offset = offset;
			if (!second_entry) {
				if (chek_seg()) {
					if (chek_ava(lex)) {
						ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
					}
					else {
						add_to_list(F_operand, 3);
						get_pointer(F_operand)->code = true;
					}
				}
				else {
					if (chek_ava(lex)) {
						ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
					}
					else {
						add_to_list(F_operand, 2);
					}
				}
				get_pointer(F_operand)->addres = offset;
				get_pointer(F_operand)->DW = true;
			}
			offset = dynamic_cast<DW*>(com)->control();
		}
		else if (lex == "DB") {
			com = new DB();
			dynamic_cast<DB*>(com)->lex = lex;
			dynamic_cast<DB*>(com)->F_operand = F_operand;
			dynamic_cast<DB*>(com)->S_operand = S_operand;
			dynamic_cast<DB*>(com)->offset = offset;
			if (!second_entry) {
				if (chek_seg()) {
					if (chek_ava(lex)) {
						ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
					}
					else {
						add_to_list(F_operand, 5);
						get_pointer(F_operand)->code = true;
					}
				}
				else {
					if (chek_ava(lex)) {
						ERROR = ERROR + "ERROR IN IDENTIFICATOR DOUBLE INITIALIZATED " + lex + "\n";
					}
					else {
						add_to_list(F_operand, 4);
					}
				}
				get_pointer(F_operand)->addres = offset;
				get_pointer(F_operand)->DB = true;
			}
			offset = dynamic_cast<DB*>(com)->control();
		}
	}
}

void Command::set_stock() {
	F_operand.clear();
	S_operand.clear();
	lex.clear();
	M_flag = false;
	R_flag = false;
	T_flag = false;
	S_flag = false;
	D_flag = false;
	identificator_flag = false;

	Digit_flag = true;
	Hexa_flag = false;
	Bool_flag = false;
	mitka_flag = false;
}
