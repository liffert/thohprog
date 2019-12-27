#include "LexicalAnalizer.h"

std::string instraction[] = { "MOV", "STI", "DEC", "INC", "CMP", "AND", "OR", "ADD", "JNZ" };
std::string directive[] = { "SEGMENT", "END", "ENDS" };
std::string regist[] = { "AL", "AH", "BL", "BH", "DL", "DH", "CL", "CH", "EAX", "ECX", "EBX", "EDX", "ESI", "EDI" };
std::string type[] = { "DB", "DD", "DW" };
std::string S_R[] = { "ES", "DS" };

LexicalAnalizer::LexicalAnalizer() {
	system("cls");
	std::string path;
	std::cout << "Шлях до файлу(якщо файл лежить в директорії програми - назва файлу)[ASM]: ";
	std::getline(std::cin >> std::ws, path);
	std::cout << "------------------------------------------------------------------\n";
	printf_s("| Номер лексеми| Кількість символів лексеми| Лексема| Тип лексеми|\n");
	std::cout << "------------------------------------------------------------------\n\n";
	control(path);
}


LexicalAnalizer::~LexicalAnalizer(){}

void LexicalAnalizer::clear_syn() {
	syn.Mitka_Idetificator_Index = NULL;
	syn.Mnemocode_index = NULL;
	syn.Mnemocode_count = 0;
	syn.F_operand_index = NULL;
	syn.F_operand_counter = 0;
	syn.S_operand_index = NULL;
	syn.S_operand_counter = 0;
	syn.Mitka_flag = true;
	syn.F_operand_flag = true;
	syn.stock_state = true;
}
void LexicalAnalizer::I_word(std::string word) {
	bool M_flag = false;
	bool R_flag = false;
	bool T_flag = false;
	bool S_flag = false;
	bool D_flag = false;
	for (int i = 0; i < N.instraction; i++) {
		if (strcmp(word.c_str(), instraction[i].c_str()) == 0) {
			syn.stock_state = false;
			syn.Mitka_flag = false;
			syn.Mnemocode_count++;
			if (syn.Mnemocode_index == NULL) {
				syn.Mnemocode_index = counter;
			}
			M_flag = true;
			break;
		}
	}
	if (!M_flag) {
		for (int i = 0; i < N.regist; i++) {
			if (strcmp(word.c_str(), regist[i].c_str()) == 0) {
				syn.stock_state = false;
				if (syn.F_operand_flag) {
					if (syn.F_operand_index == NULL) {
						syn.F_operand_index = counter;
					}
					syn.F_operand_counter++;
				}
				else {
					if (syn.S_operand_index == NULL) {
						syn.S_operand_index = counter;
					}
					syn.S_operand_counter++;
				}

				R_flag = true;
				break;
			}
		}
	}
	if (!M_flag && !R_flag) {
		for (int i = 0; i < N.type; i++) {
			if (strcmp(word.c_str(), type[i].c_str()) == 0) {
				syn.stock_state = false;
				syn.Mitka_flag = false;
				syn.Mnemocode_count++;
				if (syn.Mnemocode_index == NULL) {
					syn.Mnemocode_index = counter;
				}
				T_flag = true;
				break;
			}
		}
	}
	if (!M_flag && !R_flag && !T_flag) {
		for (int i = 0; i < N.S_R; i++) {
			if (strcmp(word.c_str(), S_R[i].c_str()) == 0) {
				syn.stock_state = false;
				if (syn.F_operand_flag) {
					if (syn.F_operand_index == NULL) {
						syn.F_operand_index = counter;
					}
					syn.F_operand_counter++;
				}
				else {
					if (syn.S_operand_index == NULL) {
						syn.S_operand_index = counter;
					}
					syn.S_operand_counter++;
				}

				S_flag = true;
				break;
			}
		}
	}
	if (!M_flag && !R_flag && !T_flag && !S_flag) {
		for (int i = 0; i < N.directive; i++) {
			if (strcmp(word.c_str(), directive[i].c_str()) == 0) {
				syn.stock_state = false;
				syn.Mitka_flag = false;
				syn.Mnemocode_count++;
				if (syn.Mnemocode_index == NULL) {
					syn.Mnemocode_index = counter;
				}
				D_flag = true;
				break;
			}
		}
	}
	if (M_flag) {
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Машинна інструкція");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else if (R_flag) {
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Регістр загального призначення");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else if (T_flag) {
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Ідентифікатор типу данних");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else if (S_flag) {
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Сегментний регістр данних");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else if (D_flag) {
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Директива");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else {
		syn.stock_state = false;
		if (syn.Mitka_flag) {
			syn.Mitka_Idetificator_Index = counter;
		}
		else {
			if (syn.F_operand_flag) {
				if (syn.F_operand_index == NULL) {
					syn.F_operand_index = counter;
				}
				syn.F_operand_counter++;
			}
			else {
				if (syn.S_operand_index == NULL) {
					syn.S_operand_index = counter;
				}
				syn.S_operand_counter++;
			}
		}
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Ідентифікатор користувача");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
}


void LexicalAnalizer::N_word(std::string word) {
	bool D_flag = true;
	bool H_flag = false;
	bool B_flag = false;

	for (int i = 0; i < word.length(); i++) {
		if (isdigit(word[i]) == 0) {
			D_flag = false;
			break;
		}
	}
	if (!D_flag) {
		for (int i = 0; i < word.length(); i++) {
			if (i == word.length() - 1 && word[i] == 'H') {
				H_flag = true;
			}
			if (!isxdigit(word[i])) {
				break;
			}
		}
	}
	if (!D_flag && !H_flag) {
		for (int i = 0; i < word.length(); i++) {
			if (i == word.length() - 1 && word[i] == 'B') {
				B_flag = true;
			}
			if (isdigit(word[i]) == 0) {
				break;
			}
		}
	}
	if (D_flag) {
		syn.stock_state = false;
		if (syn.F_operand_flag) {
			if (syn.F_operand_index == NULL) {
				syn.F_operand_index = counter;
			}
			syn.F_operand_counter++;
		}
		else {
			if (syn.S_operand_index == NULL) {
				syn.S_operand_index = counter;
			}
			syn.S_operand_counter++;
		}
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Десяткова константа");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else if (H_flag) {
		syn.stock_state = false;
		if (syn.F_operand_flag) {
			if (syn.F_operand_index == NULL) {
				syn.F_operand_index = counter;
			}
			syn.F_operand_counter++;
		}
		else {
			if (syn.S_operand_index == NULL) {
				syn.S_operand_index = counter;
			}
			syn.S_operand_counter++;
		}
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Шістнадцяткова константа");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else if (B_flag) {
		syn.stock_state = false;
		if (syn.F_operand_flag) {
			if (syn.F_operand_index == NULL) {
				syn.F_operand_index = counter;
			}
			syn.F_operand_counter++;
		}
		else {
			if (syn.S_operand_index == NULL) {
				syn.S_operand_index = counter;
			}
			syn.S_operand_counter++;
		}
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Двійкова константа");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
	else {
		syn.stock_state = false;
		if (syn.F_operand_flag) {
			if (syn.F_operand_index == NULL) {
				syn.F_operand_index = counter;
			}
			syn.F_operand_counter++;
		}
		else {
			if (syn.S_operand_index == NULL) {
				syn.S_operand_index = counter;
			}
			syn.S_operand_counter++;
		}
		printf_s("| %2d| %2d| %20s| %33s|\n", counter, word.length(), word.c_str(), "Ідентифікатор користувача");
		std::cout << "------------------------------------------------------------------\n";
		counter++;
	}
}

void LexicalAnalizer::treatment(std::string line) {
	bool flag = false;
	counter = 1;
	std::cout << line << std::endl;
	for (int i = 0; i < line.length(); i++) {
		line[i] = toupper(line[i]);
	}
	for (int i = 0; i < line.length(); i++) {
		if (line[i] != '\t' && line[i] != ' ') {
			flag = true;
			break;
		}
	}
	if (flag) {
		std::cout << "------------------------------------------------------------------\n";
	}
	std::string word;
	for (int i = 0; i < line.length(); i++) {
		if (isalpha(line[i]) != 0 || line[i] == '@') {
			while ((isalnum(line[i]) != 0 || line[i] == '@') && i < line.length()) {
				word = word + line[i];
				i++;
			}
			i--;
			I_word(word);
			word.clear();
		}
		else if (isspace(line[i])) {
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
				if (syn.S_operand_counter == 0 && line[i] == ':') {
					syn.S_operand_counter--;
				}
				syn.S_operand_counter++;
			}
			if (line[i] == ',') {
				syn.F_operand_flag = false;
			}
			if (syn.F_operand_flag) {
				if (syn.F_operand_counter == 0 && line[i] == ':') {
					syn.F_operand_counter--;
				}
				syn.F_operand_counter++;
			}
			printf_s("| %2d| %2d| %20c| %33s|\n", counter, 1, line[i], "Односимвольна лексема");
			std::cout << "------------------------------------------------------------------\n";
			counter++;
		}
	}
}

void LexicalAnalizer::print_syn() {
	if (syn.stock_state) {
		return;
	}
	std::cout << "Мітка/ідетнифікатор індекс = ";
	if (syn.Mitka_Idetificator_Index != NULL) {
		std::cout << syn.Mitka_Idetificator_Index << std::endl;
	}
	else {
		std::cout << "Відсутній" << std::endl;
	}

	std::cout << "Мнемокод - перший індекс = ";
	if (syn.Mnemocode_index != NULL) {
		std::cout << syn.Mnemocode_index << "\tМнемокод кількість = " << syn.Mnemocode_count << std::endl;
	}
	else {
		std::cout << "Відсутній" << "\tМнемокод кількість = " << syn.Mnemocode_count << std::endl;
	}

	std::cout << "Перший операнд індекс = ";
	if (syn.F_operand_index != NULL) {
		std::cout << syn.F_operand_index << "\tПерший операнд довжина = " << syn.F_operand_counter << std::endl;
	}
	else {
		std::cout << "Відсутній" << "\tПерший операнд довжина = " << syn.F_operand_counter << std::endl;
	}

	std::cout << "Другий операнд індекс = ";
	if (syn.S_operand_index != NULL) {
		std::cout << syn.S_operand_index << "\tДругий операнд довжина = " << syn.S_operand_counter << std::endl;
	}
	else {
		std::cout << "Відсутній" << "\tДругий операнд довжина = " << syn.S_operand_counter << std::endl;
	}
	std::cout << std::endl;
}
void LexicalAnalizer::control(const std::string path) {
	std::ifstream ASM(path);
	std::string line;
	if (ASM.is_open()) {
		while (!ASM.eof()) {
			std::getline(ASM, line);
			treatment(line);
			print_syn();
			clear_syn();
		}
		ASM.close();
	}
	else {
		std::cout << "Файлу не існує\n";
	}
}