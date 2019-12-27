#pragma once
#include <iostream>

void add_to_list(std::string name, int off);
bool chek_ava(std::string name);
typedef struct i {
	std::string identificator;
	int offset;
	bool DB = false;
	bool DW = false;
	bool segment = false;
	bool code = false;
	int addres;
	struct i* prew;
}list;
list* get_pointer(std::string name);
extern list* head;
