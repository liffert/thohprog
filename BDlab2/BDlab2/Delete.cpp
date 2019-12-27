#include "Delete.h"
#include "Menu.h"
#include "Select.h"

static char* get_num_pointer(int num) {
	std::string Num = std::to_string(num);
	char* p = new char[Num.length() + 1];
	for (int i = 0; i < Num.length(); i++) {
		p[i] = Num[i];
	}
	p[Num.length()] = '\0';

	return p;
}
bool check_delete_error(const PGresult* res) {
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Delete ERROR - " << PQresultErrorMessage(res) << std::endl;
		system("pause");
		return false;
	}
	return true;
}
void Dusers() {
	users();
	int id = delete_id();

	std::string SQL = "DELETE FROM public.\"Users\" WHERE \"ID\"=$1";
	const char** paramValues = new const char* [1];
	paramValues[0] = new const char[100];
	paramValues[0] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_delete_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(users, "Yes");
	ask.set_last_text("No");
	ask.start();
}

void Daccount() {
	account();

	int id = delete_id();
	std::string SQL = "DELETE FROM public.\"Account\" WHERE \"ID\"=$1";
	const char** paramValues = new const char* [1];
	paramValues[0] = new const char[100];
	paramValues[0] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_delete_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(account, "Yes");
	ask.set_last_text("No");
	ask.start();
}

void Dmessages() {
	messages();
	int id = delete_id();

	std::string SQL = "DELETE FROM public.\"Messages\" WHERE \"ID\"=$1";
	const char** paramValues = new const char* [1];
	paramValues[0] = new const char[100];
	paramValues[0] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_delete_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(messages, "Yes");
	ask.set_last_text("No");
	ask.start();
}

void Dfolders() {
	folders();
	int id = delete_id();

	std::string SQL = "DELETE FROM public.\"Folders\" WHERE \"ID\"=$1";
	const char** paramValues = new const char* [1];
	paramValues[0] = new const char[100];
	paramValues[0] = get_num_pointer(id);
	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);

	if (!check_delete_error(res)) { return; }

	Menu ask;
	ask.set_ask();
	ask.set_headline("Show updated table?");
	ask.set_func(folders, "Yes");
	ask.set_last_text("No");
	ask.start();
}
