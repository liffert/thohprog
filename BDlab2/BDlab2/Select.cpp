#include "Menu.h"
#include "Select.h"

void users() {
	PGresult* res = PQexec(Conn.conn, "SELECT * FROM public.\"Users\"");
	print(res);
	system("pause");
}
void messages() {
	PGresult* res = PQexec(Conn.conn, "SELECT * FROM public.\"Messages\"");
	print(res);
	system("pause");
}
void account() {
	PGresult* res = PQexec(Conn.conn, "SELECT * FROM public.\"Account\"");
	print(res);
	system("pause");
}
void folders() {
	PGresult* res = PQexec(Conn.conn, "SELECT * FROM public.\"Folders\"");
	print(res);
	system("pause");
}

void static_selectj() {
	std::string SQL = "SELECT * FROM public.\"Account\" INNER JOIN public.\"Users\" On public.\"Account\".\"ID\" = public.\"Users\".\"ID\" WHERE public.\"Account\".\"Secure\" = 't' and public.\"Users\".\"Name\" = 'Katy Loud'";
	PGresult* res = PQexec(Conn.conn, SQL.c_str());
	print(res);
	system("pause");
}

void dynamic_selectj() {
	std::string SQL = "SELECT * FROM public.\"Account\" INNER JOIN public.\"Users\" On public.\"Account\".\"ID\" = public.\"Users\".\"ID\" WHERE public.\"Account\".\"Secure\" = $1 and public.\"Users\".\"Name\" = $2";
	const char** paramValues = new const char*[2];
	for (int i = 0; i < 2; i++) {
		paramValues[i] = new const char[1000];
	}
	std::string secure;
	std::string name;

	select_data(secure, name);
	paramValues[0] = secure.c_str();
	paramValues[1] = name.c_str();

	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 2, nullptr, paramValues, nullptr, nullptr, 0);
	system("cls");
	print(res);
	system("pause");
}

void search() {
	std::string SQL = "SELECT * FROM public.\"Messages\" WHERE to_tsvector ('english', \"Text\") @@ to_tsquery ('english', $1)";

	std::string find = select_search("Enter word(search in messages text) : ");

	const char** paramValues = new const char* [1];
	paramValues[0] = new const char[1000];
	paramValues[0] = find.c_str();

	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
	print(res);
	system("pause");
}

void not_search() {
	std::string SQL = "SELECT * FROM public.\"Messages\" WHERE to_tsvector ('english', \"Text\") @@ to_tsquery ('english', $1)";

	std::string find = select_search("Enter word(search in messages text) !: ");
	
	find.insert(0, "!");
	const char** paramValues = new const char* [1];
	paramValues[0] = new const char[1000];
	paramValues[0] = find.c_str();

	PGresult* res = PQexecParams(Conn.conn, SQL.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);
	print(res);
	system("pause");
}

