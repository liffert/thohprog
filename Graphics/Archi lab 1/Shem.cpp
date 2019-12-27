#include "Shem.h"

void Shem::start() {
	std::cout << "Enter to start stop";

	Kva CPU(10, 10, "CPU");
	CPU.print();
	Line DB(21, 13, 10, true, "DB");
	DB.print();
	DB.left_arrow();
	DB.right_arrow();
	Line CB(21, 18, 10, true, "CB");
	CB.print();
	CB.left_arrow();
	CB.right_arrow();
	Line AB(21, 23, 10, true, "AB");
	AB.print();
	AB.right_arrow();

	Kva DLU(32, 10, "DLU");
	DLU.print();
	Line control(43, 13, 10, true, "Control");
	control.print();
	control.right_arrow();
	Line ready(43, 23, 10, true, "Ready");
	ready.print();
	ready.left_arrow();

	Kva OBJ(54, 10, "OBJ");
	OBJ.print();

	Brezenhem temp;
	temp.circle(59, 19, 1);
	gotoxy(57, 21);
	std::cout << "Start";
	gotoxy(57, 23);
	SetConsoleTextAttribute(hStdOut, 3);
	std::cout << "Stop";
	SetConsoleTextAttribute(hStdOut, 7);


	std::thread *bl = NULL;
	bool flag = true;
	while (1) {
		int ch = _getch();
		if (ch == 13) {
			if (flag) {
				bl = new std::thread(&Element::blink, &control);
				ready.on();
				DB.on();
				CB.on();
				AB.on();
				bl->detach();
				flag = false;
				SetConsoleTextAttribute(hStdOut, 3);
				gotoxy(57, 21);
				std::cout << "Start";
				SetConsoleTextAttribute(hStdOut, 7);
				gotoxy(57, 23);
				std::cout << "Stop";
			}
			else {
				bl->~thread();
				ready.stop();
				DB.stop();
				CB.stop();
				AB.stop();
				control.stop();
				gotoxy(57, 21);
				std::cout << "Start";
				gotoxy(57, 23);
				SetConsoleTextAttribute(hStdOut, 3);
				std::cout << "Stop";
				SetConsoleTextAttribute(hStdOut, 7);
				return;
			}
		}
	}
}
