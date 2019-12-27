#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <libpq-fe.h>
#include <math.h>

struct connection {
	std::string host = "127.0.0.1";
	std::string name = "postgres";
	std::string user = "postgres";
	std::string pass = "21digitize";
	int port = 5432;
	PGconn* conn = nullptr;

	ConnStatusType start() {
		conn = PQsetdbLogin(host.c_str(), std::to_string(port).c_str(), nullptr, nullptr, name.c_str(), user.c_str(), pass.c_str());
		return PQstatus(conn);
	}
};extern struct connection Conn;

void insert_data(std::string& name, int& year, int& month, int& day, int &number);
void insert_data(std::string& login, std::string& passsword, std::string& secure);
void insert_data(std::string& Text, int& year, int& month, int& day, int& files_count, std::vector<std::string> &Recipient);
void insert_data(std::string& name, int& year, int& month, int& day);

std::string select_search(std::string text);
void select_data(std::string &secure, std::string &name);

int delete_id();

void get_update_idtext(std::string& text, int& id, const std::string out);