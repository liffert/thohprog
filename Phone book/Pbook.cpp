#include "Pbook.h"



void Pbook::add(std::string Fname, std::string Lname, std::string num) {
	auto Find = book.find(num);
	if (Find != book.end()) {
		int a;
		std::cout << "This num is alredy exist\n";
		std::cout << (*Find).first << "\t" << (*Find).second.get_full_name() << std::endl
			<< "You want change them? (1 yes, other num - no): ";
		std::cin >> a;
		if (a != 1) { return; }
	}
	names temp(Fname, Lname);
	book.emplace(std::make_pair(num, temp));
}
void Pbook::show()const {
	for (auto iter : book) {
		std::cout << iter.first << "\t" << iter.second.get_full_name() << std::endl;
	}
}
void Pbook::find(std::string Find) {
	auto F = book.find(Find);
	if (F != book.end()) {
		std::cout << (*F).first << "\t" << (*F).second.get_full_name() << std::endl;
	}
	else {
		std::cout << "NO";
	}
}

std::vector<std::pair<Pbook::names, std::string>> Pbook::find() {
	std::string F;
	std::string temp;
	std::vector<std::pair<names, std::string>> current;

	while (1) {
		int a = _getch();
		if (a == 13) {
			return current;
		}
		current.clear();
		if (a != 8) {
			F = F + static_cast<char>(a);
		}
		else if (F.length() != 0) {
			F.pop_back();
		}
		for (auto iter : book) {
			if (F.length() > iter.first.length()) {
				continue;
			}
			for (int i = 0; i < F.length(); i++) {
				temp = temp + iter.first[i];
			}
			if (F == temp) {
				current.push_back(std::make_pair(iter.second, iter.first));
			}
			temp.clear();
		}
		system("cls");
		std::cout << F << std::endl;
		for (auto iter : current) {
			std::cout << iter.first.get_full_name() << "\t-\t" << iter.second << std::endl;
		}
	}
}


std::string Pbook::names::get_full_name() const {
	return Fname + " " + Lname;
}

std::string Pbook::names::get_Lname()const {
	return Lname;
}
std::string Pbook::names::get_Fname()const {
	return Fname;
}