#pragma once
#include "Command.h"
class DEC :
	public Command
{
public:
	DEC();
	~DEC();
	virtual void Display();
	int control();
private:
	std::string _8(std::string name);
	std::string _32(std::string name);
	int count_of_operands = 1;
};