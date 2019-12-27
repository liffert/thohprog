#include "menu.h"

int main() {
	
	/*int c = _getch();

	std::cout << c;
	c = _getch();
	std::cout << c;
	getchar();*/
	system("chcp 1251");//переводим консоль в другую кодировку для адекватного отображения
	control_loop();
	return 0;
}