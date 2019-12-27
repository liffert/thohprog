#include "menu.h"
#include "Header.h"
#define MENU_FUNC 2
#pragma warning (disable: 4996)
HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO structCursorInfo;
void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}
void draw_menu(int selection) {
	system("cls");
	char options[MENU_FUNC][255] = { "Play by index", "Exit" };
	for (int i = 0; i < MENU_FUNC; i++) {
		gotoxy(50, 10 + i);
		if (i == selection) {
			SetConsoleTextAttribute(hStdOut, 5);
			printf("%d. %s", i + 1, options[i]);
		}
		else {
			SetConsoleTextAttribute(hStdOut, 7);
			printf("%d. %s", i + 1, options[i]);
		}
	}
}
void control_loop() {
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	int zinderg = 0;

	while (1) {
		draw_menu(zinderg);
		int nextchar = getch();
		switch (nextchar) {
		case 224: {
			int t = getch();
			if (t == 80 && zinderg < MENU_FUNC - 1) { zinderg++; }
			else if (t == 72 && zinderg > 0) { zinderg--; }
			break;
		}
		case 13: {
			switch (zinderg) {
			case 0: play(-1); break;
			case 1: exit(1);
			}
		}
		}
	}
}