#include "ModRM.h"

void ModRM::set(std::string name, std::string Mod, std::string R_M, std::string REG) {
	table temp(name, Mod, R_M, REG);
	t.push_back(temp);
}
ModRM::ModRM() {
	set("AL", "11", "000", "000");
	set("CL", "11", "001", "001");
	set("DL", "11", "010", "010");
	set("BL", "11", "011", "011");
	set("AH", "11", "100", "100");
	set("CH", "11", "101", "101");
	set("DH", "11", "110", "110");
	set("BH", "11", "111", "111");
	set("EAX", "11", "000", "000");
	set("ECX", "11", "001", "001");
	set("EDX", "11", "010", "010");
	set("EBX", "11", "011", "011");
	set("ESI", "11", "110", "110");
	set("EDI", "11", "111", "111");
	set("EBP", "11", "101", "101");
	set("EAX*2", "01", "000", "000");
	set("EBX*2", "01", "011", "000");
	set("ECX*2", "01", "001", "000");
	set("EDX*2", "01", "010", "000");
	set("ESI*2", "01", "110", "000");
	set("EDI*2", "01", "111", "000");
	set("EBP*2", "01", "101", "000");
	set("EAX*4", "10", "000", "000");
	set("EBX*4", "10", "011", "000");
	set("ECX*4", "10", "001", "000");
	set("EDX*4", "10", "010", "000");
	set("ESI*4", "10", "110", "000");
	set("EDI*4", "10", "111", "000");
	set("EBP*4", "10", "101", "000");
	set("SI+disp16", "10", "100", "000");
	set("DI", "00", "101", "000");
	set("EAX*8", "11", "000", "000");
	set("EBX*8", "11", "011", "000");
	set("ECX*8", "11", "001", "000");
	set("EDX*8", "11", "010", "000");
	set("ESI*8", "11", "110", "000");
	set("EDI*8", "11", "111", "000");
	set("EBP*8", "11", "101", "000");
}


ModRM::~ModRM() {
}

std::string ModRM::get_REG(std::string name) {
	for (int i = 0; i < t.size(); i++) {
		if (t[i].name == name) {
			return t[i].REG;
		}
	}
	return "000";
}

std::string ModRM::get_MOD(std::string name) {
	for (int i = 0; i < t.size(); i++) {
		if (t[i].name == name) {
			return t[i].Mod;
		}
	}
	return "000";
}

std::string ModRM::get_R_M(std::string name) {
	for (int i = 0; i < t.size(); i++) {
		if (t[i].name == name) {
			return t[i].R_M;
		}
	}
	return "000";
}


table::table(std::string name, std::string Mod, std::string R_M, std::string REG) {
	this->name = name;
	this->Mod = Mod;
	this->R_M = R_M;
	this->REG = REG;
}

table::~table() {
}
