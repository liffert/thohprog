#include "Insert.h"
#include "Menu.h"
#include "Select.h"
#include <ctime>

#define ERRORID -1

int check_count_err(std::string table) {
	std::string SQL = "SELECT * FROM public.\"" + table + "\"";
	PGresult*count = PQexec(Conn.conn, SQL.c_str());
	if (PQresultStatus(count) != PGRES_TUPLES_OK) {
		std::cout << "Select ERRROR - " << PQresultErrorMessage(count) << std::endl;
		system("pause");
		return ERRORID;
	}
	return PQntuples(count);
}

bool check_insert_error(const PGresult *res) {
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Insert ERROR - " << PQresultErrorMessage(res) << std::endl;
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
void Iusers() {
	struct data {
		std::string name = "";
		int day = 0;
		int month = 0;
		int year = 0;
		int number = 0;
		int id = ERRORID;

		int paramN = 4;
		const char** paramValues;
		std::string date = "";
		std::string get_sql() {
			date = "'" + std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "'";
			std::string SQL = "INSERT INTO public.\"Users\" VALUES ($1, $2, $3, $4)";
			
			paramValues = new const char* [paramN];
			for (int i = 0; i < paramN; i++) {
				paramValues[i] = new const char[100];
			}

			paramValues[0] = name.c_str();
			paramValues[1] = date.c_str();
			paramValues[2] = get_num_pointer(number);
			paramValues[3] = get_num_pointer(id + 1);
			
			return SQL;
		}
	}; struct data var;

	insert_data(var.name, var.year, var.month, var.day, var.number);
	var.id = check_count_err("Users");

	if (var.id == ERRORID) { return; }
	PGresult* res = PQexecParams(Conn.conn, var.get_sql().c_str(), var.paramN, nullptr, var.paramValues, nullptr, nullptr, 0);

	if (!check_insert_error(res)) { return; }
	
	Menu ask;
	ask.set_headline("Insert done. Show table?");
	ask.set_func(users, "Yes");
	ask.set_last_text("No");
	ask.set_ask();
	ask.start();
}


void Iaccount() {
	struct data {
		std::string login = "";
		std::string password = "";
		int id = ERRORID;
		int paramN = 4;
		std::string secure;

		const char** paramValues;
		std::string get_sql() {
			std::string SQL = "INSERT INTO public.\"Account\" VALUES ($1, $2, $3, $4)";

			paramValues = new const char* [paramN];
			for (int i = 0; i < paramN; i++) {
				paramValues[i] = new const char[100];
			}

			paramValues[0] = login.c_str();;
			paramValues[1] = password.c_str();
			paramValues[2] = get_num_pointer(id + 1);
			paramValues[3] = secure.c_str();
			return SQL;
		}
	}; struct data var;

	insert_data(var.login, var.password, var.secure);

	var.id = check_count_err("Account");

	if (var.id == ERRORID) { return; }

	PGresult* res = PQexecParams(Conn.conn, var.get_sql().c_str(), var.paramN, nullptr, var.paramValues, nullptr, nullptr, 0);

	if (!check_insert_error(res)) { return; }

	Menu ask;
	ask.set_headline("Insert done. Show table?");
	ask.set_func(account, "Yes");
	ask.set_last_text("No");
	ask.set_ask();
	ask.start();
}

char* get_array_ptr(std::string arr) {
	char* pointer = new char[arr.length() + 1];
	for (int i = 0; i < arr.length(); i++) {
		pointer[i] = arr[i];
	}
	pointer[arr.length()] = '\0';
	return pointer;
}
void Imessages() {
	struct data {
		std::string Text = "";
		int day = 0;
		int month = 0;
		int year = 0;
		int files_count = 0;
		std::vector<std::string> Recipient;
		int id = ERRORID;

		int paramN = 5;
		const char** paramValues;
		std::string date = "";
		std::string get_sql() {
			std::string recipient = "{ ";
			for (int i = 0; i < Recipient.size(); i++) {
				recipient = recipient + "\"" + Recipient[i] + "\", ";
			}
			recipient.pop_back();
			recipient.pop_back();
			recipient = recipient + " }";

			date = "'" + std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "'";

			std::string SQL = "INSERT INTO public.\"Messages\" VALUES ($1, $2, $3, $4, $5)";

			paramValues = new const char* [paramN];
			for (int i = 0; i < paramN; i++) {
				paramValues[i] = new const char[100];
			}

			paramValues[0] = date.c_str();
			paramValues[1] = get_num_pointer(files_count);
			paramValues[2] = get_num_pointer(id + 1);
			paramValues[3] = Text.c_str();
			paramValues[4] = get_array_ptr(recipient);
			
			return SQL;
		}

	}; struct data var;

	insert_data(var.Text, var.year, var.month, var.day, var.files_count, var.Recipient);

	var.id = check_count_err("Messages");

	if (var.id == ERRORID) { return; }

	PGresult* res = PQexecParams(Conn.conn, var.get_sql().c_str(), var.paramN, nullptr, var.paramValues, nullptr, nullptr, 0);

	if (!check_insert_error(res)) { return; }

	Menu ask;
	ask.set_headline("Insert done. Show table?");
	ask.set_func(messages, "Yes");
	ask.set_last_text("No");
	ask.set_ask();
	ask.start();
}

void Ifolders() {
	struct data {
		std::string name = "";
		int day = 0;
		int month = 0;
		int year = 0;
		int id = ERRORID;

		int paramN = 3;
		const char** paramValues;
		std::string date = "";
		std::string get_sql() {
			date = "'" + std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "'";
			std::string SQL = "INSERT INTO public.\"Folders\" VALUES ($1, $2, $3)";

			paramValues = new const char* [paramN];
			for (int i = 0; i < paramN; i++) {
				paramValues[i] = new const char[100];
			}

			paramValues[0] = date.c_str();
			paramValues[1] = get_num_pointer(id + 1);
			paramValues[2] = name.c_str();
			return SQL;
		}
	}; struct data var;

	insert_data(var.name, var.year, var.month, var.day);

	var.id = check_count_err("Folders");

	if (var.id == ERRORID) { return; }

	PGresult* res = PQexecParams(Conn.conn, var.get_sql().c_str(), var.paramN, nullptr, var.paramValues, nullptr, nullptr, 0);

	if (!check_insert_error(res)) { return; }

	Menu ask;
	ask.set_headline("Insert done. Show table?");
	ask.set_func(folders, "Yes");
	ask.set_last_text("No");
	ask.set_ask();
	ask.start();
}

void random() {
	struct data {
		std::string login = "";
		std::string password = "";
		int id = ERRORID;
		int paramN = 4;
		std::string secure;

		const char** paramValues;
		std::string get_sql() {
			std::string SQL = "INSERT INTO public.\"Account\" VALUES ($1, $2, $3, $4)";

			paramValues = new const char* [paramN];
			for (int i = 0; i < paramN; i++) {
				paramValues[i] = new const char[100];
			}

			paramValues[0] = login.c_str();;
			paramValues[1] = password.c_str();
			paramValues[2] = get_num_pointer(id + 1);

			paramValues[3] = secure.c_str();
			return SQL;
		}


		void create_rand_params() {
			login.clear();
			password.clear();
			id = ERRORID;
			int temp = rand() % 10 + 2;
			for (int i = 0; i < temp; i++) {
				int symb = 65;
				login = login + static_cast<char>(symb + rand()%26);
			}
			for (int i = 0; i < 8; i++) {
				int symb = 65;
				password = password + static_cast<char>(symb + rand() % 26);
			}

			if (rand() % 2 == 1) {
				secure = "t";
			}
			else {
				secure = "f";
			}
		}
	}; struct data var;

	int count = 0;
	std::cout << "Randrom 5 - 10000 str in table 'account'\nEnter count: ";
	std::cin >> count;
	CIN_ELIMINATION_ERROR(false);
	if (count < 5) {
		count = 5;
	}
	else if (count > 10000) {
		count = 10000;
	}
	srand(time(NULL));
	for (int i = 0; i < count; i++) {
		var.create_rand_params();
		var.id = check_count_err("Account");

		if (var.id == ERRORID) { return; }
		PGresult* res = PQexecParams(Conn.conn, var.get_sql().c_str(), var.paramN, nullptr, var.paramValues, nullptr, nullptr, 0);
		if (!check_insert_error(res)) { return; }
	}

	Menu ask;
	ask.set_headline("Insert done. Show table?");
	ask.set_func(account, "Yes");
	ask.set_last_text("No");
	ask.set_ask();
	ask.start();

}


