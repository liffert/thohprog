#include "Header.h"

Game::Snake::Snake(const rect field) : field(field) {
	body.push_back(Block(this->field.x1 + 2, this->field.y1 + 2));
}

Game::Snake::~Snake() {
}

void Game::Snake::show() const {
	this->clear();
	int  i = 0;
	for (auto iter : body) {
		iter.show(i + '0');
		i++;
	}
}
bool Game::Snake::move() {
	int m = 0;
	bool flag = false;
	if (state.left) {
		this->clear();
		Block n(body.begin()->get_x() - 1, body.begin()->get_y());
		if (body.size() == 1) {
			body.begin()->add_move(MOVE::left);
			flag = true;
		}
		else if (!body[1].compare(n)) {
			add_body_moves(MOVE::left);
			flag = true;
		}
		else {
			flag = false;
		}
		m = MOVE::left;
	}
	else if (state.right) {
		this->clear();
		Block n(body.begin()->get_x() + 1, body.begin()->get_y());
		if (body.size() == 1) {
			body.begin()->add_move(MOVE::right);
			flag = true;
		}
		else if (!body[1].compare(n)) {
			add_body_moves(MOVE::right);
			flag = true;
		}
		else {
			flag = false;
		}
		m = MOVE::right;
	}
	else if (state.down) {
		this->clear();
		Block n(body.begin()->get_x(), body.begin()->get_y() + 1);
		if (body.size() == 1) {
			body.begin()->add_move(MOVE::down);
			flag = true;
		}
		else if (!body[1].compare(n)) {
			add_body_moves(MOVE::down);
			flag = true;
		}
		else {
			flag = false;
		}
		m = MOVE::down;
	}
	else if (state.up) {
		this->clear();
		Block n(body.begin()->get_x(), body.begin()->get_y() - 1);
		if (body.size() == 1) {
			body.begin()->add_move(MOVE::up);
			flag = true;
		}
		else if (!body[1].compare(n)) {
			add_body_moves(MOVE::up);
			flag = true;
		}
		else {
			flag = false;
		}
		m = MOVE::up;
	}

	if (flag) {
		for (int i = 0; i < body.size(); i++) {
			body[i].move();
		}
	}

	if (eat->compare(body[0]) && eat->eat_status()) {
		int x = body.back().get_x();
		int y = body.back().get_y();

		int size = body.size();
		if (size != 1) { m = body.back().get().begin()->get(); }

		switch (m) {
		case MOVE::down: {
			body.push_back(Block(x, y - 1));
			break;
		}
		case MOVE::up: {
			body.push_back(Block(x, y + 1));
			break;
		}
		case MOVE::left: {
			body.push_back(Block(x + 1, y));
			break;
		}
		case MOVE::right: {
			body.push_back(Block(x - 1, y));
			break;
		}
		}
		if (size != 1) { body.back().add_move((body.end() - 2)->get().begin()->get()); }
		else { body.back().add_move(m); }
		body.back().add_move((body.end() - 2)->get());
		eat->eating();
	}

	check_end();
	return flag;
}
void Game::Snake::set_eat(Block* &eat) {
	this->eat = eat;
}
void Game::Snake::change_status(const int m) {
	if (m == MOVE::left) {
		state.clear();
		state.left = true;
	}
	else if (m == MOVE::right) {
		state.clear();
		state.right = true;
	}
	else if (m == MOVE::up) {
		state.clear();
		state.up = true;
	}
	else if (m == MOVE::down) {
		state.clear();
		state.down = true;
	}
}
bool Game::Snake::check_with_body(const Block temp) const {
	for (auto iter : body) {
		if (iter.compare(temp)) {
			return false;
		}
	}
	return true;
}
Game::rect Game::Snake::get_field() const {
	return field;
}
int Game::Snake::get_body_size() const {
	return body.size();
}
void Game::Snake::clear() const {
	for (auto iter : body) {
		iter.show(' ');
	}
}

void Game::Snake::check_end() const {
	for (auto iter = body.begin() + 1; iter != body.end(); iter++) {
		if (iter->compare(body[0])) {
			Game::end_game(field);
		}
	}
	int x = body.begin()->get_x();
	int y = body.begin()->get_y();
	if (x >= field.x2 || x <= field.x1 || y <= field.y1 || y >= field.y2) {
		Game::end_game(field);
	}
}

void Game::Snake::add_body_moves(const int move) {
	for (int i = 0; i < body.size(); i++) {
		body[i].add_move(move);
	}
}
