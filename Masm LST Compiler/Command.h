#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "ToHEX.h"
#include "list.h"
#include <sstream>
#include "ModRM.h"
#include "Get_imm_value.h"

extern std::ostringstream file;
extern bool second_entry;
extern std::string ERROR;

class Command {
public:
	Command();
	~Command();
	void control();
	void set_stock();
	

	virtual void Display();

	
	std::string F_operand;
	std::string S_operand;
	std::string lex;
	bool M_flag = false;
	bool R_flag = false;
	bool T_flag = false;
	bool S_flag = false;
	bool D_flag = false;
	bool identificator_flag = false;

	bool Digit_flag = true;
	bool Hexa_flag = false;
	bool Bool_flag = false;

	bool mitka_flag = false;
protected:
	bool is_8_reg(std::string name);
	bool is_32_reg(std::string name);
	int offset = 0;
	int reconstruction(std::string operand, bool& code, bool& dw, bool& ES, bool &DB, int &address);
	bool check_operands_error(int count_of_operands);
	bool check_reg_error(std::string name);
	bool check_NUM_error(std::string name);
	bool check_LEN_error(std::string name);
private:
	bool chek_seg();
	Command* com;
};