#pragma once
#include "Header.h"
#include <fstream>

class Create_train {

public:
	Create_train() {}
	~Create_train(){}
	
	void start();

	void start2();
	std::string get_path() { return path; }
private:
	std::string path = "train.txt";
	std::string path2 = "train2.txt";
};