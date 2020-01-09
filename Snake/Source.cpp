#include "Header.h"
#include "Menu.h"

void start_game() {
	system("cls");
	Game::setup_console();
	Game::start();
	Game::setup_console(12, 18);
}
void change_speed() {
	system("cls");
	std::cout << "Input new speed\nCurrent speed - " << Game::speed << ": ";
	int speed;
	std::cin >> speed;
	CIN_ELIMINATION_ERROR(false);
	Game::change_speed(speed);
}
void change_field() {
	system("cls");
	std::cout << "Input new field\nCurrent field:\n"
			  << "X1: " << Game::field.x1 << "\tX2: " << Game::field.x2 << "\nY1: " << Game::field.y1 << "\tY2: " << Game::field.y2 << std::endl;

	Game::rect temp;
	std::cout << "Input x1: ";
	std::cin >> temp.x1;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Input x2: ";
	std::cin >> temp.x2;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Input y1: ";
	std::cin >> temp.y1;
	CIN_ELIMINATION_ERROR(false);
	std::cout << "Input y2: ";
	std::cin >> temp.y2;
	CIN_ELIMINATION_ERROR(false);
	Game::setup_field(temp);
}

int main() {
	Menu menu;
	menu.set_headline("Main");
	menu.set_func(&start_game, "Start");
	menu.set_func(&change_speed, "Change speed");
	menu.set_func(&change_field, "Change field");
	menu.set_last_text("Results");
	
	menu.prestartF(&Game::setup_console, 12, 18);
	menu.start();

	
	const Game::results_t temp = Game::get_results();

	Game::gotoxy(0, Game::field.y2 + 5);
	std::cout << "Time in game:: " << temp.time / CLOCKS_PER_SEC << "\nMoves: " << temp.moves << "\nResult(body size): " << temp.results << std::endl;
	system("pause");
	
}