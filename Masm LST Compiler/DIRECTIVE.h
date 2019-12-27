#pragma once
#include "Command.h"
class DIRECTIVE :
	public Command
{
public:
	DIRECTIVE();
	~DIRECTIVE();
	virtual void Display();
	int control();
private:
	int count_of_operands = 1;
};

