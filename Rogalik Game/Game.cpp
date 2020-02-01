#include "Game.h"
#include <iostream>
Game::Game(){
	Inintialization();
}

Game::~Game() {

}

void Game::Inintialization() {
	characters.clear();
	Character hero("Hero", false);
	int x1 = hero.getX();
	int y1 = hero.getY();
	Weapon weap(x1, y1);
	characters.push_back(std::make_pair(hero, weap));
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& iter : characters) {
		target.draw(iter.first, states);
		target.draw(iter.second, states);
	}
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
