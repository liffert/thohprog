#include "Source.h"
#include <fstream>
#include "ToHEX.h"
std::string instraction[] = { "MOV", "STI", "DEC", "INC", "CMP", "AND", "OR", "ADD", "JNZ" };
std::string directive[] = { "SEGMENT", "END", "ENDS" };
std::string regist[] = { "AL", "AH", "BL", "BH", "DL", "DH", "CL", "CH", "EAX", "ECX", "EBX", "EDX", "ESI", "EDI", "EBP" };
std::string type[] = { "DB", "DD", "DW" };
std::string S_R[] = { "ES", "DS" };
std::ostringstream file;
bool second_entry = false;

	void M::I_word(std::string word) {
		for (int i = 0; i < N.instraction; i++) {
			if (strcmp(word.c_str(), instraction[i].c_str()) == 0) {
				syn.stock_state = false;
				example.M_flag = true;
				example.lex = word;
				return;
			}
		}
		for (int i = 0; i < N.regist; i++) {
			if (strcmp(word.c_str(), regist[i].c_str()) == 0) {
				syn.stock_state = false;
				if (syn.F_operand_flag) {
					if (syn.F_operand_index == NULL) {
						syn.F_operand_index = counter;
					}
					example.F_operand = example.F_operand + word;
				}
				else {
					if (syn.S_operand_index == NULL) {
						syn.S_operand_index = counter;
					}
					example.S_operand = example.S_operand + word;
				}

				example.R_flag = true;
				return;
			}
		}
		for (int i = 0; i < N.type; i++) {
			if (strcmp(word.c_str(), type[i].c_str()) == 0) {
				syn.stock_state = false;
				example.T_flag = true;
				example.F_operand = example.lex;
				example.identificator_flag = false;
				syn.F_operand_flag = false;
				syn.stock_state = false;
				example.lex = word;
				return;
			}
		}
		for (int i = 0; i < N.S_R; i++) {
			if (strcmp(word.c_str(), S_R[i].c_str()) == 0) {
				syn.stock_state = false;
				if (syn.F_operand_flag) {
					if (syn.F_operand_index == NULL) {
						syn.F_operand_index = counter;
					}
					example.F_operand = example.F_operand + word;
				}
				else {
					if (syn.S_operand_index == NULL) {
						syn.S_operand_index = counter;
					}
					example.S_operand = example.S_operand + word;
				}

				example.S_flag = true;
				return;
			}
		}
		for (int i = 0; i < N.directive; i++) {
			if (strcmp(word.c_str(), directive[i].c_str()) == 0) {
				syn.stock_state = false;
				example.D_flag = true;
				example.F_operand = example.lex;
				example.identificator_flag = false;
				syn.F_operand_flag = false;
				syn.stock_state = false;
				example.lex = word;
				return;
			}
		}
		syn.stock_state = false;
		if (!example.M_flag) {
			example.identificator_flag = true;
			example.lex = word;
			return;
		}
		if (syn.F_operand_flag) {
			if (syn.F_operand_index == NULL) {
				syn.F_operand_index = counter;
			}
			example.F_operand = example.F_operand + word;
		}
		else {
			if (syn.S_operand_index == NULL) {
				syn.S_operand_index = counter;
			}
			example.S_operand = example.S_operand + word;
		}
	}
	void M::N_word(std::string word) {

		for (int i = 0; i < word.length(); i++) {
			if (isdigit(word[i]) == 0) {
				example.Digit_flag = false;
				break;
			}
		}
		if (!example.Digit_flag) {
			for (int i = 0; i < word.length(); i++) {
				if (i == word.length() - 1 && word[i] == 'H') {
					example.Hexa_flag = true;
				}
				if (!isxdigit(word[i])) {
					break;
				}
			}
		}
		if (!example.Digit_flag && !example.Hexa_flag) {
			for (int i = 0; i < word.length(); i++) {
				if (i == word.length() - 1 && word[i] == 'B') {
					example.Bool_flag = true;
				}
				if (isdigit(word[i]) == 0) {
					break;
				}
			}
		}
		if (example.Digit_flag) {
			syn.stock_state = false;
			if (syn.F_operand_flag) {
				if (syn.F_operand_index == NULL) {
					syn.F_operand_index = counter;
				}
				example.F_operand = example.F_operand + word;
			}
			else {
				if (syn.S_operand_index == NULL) {
					syn.S_operand_index = counter;
				}
				example.S_operand = example.S_operand + word;
			}
		}
		else if (example.Hexa_flag) {
			syn.stock_state = false;
			if (syn.F_operand_flag) {
				if (syn.F_operand_index == NULL) {
					syn.F_operand_index = counter;
				}
				example.F_operand = example.F_operand + word;
			}
			else {
				if (syn.S_operand_index == NULL) {
					syn.S_operand_index = counter;
				}
				example.S_operand = example.S_operand + word;
			}
		}
		else if (example.Bool_flag) {
			syn.stock_state = false;
			if (syn.F_operand_flag) {
				if (syn.F_operand_index == NULL) {
					syn.F_operand_index = counter;
				}
				example.F_operand = example.F_operand + word;
			}
			else {
				if (syn.S_operand_index == NULL) {
					syn.S_operand_index = counter;
				}
				example.S_operand = example.S_operand + word;
			}
		}
		else {
			std::cout << "error\n";
		}
	}

	void M::treatment(std::string line) {
		bool flag = false;
		counter = 1;
		for (int i = 0; i < line.length(); i++) {
			line[i] = toupper(line[i]);
		}
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != '\t' && line[i] != ' ') {
				flag = true;
				break;
			}
		}
		if (!flag) {
			return;
		}
		std::string word;
		for (int i = 0; i < line.length(); i++) {
			if (isalpha(line[i]) != 0 || line[i] == '@') {
				while ((isalnum(line[i]) != 0 || line[i] == '@') && i < line.length()) {
					word = word + line[i];
					i++;
				}
				i--;
				if ((i + 1) != line.length() && line[i + 1] == ':') {
					example.mitka_flag = true;
				}
				I_word(word);
				word.clear();
			}
			else if (isspace(line[i])) {
				//space(line[i]);
			}
			else if (isdigit(line[i])) {
				while (isxdigit(line[i]) && i < line.length()) {
					word = word + line[i];
					i++;
				}
				if (line[i] == 'H') {
					word = word + line[i];
					i++;
				}
				i--;
				N_word(word);
				word.clear();
			}
			else {
				if (!syn.F_operand_flag) {
					if (syn.S_operand_index == NULL) {
						syn.S_operand_index = counter;
					}
					example.S_operand = example.S_operand + line[i];
				}
				if (line[i] == ',') {
					syn.F_operand_flag = false;
				}
				if (syn.F_operand_flag) {
					example.F_operand = example.F_operand + line[i];
				}
				counter++;
			}
		}
	}
	void M::control(const std::string path) {
		FILE* LST;
		std::ifstream ASM(path);
		std::string line;
		std::string lst_path;
		if (second_entry) {
			for (int i = 0; i < path.length(); i++) {
				if (path[i] != '.') {
					lst_path = lst_path + path[i];
					continue;
				}
				break;
			}
			lst_path = lst_path + ".LST";
		}
		if (ASM.is_open()) {
			fopen_s(&LST, lst_path.c_str(), "w");
			if (second_entry) {
				file << "THe ONe LST creator ----- FILE: " << path << std::endl << std::endl;
			}
			while (!ASM.eof()) {
				std::getline(ASM, line);
				treatment(line);
				clear_syn();
				if (second_entry) {
					print_line_num();
					line_num++;
				}
				example.control();
				example.set_stock();
				if (second_entry) {
					std::cout << std::endl;
					file << std::endl;
				}
			}
			ASM.close();
			if (second_entry) {
				fputs(file.str().c_str(), LST);
				fclose(LST);
			}
			else {
				second_entry = true;
				control(path);
			}
		}
		else {
			std::cout << "Файлу не існує\n";
			system("pause");
			exit(1);
		}
	}
	void M::clear_syn() {
		syn.F_operand_index = NULL;
		syn.S_operand_index = NULL;
		syn.F_operand_flag = true;
		syn.stock_state = true;
	}
	M::M() {
		system("cls");
		std::cout << "Шлях до файлу(якщо файл лежить в директорії програми - назва файлу)[ASM]: ";
		std::getline(std::cin >> std::ws, path);
		control(path);
	}
	M::~M() {}
	void M::print_line_num() {
		if (line_num < 10) {
			std::cout << "000" << line_num << "\t";
			file << "000" << line_num << "\t";
		}
		else if (line_num < 100) {
			std::cout << "00" << line_num << "\t";
			file << "00" << line_num << "\t";
		}
		else if (line_num < 1000) {
			std::cout << "0" << line_num << "\t";
			file << "0" << line_num << "\t";
		}
		else {
			std::cout << line_num << "\t";
			file << line_num << "\t";
		}
	}



int main() {
	system("chcp 1251");
	M();
	if (!ERROR.empty()) {
		std::cout << std::endl << "IDETIFICATOR ERRORS:\n" << ERROR;
	}
	system("pause");
}