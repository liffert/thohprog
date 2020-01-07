#include "Header.h"


void Game::create_field(rect Square) {
	for (int i = Square.x1; i <= Square.x2; i++) {
		gotoxy(i, Square.y1);
		std::cout << "*";
		gotoxy(i, Square.y2);
		std::cout << "*";
	}

	for (int i = Square.y1; i <= Square.y2; i++) {
		gotoxy(Square.x1, i);
		std::cout << "*";
		gotoxy(Square.x2, i);
		std::cout << "*";
	}
}
void Game::start() {

	int last_key = 0;
	end_flag = false;
	std::srand(0);
	res.time = std::clock();

	create_field(field);
	//100 115 97 119

	int speed = 150;
	Snake snake(field);
	std::clock_t time;
	std::clock_t press_time = 0;
	time = std::clock();
	Block* eat = Game::eat_generator(snake);
	eat->show('@');
	snake.set_eat(eat);

	move_t prew_move;
	while (!end_flag) {
		if (_kbhit() && (std::clock() - press_time) >= speed) {
			bool flag = true;
			int a = _getch();
			if (a != last_key) {
				switch (a) {
				case 100:
					snake.change_status(Game::MOVE::right);
					if (!snake.move()) {
						snake.change_status(prew_move.get());
						flag = false;
					}
					else {
						prew_move.clear();
						prew_move.right = true;
						res.moves++;
					}
					snake.show();
					last_key = a;
					break;
				case 115:
					snake.change_status(Game::MOVE::down);
					if (!snake.move()) {
						snake.change_status(prew_move.get());
						flag = false;
					}
					else {
						prew_move.clear();
						prew_move.down = true;
						res.moves++;
					}
					snake.show();
					last_key = a;
					break;
				case 97:
					snake.change_status(Game::MOVE::left);
					if (!snake.move()) {
						snake.change_status(prew_move.get());
						flag = false;
					}
					else {
						prew_move.clear();
						prew_move.left = true;
						res.moves++;
					}
					snake.show();
					last_key = a;
					break;
				case 119:
					snake.change_status(Game::MOVE::up);
					if (!snake.move()) {
						snake.change_status(prew_move.get());
						flag = false;
					}
					else {
						prew_move.clear();
						prew_move.up = true;
						res.moves++;
					}
					snake.show();
					last_key = a;
					break;
				}
				if (flag) {
					time = std::clock();
				}
			}
			press_time = std::clock();
		}
		else if ((std::clock() - time) >= speed) {
			snake.move();
			snake.show();
			time = std::clock();
		}
		if (!eat->eat_status()) {
			delete eat;
			eat = eat_generator(snake);
			eat->show('@');
			snake.set_eat(eat);
		}
	}

	res.time = std::clock() - res.time;
	res.results = snake.get_body_size();
}
const Game::results_t Game::get_results(){
	return res;
}
Game::Block Game::new_el(rect Square) {
	int x = std::rand() % Square.x2;
	if (x < Square.x1) {
		x = x + Square.x1;
	}
	int y = std::rand() % Square.y2;
	if (y < Square.y1) {
		y = y + Square.y1;
	}
	return Block(x, y);
}

void Game::setup_field(rect field) {
	if (field.x1 == field.x2 || field.y1 == field.y2) {
		std::cerr << "ERROR change field";
		system("pause");
	}
	else {
		Game::field = field;
	}
}

void Game::setup_field(int x1, int y1, int x2, int y2) {
	if (x2 == x1 || y1 == y2) {
		std::cerr << "ERROR change field";
		system("pause");
	}
	else {
		field = rect{ x1, y1, x2, y2 };
	}
}

Game::Block* Game::eat_generator(const Snake g) {
	std::srand(std::time(NULL));
	rect field = g.get_field();
	while (1) {
		int x = std::rand() % field.x2;
		while(x <= field.x1) {
			x = field.x1 + rand() % ((field.x2 - field.x1) / 2);
		}
		int y = std::rand() % field.y2;
		while (y <= field.y1) {
			y = field.y1 + rand() % ((field.y2 - field.y1) / 2);
		}
		Block* n = new Block{ x, y, true };
		if (g.check_with_body(*n)) {
			return n;
		}
	}
}

int Game::Move::get() {
	if (up) {
		return MOVE::up;
	}
	else if (left) {
		return MOVE::left;
	}
	else if (right) {
		return MOVE::right;
	}
	else if (down) {
		return MOVE::down;
	}
	else {
		return NAN;
	}
}

void Game::end_game(rect field) {
	end_flag = true;
}

void Game::gotoxy(int X, int Y) {
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}