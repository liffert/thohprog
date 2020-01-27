#include "Game.h"

Game::Game(){
	Inintialization();
}

Game::~Game() {

}

void Game::Inintialization() {
	characters.clear();
	characters.push_back(Character("Hero", false));
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& iter : characters) {
		target.draw(iter, states);
	}
}

void Game::Move_hero(int move) {
	characters.begin()->move(move);
}
