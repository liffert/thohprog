#include "Header.h"

Game::Block::Block(int x, int y) {
	this->x = x;
	this->y = y;
}
Game::Block::Block(int x, int y, bool eat) {
	this->x = x;
	this->y = y;
	this->eat_s = eat;
}
Game::Block::~Block() {
}

bool Game::Block::compare(Block temp) {
	if (temp.x == x && temp.y == y) { return true; }
	return false;
}

int Game::Block::get_x() const {
	return x;
}

int Game::Block::get_y() const {
	return y;
}

void Game::Block::show(char symb) const {
	gotoxy(x, y);
	std::cout << symb;
	gotoxy(x, y);
}

bool Game::Block::eat_status() const {
	return eat_s;
}

void Game::Block::add_move(int move) {
	move_t temp;
	switch (move) {
	case MOVE::down: {
		temp.down = true;
		break;
	}
	case MOVE::left: {
		temp.left = true;
		break;
	}
	case MOVE::right: {
		temp.right = true;
		break;
	}
	case MOVE::up: {
		temp.up = true;
		break;
	}
	default:
		return;
	}
	moves.push_back(temp);
}

void Game::Block::add_move(std::vector<move_t> moves) {
	for (auto iter : moves) {
		this->moves.push_back(iter);
	}
}

void Game::Block::move() {
	auto iter = moves.begin();
	if (iter == moves.end()) { return; }
	switch (iter->get()) {
	case MOVE::down: {
		y++;
		break;
	}
	case MOVE::left: {
		x--;
		break;
	}
	case MOVE::right: {
		x++;
		break;
	}
	case MOVE::up: {
		y--;
		break;
	}
	default:
		return;
	}
	iter = moves.erase(iter);
}

int Game::Block::get_size_moves() const {
	return moves.size();
}

std::vector<Game::move_t> Game::Block::get() const {
	return moves;
}
