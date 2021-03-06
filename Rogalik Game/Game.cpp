#include "Game.h"
#include <iostream>

Game::Game(int n, int m) : n(n), m(m) {
	lvl = new LevelGeneration(n, m);
	MAP = lvl->get();
	int x;
	int y;

	lvl->get_start(x, y);
	x = x * pixelSize;
	y = y * pixelSize;
	Inintialization(x, y);
}

Game::~Game() {

}

void Game::Inintialization(int x, int y) {
	characters.clear();
	Hero hero("Hero", x, y, MAP, n, m);
	Weapon weap(x, y);
	characters.push_back(std::make_pair(hero, weap));
}

void Game::draw(sf::RenderTarget& target) {
	target.draw(*lvl);
	target.draw(characters.begin()->first);
	target.draw(characters.begin()->second);
	for (int i = 1; i < characters.size(); i++) {
		dynamic_cast<Enemy*>(&characters[i].first)->draw(target);
	}
	kick_hero(false);
}

void Game::Move_hero(int move) {
	characters.begin()->first.move(move);
	characters.begin()->second.move(characters.begin()->first.getX(), characters.begin()->first.getY());
}

void Game::kick_hero(bool state) {
	characters.begin()->second.set_kick(state);
}

int Game::get_hero_X() const {
	return characters.begin()->first.getX();
}

int Game::get_hero_Y() const {
	return characters.begin()->first.getY();
}

void Game::check_kick() {
	int x = 70;
	int y = 80;
	int x2 = x + 20;
	int y2 = y + 20;
	if (characters.begin()->second.kicked(x, x2, y, y2)) {
		std::cout << "Kick\n";
	}
	else {
		std::cout << "Not kick\n";
	}
}
