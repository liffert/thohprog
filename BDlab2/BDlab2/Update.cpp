#include "Update.h"
#include "Menu.h"
#include "Select.h"

bool check_update_error(const PGresult* res) {
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Delete ERROR - " << PQresultErrorMessage(res) << std::endl;
		system("pause");
		return false;
	}
	return true;
}
static char* get_num_pointer(int num) {
	std::string Num = std::to_string(num);
	char* p = new char[Num.length() + 1];
	for (int i = 0; i < Num.length(); i++) {
		p[i] = Num[i];
	}
	p[Num.length()] = '\0';

	return p;
}
void Uusers() {
	users();
	int id;
	std::string name;

	get_update_idtext(name, id, "Enter new name: ");

	std::string SQL = "UPDATE public.\"Users\" SET \"Name\"=$1 WHERE \"ID\"=$2";
	const char** paramValues = new const char* [2];
	for (int i = 0; i < 2; i++) {
		paramValues[i] = new const char[100];
	}
	paramValues[0] = name.c_str();
	paramValues[1] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 2, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_update_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(users, "Yes");
	ask.set_last_text("No");
	ask.start();
}

void Uaccount() {
	account();
	int id;
	std::string login;

	get_update_idtext(login, id, "Enter new login: ");

	std::string SQL = "UPDATE public.\"Account\" SET \"Login\"=$1 WHERE \"ID\"=$2";
	const char** paramValues = new const char* [2];
	for (int i = 0; i < 2; i++) {
		paramValues[i] = new const char[100];
	}
	paramValues[0] = login.c_str();
	paramValues[1] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 2, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_update_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(account, "Yes");
	ask.set_last_text("No");
	ask.start();
}

void Umessages() {
	messages();
	int id;
	std::string text;

	get_update_idtext(text, id, "Enter new text: ");

	std::string SQL = "UPDATE public.\"Messages\" SET \"Text\"=$1 WHERE \"ID\"=$2";
	const char** paramValues = new const char* [2];
	for (int i = 0; i < 2; i++) {
		paramValues[i] = new const char[1000];
	}
	paramValues[0] = text.c_str();
	paramValues[1] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 2, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_update_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(messages, "Yes");
	ask.set_last_text("No");
	ask.start();
}

void Ufolders() {
	folders();
	int id;
	std::string name;

	get_update_idtext(name, id, "Enter new name: ");

	std::string SQL = "UPDATE public.\"Folders\" SET \"Name\"=$1 WHERE \"ID\"=$2";
	const char** paramValues = new const char* [2];
	for (int i = 0; i < 2; i++) {
		paramValues[i] = new const char[100];
	}
	paramValues[0] = name.c_str();
	paramValues[1] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 2, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_update_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(folders, "Yes");
	ask.set_last_text("No");
	ask.start();
}
