#pragma once
#include "Command.h"
class ADD :
	public Command
{
public:
	ADD();
	~ADD();
	virtual void Display();
	int control();
private:
	std::string RM(std::string name);
	int address = 0;
	bool DB = false;
	bool ES = false;
	bool DW = false;
	bool code = false;
	int current_offset;
	int count_of_operands = 2;
};

