#include "Header.h"



void setup_console() {
	//Console settings
	CONSOLE_FONT_INFOEX fontinfo;
	fontinfo.cbSize = sizeof(fontinfo);
	fontinfo.FontFamily = FF_SCRIPT;
	wcscpy_s(fontinfo.FaceName, L"Terminal");
	fontinfo.dwFontSize.X = 18;
	fontinfo.dwFontSize.Y = 18;
	SetCurrentConsoleFontEx(Game::hStdOut, FALSE, &fontinfo);

	COORD screen = { 1400, 800 };
	SetConsoleScreenBufferSize(Game::hStdOut, screen);
	MoveWindow(GetConsoleWindow(), 100, 100, screen.X, screen.Y, TRUE);

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(Game::hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(Game::hStdOut, &structCursorInfo);

	////////////////////////////////////////////////////////////////////
}

int main() {
	setup_console();
	//Game::setup_field(Game::rect{ 10, 10, 20, 20 });
	Game::change_speed(90);
	Game::start();
	const Game::results_t temp = Game::get_results();


	Game::gotoxy(0, Game::field.y2 + 5);
	std::cout << "Time in game:: " << temp.time / CLOCKS_PER_SEC << "\nMoves: " << temp.moves << "\nResult(body size): " << temp.results << std::endl;
	system("pause");
}