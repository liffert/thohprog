#pragma once
#include "Command.h"
class DD :
	public Command
{
public:
	DD();
	~DD();
	virtual void Display();
	int control();
private:
	int count_of_operands = 2;
};

