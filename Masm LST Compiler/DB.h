#pragma once
#include "Command.h"
class DB :
	public Command
{
public:
	DB();
	~DB();
	virtual void Display();
	int control();
private:
	int count_of_operands = 2;
};

