#include "Employee.h"

void Employee::Display() {
	std::cout << "Employnent type: employee" << std::endl << "id: " << id << std::endl 
			  << f_name << " " << l_name << "age: " << age << " salary: " << salary << std::endl
			  << "Departament: " << department << std::endl;

}
void Employee::Display(bool flag) {
	if (flag) {
		std::cout << "\t\tEmploynent type: employee" << std::endl << "\t\tid: " << id << std::endl
			<< "\t\t" << f_name << " " << l_name << "age: " << age << " salary: " << salary << std::endl
			<< "\t\tDepartament: " << department << std::endl;
	}
	else {
		Display();
	}

}

int Employee::getSalary() {
	return salary;
}

int Employee::getAge() {
	return age;
}

Employee::Employee(const Employee& e) {
	f_name = e.f_name;
	l_name = e.l_name;
	age = e.age;
	salary = e.salary;
	id = e.id;
	department = e.department;
}

Employee& Employee::operator=(const Employee& e) {

	if (this == &e) {
		return *this;
	}

	f_name = e.f_name;
	l_name = e.l_name;
	age = e.age;
	salary = e.salary;
	id = e.id;
	department = e.department;
	
	return *this;
}

void Employee::SetSalary(int s){
	salary = s;
}

void Employee::SetDepartment(std::string dept) {
	department = dept;
}

void Employee::SetId(int n) {
	id = n;
}

int Employee::GetId() {
	return id;
}

std::string Employee::GetDepartment() {

	return department;
}
