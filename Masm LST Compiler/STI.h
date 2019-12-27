#pragma once
#include "Command.h"
class STI :
	public Command
{
public:
	STI();
	~STI();
	void Display();
	int control();
private:
	int count_of_operands = 0;
};

