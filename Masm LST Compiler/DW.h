#pragma once
#include "Command.h"
class DW :
	public Command
{
public:
	DW();
	~DW();
	virtual void Display();
	int control();
private:
	int count_of_operands = 2;
};

