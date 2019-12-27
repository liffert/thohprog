#include "Header.h"
#include "Shem.h"


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

		COORD screen = { 1200, 800 };
		SetConsoleScreenBufferSize(hStdOut, screen);
		MoveWindow(GetConsoleWindow(), 100, 100, screen.X, screen.Y, TRUE);
		////////////////////////////////////////////////////////////////////
	}

	Shem shema;
	shema.start();

	gotoxy(0, 30);
	return 0;
}
