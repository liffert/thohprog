#include "Brezenhem.h"
#include "Header.h"
#include "DDA.h"
#include "Woo.h"
#include "Test.h"

int main() {
	{
		//Console settings
		CONSOLE_FONT_INFOEX fontinfo;
		fontinfo.cbSize = sizeof(fontinfo);
		fontinfo.FontFamily = FF_SCRIPT;
		wcscpy_s(fontinfo.FaceName, L"Terminal");
		fontinfo.dwFontSize.X = 8;
		fontinfo.dwFontSize.Y = 9;
		SetCurrentConsoleFontEx(hStdOut, FALSE, &fontinfo);

		COORD screen = { 1400, 800 };
		SetConsoleScreenBufferSize(hStdOut, screen);
		MoveWindow(GetConsoleWindow(), 100, 100, screen.X, screen.Y, TRUE);
		////////////////////////////////////////////////////////////////////
	}


	Brezenhem temp;
	Test test;
	std::vector<double> results;
	results = test.test();
	system("cls");

	std::cout << "Brezenhem: " << results[0] << std::endl << "DDA: " << results[1] << std::endl << "Woo: " << results[2];
	
	system("color 50");//делает фиолетовую консоль
	_getch();
	system("cls");
	gotoxy(0, 0);
	std::cout << "Circle: ";
	SetConsoleTextAttribute(hStdOut, 69);
	temp.circle(50, 13, 10);


	gotoxy(0, 30);
	SetConsoleTextAttribute(hStdOut, 7);
	std::cout << "Brezenhem					DDA 						Woo";
	SetConsoleTextAttribute(hStdOut, 14);
	temp.line(0, 31, 50, 50);
	
	SetConsoleTextAttribute(hStdOut, 22);
	DDA tempd;
	tempd.line(50, 31, 100, 50);

	Woo tempw;
	SetConsoleTextAttribute(hStdOut, 58);
	tempw.line(100, 31, 150, 50);

	gotoxy(0, 83);
	SetConsoleTextAttribute(hStdOut, 7);

	///D//
	temp.line(5, 84, 8, 84);
	temp.line(5, 84, 5, 87);
	temp.line(8, 84, 8, 87);
	temp.line(3, 87, 10, 87);
	temp.line(3, 87, 3, 90);
	temp.line(10, 87, 10, 90);
	//////
	///M//
	temp.line(12, 84, 12, 90);
	temp.line(12, 84, 15, 87);
	temp.line(18, 84, 15, 87);
	temp.line(18, 84, 18, 90);
	////
	//и//
	temp.line(20, 84, 20, 90);
	temp.line(26, 84, 20, 90);
	temp.line(26, 84, 26, 90);
	///
	//T///
	temp.line(28, 84, 34, 84);
	temp.line(31, 84, 31, 90);
	///
	///R
	temp.line(36, 84, 36, 90);
	temp.line(36, 84, 40, 84);
	temp.line(36, 87, 40, 87);
	temp.line(40, 84, 40, 87);
	////
	///O///
	temp.circle(46, 87, 3);


	gotoxy(0, 91);
	
	return 0;
}