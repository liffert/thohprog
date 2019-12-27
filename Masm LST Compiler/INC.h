#pragma once
#include "Command.h"
class INC :
	public Command
{
public:
	INC();
	~INC();
	virtual void Display();
	int control();
private:
	int address = 0;
	bool DB = false;
	bool ES = false;
	bool DW = false;
	bool code = false;
	int current_offset;
	int count_of_operands = 1;
	std::string RM(std::string name);
};

