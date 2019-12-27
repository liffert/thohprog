#pragma once
#include "Person.h"
class Employee :
	public Person {
public:
	Employee() {};
	Employee(std::string _f_name, std::string _l_name, int _age, int _id) :
		Person(_f_name, _l_name, _age), id(_id) {
	};
	Employee(const Employee &e);
	Employee& operator=(const Employee &e);
	void SetSalary(int s);
	void SetDepartment(std::string dept);
	void SetId(int n);
	int GetId();
	std::string GetDepartment();
	virtual void Display();
	void Display(bool);
	//Add here whatever you need
	int getSalary();
	int getAge();

protected:
	std::string department;
	int salary = 0;
	int id;
};

