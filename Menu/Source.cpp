#include "Menu.h"

class A {

public:
	A() {}
	~A() {}

	static void a() {
		std::cout << "hello";
	}
};
void func3() {
	Menu ask;
	ask.set_ask();
	ask.set_func([]() {}, "One-two");
	ask.set_func([]() {}, "Two-two");
	ask.set_last_text("Back");
	switch (ask.start()) {
	case 1:
		//do
		break;
	case 2:
		//do
		break;
	}
}

void a(int b, int c) {
	std::cout << b + c << std::endl;
}

int main() {
	Menu main;
	main.set_headline("Test");
	main.prestartF(a, 10, 10);
	main.set_func(&func3, "One");
	main.set_func(&A::a, "Two");
	main.start();
}