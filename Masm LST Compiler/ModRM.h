#pragma once
#include <iostream>
#include <vector>

class table {
public:
	table(std::string name, std::string Mod, std::string R_M, std::string REG);
	~table();
	std::string name;
	std::string Mod;
	std::string R_M;
	std::string REG;
};

class ModRM {
public:
	void set(std::string name, std::string Mod, std::string R_M, std::string REG);
	ModRM();
	~ModRM();
	std::string get_REG(std::string name);
	std::string get_MOD(std::string name);
	std::string get_R_M(std::string name);
private:
	std::vector<table> t;
};

