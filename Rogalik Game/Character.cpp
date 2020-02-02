#include "Character.h"
#include "Game.h"

Character::Character(std::string name, int x, int y, char** MAP, int n, int m) : name(name), x(x), y(y), MAP(MAP), n(n), m(m) {
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
		if (ability_to_move(x, y + step)) {
			y = y + step;
		}
		now_move = hero_path::front;
		break;
	case Game::MOVE::UP:
		if (ability_to_move(x, y - step)) {
			y = y - step;
		}
		now_move = hero_path::back;
		break;
	case Game::MOVE::LEFT:
		if (ability_to_move(x - step, y)) {
			x = x - step;
		}
		now_move = hero_path::left;
		break;
	case Game::MOVE::RIGHT:
		now_move = hero_path::right;
		if (ability_to_move(x + step, y)) {
			x = x + step;
		}
		break;
	}
}

int Character::getY() const {
	return y;
}

int Character::getX() const {
	return x;
}

void Character::init() {
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

bool Character::ability_to_move(int x, int y) {
	if (MAP[y / pixelSize][x / pixelSize] != 'A' || MAP[y / pixelSize][(x + size) / pixelSize] != 'A' || MAP[(y + size)/ pixelSize][(x + size)/ pixelSize] != 'A' || MAP[(y + size)/ pixelSize][x/ pixelSize] != 'A') {
		return false;
	}
	else {
		return true;
	}
}


Hero::Hero(std::string name, int x, int y, char** MAP, int n, int m) : Character(name, x, y, MAP, n, m) {
	Hero_path[hero_path::left] = "Characters/Left.png";
	Hero_path[hero_path::right] = "Characters/Right.png";
	Hero_path[hero_path::front] = "Characters/Front.png";
	Hero_path[hero_path::back] = "Characters/Front.png";
	init();
}

Hero::~Hero() {
}

Enemy::Enemy(std::string name, int x, int y, char** MAP, int n, int m) : Character(name, x, y, MAP, n, m) {
	Hero_path[hero_path::left] = "Characters/Left.png";
	Hero_path[hero_path::right] = "Characters/Right.png";
	Hero_path[hero_path::front] = "Characters/Front.png";
	Hero_path[hero_path::back] = "Characters/Front.png";
	init();
}

Enemy::~Enemy() {
}

void Enemy::draw(sf::RenderTarget& target) {
	sf::Sprite sprite;
	sprite.setTexture(Hero_textures[now_move]);
	sprite.setPosition(x, y);
	sprite.setScale(0.01, 0.01);
	target.draw(sprite);
}
