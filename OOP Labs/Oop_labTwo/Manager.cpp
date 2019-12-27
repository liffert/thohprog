#include "Manager.h"




Manager::Manager(const Manager& m){
	f_name = m.f_name;
	l_name = m.l_name;
	age = m.age;
	id = m.id;
	salary = m.salary;
	department = m.department;
	subordinates = m.subordinates;
}

Manager& Manager::operator=(const Manager& m) {
	if (this == &m) {
		return *this;
	}

	f_name = m.f_name;
	l_name = m.l_name;
	age = m.age;
	id = m.id;
	salary = m.salary;
	department = m.department;
	subordinates = m.subordinates;

	return *this;
}

void Manager::Display(bool flag) {
	if (flag) {
		std::cout << "\t\tEmploynent type: manager" << std::endl << "\t\tid: " << id << std::endl
			<< "\t\t" << f_name << " " << l_name << "age: " << age << " salary: " << salary << std::endl
			<< "\t\tDepartament: " << department << std::endl;
	}
	else {
		std::cout << "Employnent type: manager" << std::endl << "id: " << id << std::endl
			<< f_name << " " << l_name << "age: " << age << " salary: " << salary << std::endl
			<< "Departament: " << department << std::endl;
	}
	DisplaySubordinates();
}

Person* Manager::AddSubordinate(Person* p) {
	if (p == NULL) {
		return p;
	}
	subordinates.push_back(p);
	return p;
}

void Manager::DisplaySubordinates() {
	std::cout << "Subordinates:" << std::endl;
	if (subordinates.size() == 0) {
		std::cout << "\t\tnone" << std::endl;
		return;
	}
	for (auto itetator = subordinates.begin(); itetator != subordinates.end(); itetator++) {
		(*itetator)->Display(true);
		std::cout << std::endl;
	}
}

bool Manager::FireSub(int id) {
	for (auto iter = subordinates.begin(); iter != subordinates.end(); iter++) {
		if (dynamic_cast<Employee*>(*iter)->GetId() == id) {
			iter = subordinates.erase(iter);
			return true;
		}
	}
	return false;
}

void Manager::eraseSub() {
	subordinates.clear();
}
