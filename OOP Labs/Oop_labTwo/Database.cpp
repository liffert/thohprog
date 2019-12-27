#include "Database.h"
#include <iostream>
#include "Manager.h"
#include "Employee.h"
#include <fstream>
#include <string>

bool Database::FireEmployee(int id) {
	bool flag = false;
	for (auto iter = employees.begin(); iter < employees.end(); iter++) {
		if (dynamic_cast<Employee*>(*iter)->GetId() == id) {
			flag = true;
			iter = employees.erase(iter);
		}
	}
	if (flag) {
		for (Person* pointer : employees) {
			if (typeid(*pointer) == typeid(Manager)) {
				dynamic_cast<Manager*>(pointer)->FireSub(id);
			}
		}
	}
	return flag;
}

void Database::DisplayAll() {
	for (Person* pointer : employees) {
		pointer->Display(false);
		std::cout << std::endl;
	}
}
std::vector<Person*> Database::SQL(const char* field, const char* cond, const char* value) {
	if (field == NULL || value == NULL || cond == NULL) {
		exit(1);
	}
	std::vector<Person*> RS;
	if (strcmp(field, "salary") == 0) {
		bool le = false;
		if (strcmp(cond, "le") == 0) {
			le = true;
		}
		if (le) {
			for (Person* pointer : employees) {
				if (dynamic_cast<Employee*>(pointer)->getSalary() <= atoi(value)) {
					RS.push_back(pointer);
				}
			}
		}
		else {
			for (Person* pointer : employees) {
				if (dynamic_cast<Employee*>(pointer)->getSalary() >= atoi(value)) {
					RS.push_back(pointer);
				}
			}
		}
	}
	else if (strcmp(field, "age") == 0) {
		bool le = false;
		if (strcmp(cond, "le") == 0) {
			le = true;
		}
		if (le) {
			for (Person* pointer : employees) {
				if (dynamic_cast<Employee*>(pointer)->getAge() <= atoi(value)) {
					RS.push_back(pointer);
				}
			}
		}
		else {
			for (Person* pointer : employees) {
				if (dynamic_cast<Employee*>(pointer)->getAge() >= atoi(value)) {
					RS.push_back(pointer);
				}
			}
		}
	}
	return RS;
}
void Database::ShowRecordSet(std::vector<Person*> rs) {
	std::cout << "Show RS from SQL: \n";
	if (rs.empty()) {
		std::cout << "RS is empty";
		return;
	}
	for (int i = 0; i < rs.size(); i++) {
		rs[i]->Display(false);
	}
}
bool Database::LoadFromFile(const char *file) {
	if (file == NULL) {
		std::cout << "File is empty\n";
		system("pause");
		return false;
	}
	std::ifstream input(file);
	if (!input.is_open()) {
		std::cout << "Can’t open the file\n";
		system("pause");
		return false;
	}
	std::string line;
	while (!input.eof()) {
		std::getline(input, line);
		ParseLine(line);
	}
	return true;
}
void Database::ArrangeSubordinates() {
	std::vector<Manager*> managers;
	std::vector<Employee*>employee;
	for (Person* pointer : employees) {
		if (typeid(*pointer) == typeid(Employee)) {
			employee.push_back((Employee*)pointer);
		}
		else if (typeid(*pointer) == typeid(Manager)) {
			managers.push_back((Manager*)pointer);
		}
	}
	for (int i = 0; i < managers.size(); i++) {
		managers[i]->eraseSub();
	}
	for (int i = 0; i < managers.size(); i++) {
		for (int j = 0; j < employee.size(); j++) {
			if (employee[j]->GetDepartment() == managers[i]->GetDepartment()) {
				managers[i]->AddSubordinate(employee[j]);
			}
		}
	}
	employee.clear();
	managers.clear();
}
Person* Database::HireEmployee(Person* p) {
	if (p == NULL) {
		return NULL;
	}

	employees.push_back(p);
	ArrangeSubordinates();
	return p;
}
void Database::DisplayDepartmentEmployees(std::string _department) {
	std::cout << "Display " << _department << " department employees:\n";
	for (Person* pointer : employees) {
		if (dynamic_cast<Employee*>(pointer)->GetDepartment() == _department) {
			pointer->Display(false);
		}
	}
}
void Database::ParseLine(std::string &line) {

	int position = stoi(getword(line, 1));
	int id = stoi(getword(line, 2));
	std::string F_name = getword(line, 3);
	std::string S_name = getword(line, 4);
	int age = stoi(getword(line, 5));
	std::string departament = getword(line, 6);
	int salary = stoi(getword(line, 7));

	if (position == 0) {
		Employee *temp = new Employee(F_name, S_name, age, id);
		temp->SetSalary(salary);
		temp->SetDepartment(departament);
		temp->SetId(id);
		employees.push_back(temp);
	}
	else if (position == 1) {
		Manager* temp = new Manager(F_name, S_name, age, id);
		temp->SetSalary(salary);
		temp->SetDepartment(departament);
		temp->SetId(id);
		employees.push_back(temp);
	}

}
std::string Database::getword(std::string line, int field) {
	std::string word;
	int i = 0;
	if (field > 1) {
		for (i; i < line.length(); i++) {
			if (field == 1) {
				break;
			}
			if (line[i] == ';') {
				field--;
			}
		}
	}
	while (line[i] != ';' && i < line.length()) {
		word = word + line[i];
		i++;
	}
	return word;
}