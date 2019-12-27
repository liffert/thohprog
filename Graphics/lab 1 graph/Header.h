#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <vector>

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
static void gotoxy(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}