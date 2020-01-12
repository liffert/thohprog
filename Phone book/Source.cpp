#include "Pbook.h"
#include <ctime>

std::string Random() {
	std::string temp;
	for (int i = 0; i < 12; i++) {
		temp = temp + std::to_string(std::rand() % 10);
	}
	return temp;
}

int main() {
	std::srand(std::time(NULL));
	std::string name = "Dimasik";
	Pbook book;
	for (int i = 0; i < 10; i++) {
		book.add(name + std::to_string(rand() % 10), name + std::to_string(rand() % 100), Random());
	}
	book.show();

	std::string a;
	auto res = book.find();
	system("cls");
	for (auto iter : res) {
		std::cout << iter.first.get_full_name() << std::endl;
	}
}