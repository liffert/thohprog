#pragma once
#include "Command.h"
class OR :
	public Command
{
public:
	OR();
	~OR();
	virtual void Display();
	int control();
private:
	std::string RM(std::string name);
	int count_of_operands = 2;
};

