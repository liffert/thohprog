#include "Database.h"
#include "Employee.h"


int main() {
	Database data;
	data.LoadFromFile("input.csv");
	data.DisplayAll();
	data.ArrangeSubordinates();
	std::cout << "\n\n\n";
	data.DisplayAll();
	std::cout << "Delete id 1\n";
	data.FireEmployee(1);
	std::cout << "\n\n\n";
	data.DisplayAll();

	std::cout << "Hire test(Wander Frosty +)\n";
	Employee* temp = new Employee("Wander", "Frosty", 18, 13);
	temp->SetSalary(2000);
	temp->SetDepartment("IT");

	data.HireEmployee(temp);
	data.DisplayAll();
	std::vector<Person*> RS = data.SQL("age", "le", "50");
	data.ShowRecordSet(RS);

	system("pause");
}