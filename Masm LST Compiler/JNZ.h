#pragma once
#include "Command.h"
class JNZ :
	public Command
{
public:
	JNZ();
	~JNZ();
	virtual void Display();
	int control();
private:
	int count_of_operands = 1;
};

