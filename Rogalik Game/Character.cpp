#include "Character.h"
#include "Game.h"

Character::Character(std::string name, bool enemy) : name(name), enemy(enemy) {
	sf::Image image;
	image.loadFromFile(Hero_path[hero_path::left]);
	Hero_textures[hero_path::left].loadFromImage(image);
	image.loadFromFile(Hero_path[hero_path::right]);
	Hero_textures[hero_path::right].loadFromImage(image);
	image.loadFromFile(Hero_path[hero_path::front]);
	Hero_textures[hero_path::front].loadFromImage(image);
	image.loadFromFile(Hero_path[hero_path::back]);
	Hero_textures[hero_path::back].loadFromImage(image);
}

Character::~Character() {

}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite sprite;
	sprite.setTexture(Hero_textures[now_move]);
	sprite.setPosition(x, y);
	sprite.setScale(0.01, 0.01);
	target.draw(sprite, states);
}

void Character::move(int move) {
	switch (move) {
	case Game::MOVE::DOWN:
		y = y + step;
		now_move = hero_path::front;
		break;
	case Game::MOVE::UP:
		y = y - step;
		now_move = hero_path::back;
		break;
	case Game::MOVE::LEFT:
		now_move = hero_path::left;
		x = x - step;
		break;
	case Game::MOVE::RIGHT:
		now_move = hero_path::right;
		x = x + step;
		break;
	}
}

int Character::getY() const {
	return y;
}

int Character::getX() const {
	return x;
}
