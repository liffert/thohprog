#pragma once
#include <iostream>
class Get_imm_value {
public:
	Get_imm_value();
	~Get_imm_value();
	int get(std::string num);
private:
	int reconstruction(std::string num);
};

