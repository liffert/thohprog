#pragma once
#include "Command.h"
class MOV :
	public Command {
public:
	MOV();
	~MOV();
	virtual void Display();
	int control();
private:
	std::string RM(std::string name);
	int address = 0;
	bool DB = false;
	bool ES = false;
	bool DW = false;
	int current_offset;
	bool code = false;
	int count_of_operands = 2;
};

