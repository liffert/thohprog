#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <conio.h>

class Pbook {

private:
	class names {
	public:
		names(std::string Fname, std::string Lname) : Fname(Fname), Lname(Lname) {}
		~names() {}

		std::string get_full_name() const;
		std::string get_Lname()const;
		std::string get_Fname()const;

	private:
		std::string Fname;
		std::string Lname;
	};
	std::map<std::string, names> book;

public:
	Pbook() {}
	~Pbook() {}

	void add(std::string Fname, std::string Lname, std::string num);
	void show() const;

	void find(std::string Find);
	std::vector<std::pair<names, std::string>> find();


};

