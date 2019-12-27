#pragma once
#include <iostream>

class Person {
public:
	Person() {};
	Person(std::string _f_name, std::string _l_name, int _age) : age(_age),
		f_name(_f_name), l_name(_l_name) {	}
	virtual void Display(bool) = 0;
	~Person() {};
protected:
	std::string f_name;//first name
	std::string l_name;//last name
	int age;

};

