#include "Character.h"
#include "Game.h"

Character::Character(std::string name, bool enemy) : name(name), enemy(enemy) {
	sf::Image image;
	image.loadFromFile(path);
	texture.loadFromImage(image);
}

Character::~Character() {

}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	target.draw(sprite, states);
}

void Character::move(int move) {
	switch (move) {
	case Game::MOVE::DOWN:
		y = y + step;
		break;
	case Game::MOVE::UP:
		y = y - step;
		break;
	case Game::MOVE::LEFT:
		x = x - step;
		break;
	case Game::MOVE::RIGHT:
		x = x + step;
		break;
	}
}
