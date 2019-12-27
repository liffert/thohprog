#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
class LexicalAnalizer
{
public:
	LexicalAnalizer();
	~LexicalAnalizer();

private:
	void clear_syn();
	void I_word(std::string word);
	void N_word(std::string word);
	void treatment(std::string line);
	void print_syn();
	void control(const std::string path);


	std::string path;
	int counter = 1;
	struct quantity {
		const int instraction = 9;
		const int directive = 3;
		const int regist = 14;
		const int type = 3;
		const int S_R = 2;
	}; quantity N;
	struct struct_s {
		int Mitka_Idetificator_Index = NULL;
		int Mnemocode_index = NULL;
		int Mnemocode_count = 0;
		int F_operand_index = NULL;
		int F_operand_counter = 0;
		bool F_operand_flag = true;
		int S_operand_index = NULL;
		int S_operand_counter = 0;
		bool Mitka_flag = true;
		bool stock_state = true;
	}; struct_s syn;
};

