#include "Menu.h" 
#include "Select.h"
#include "Insert.h"
#include "Delete.h"
#include "Update.h"
#include <vector>

struct connection Conn;
void emptyfunc() {}

void insert_data(std::string &name, int &year, int &month, int &day, int &number) {
	std::cout << "Enter name: ";
	std::getline(std::cin >> std::ws, name);
	std::cout << "Enter birth year: ";
	std::cin >> year;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter birth month: ";
	std::cin >> month;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter birth day: ";
	std::cin >> day;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter phone number: ";
	std::cin >> number;
	CIN_ELIMINATION_ERROR(false);
}
void insert_data(std::string& login, std::string& password, std::string& secure) {
	std::cout << "Enter login: ";
	std::getline(std::cin >> std::ws, login);
	std::cout << "Enter password: ";
	std::getline(std::cin >> std::ws, password);
	std::cout << "Enter secure status(true or t/false or f): ";
	std::getline(std::cin >> std::ws, secure);
}
void insert_data(std::string& Text, int& year, int& month, int& day, int& files_count, std::vector<std::string> &Recipient) {
	std::cout << "Enter text: ";
	std::getline(std::cin >> std::ws, Text);
	std::cout << "Enter year: ";
	std::cin >> year;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter month: ";
	std::cin >> month;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter day: ";
	std::cin >> day;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter count of files: ";
	std::cin >> files_count;
	CIN_ELIMINATION_ERROR(false);
	Console_clear();

	std::string buff;
	std::cout << "Enter recipient: ";
	std::getline(std::cin >> std::ws, buff);
	Recipient.push_back(buff);
	buff.clear();

	while (1) {
		Menu rep;
		rep.set_ask();
		rep.set_func(emptyfunc, "Yes");
		rep.set_headline("Add recipient");
		rep.set_last_text("No");
		if (rep.start() == 1) {
			std::cout << "Enter recipient: ";
			std::getline(std::cin >> std::ws, buff);
			Recipient.push_back(buff);
			buff.clear();
		}
		else { Console_clear(); break; }
	}
}
void insert_data(std::string& name, int& year, int& month, int& day) {
	std::cout << "Enter name: ";
	std::getline(std::cin >> std::ws, name);
	std::cout << "Enter creation year: ";
	std::cin >> year;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter creation month: ";
	std::cin >> month;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Enter creation day: ";
	std::cin >> day;
	CIN_ELIMINATION_ERROR(false);
}

std::string select_search(std::string text) {
	std::string find;
	std::cout << text;
	std::getline(std::cin >> std::ws, find);
	return find;
}
void select_data(std::string& secure, std::string &name) {
	std::cout << "Enter name: ";
	std::getline(std::cin >> std::ws, name);
	std::cout << "Enter secure status(true or t/false of f): ";
	std::getline(std::cin >> std::ws, secure);
}
int delete_id() {
	int id;
	std::cout << "Enter id to delete: ";
	std::cin >> id;
	CIN_ELIMINATION_ERROR(false);
	return id;
}
void get_update_idtext(std::string& text, int& id, const std::string out) {
	std::cout << "Enter id to update: ";
	std::cin >> id;
	CIN_ELIMINATION_ERROR(false);
	std::cout << out;
	std::getline(std::cin >> std::ws, text);
}
void Sstart() {
	Menu selectMenu;
	selectMenu.set_headline("Select");
	selectMenu.set_func(users, "From users");
	selectMenu.set_func(messages, "From messages");
	selectMenu.set_func(account, "From account");
	selectMenu.set_func(folders, "From folders");
	selectMenu.set_func(static_selectj, "From accounts and users by secure flag and username(static)");
	selectMenu.set_func(dynamic_selectj, "From accounts and users by secure flag and username(dynamic)");
	selectMenu.set_func(search, "Search word in messages text");
	selectMenu.set_func(not_search, "Search not_word in messages text");

	selectMenu.set_last_text("Back");
	selectMenu.start();
}
void Istart() {
	Menu insertMenu;
	insertMenu.set_headline("Insert");
	insertMenu.set_func(Iusers, "User");
	insertMenu.set_func(Iaccount, "Account");
	insertMenu.set_func(Imessages, "Messages");
	insertMenu.set_func(Ifolders, "Folders");
	insertMenu.set_func(random, "Random into Account");

	insertMenu.set_last_text("Back");
	insertMenu.start();
}

void Dstart() {
	Menu deleteMenu;
	deleteMenu.set_headline("Delete");
	deleteMenu.set_func(Dusers, "Users");
	deleteMenu.set_func(Daccount, "Account");
	deleteMenu.set_func(Dmessages, "Messages");
	deleteMenu.set_func(Dfolders, "Folders");

	deleteMenu.set_last_text("Back");
	deleteMenu.start();
}

void Ustart() {
	Menu updateMenu;
	updateMenu.set_headline("Update");
	updateMenu.set_func(Uusers, "Users");
	updateMenu.set_func(Uaccount, "Account");
	updateMenu.set_func(Umessages, "Messages");
	updateMenu.set_func(Ufolders, "Folders");

	updateMenu.set_last_text("Back");
	updateMenu.start();
}
int main() {
	{
		COORD screen = { 1750, 800 };
		SetConsoleScreenBufferSize(hStdOut, screen);
		MoveWindow(GetConsoleWindow(), 100, 100, screen.X, screen.Y, TRUE);
	}

	ConnStatusType connection_result = Conn.start();

	if (connection_result == CONNECTION_OK) {
		std::cout << "Connection to database - done\n";
		Sleep(300);
	}
	else {
		std::cout << "Connection to database - failed\n";
		return 0;
	}
	
	Menu mainMenu;
	mainMenu.set_headline("Main");
	mainMenu.set_func(Sstart, "Select");
	mainMenu.set_func(Istart, "Insert");
	mainMenu.set_func(Dstart, "Delete");
	mainMenu.set_func(Ustart, "Update");
	mainMenu.start();
}