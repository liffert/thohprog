#include "Weapon.h"

Weapon::~Weapon() {
}

Weapon::Weapon(int x1, int y1) : x1(x1 + 5), y1(y1 + 7) {
	Initialization();
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::VertexArray weap(sf::Lines, 2);

	for (int i = 0; i < 9; i++) {
		weap[0].color = sf::Color::Blue;
		weap[0].position = sf::Vector2f(x1, y1 + i);
		weap[1].color = sf::Color::Blue;
		if (kick) {
			weap[1].position = sf::Vector2f(x2, y1 + i);
		}
		else {
			weap[1].position = sf::Vector2f(x2, y2 + i);
		}
		target.draw(weap, states);
	}
}

void Weapon::set_kick(bool state) {
	kick = state;
}

void Weapon::move(int x, int y) {
	this->x1 = x + 5;
	this->y1 = y + 7;
	Initialization();
}

void Weapon::rotate() {
}

bool Weapon::kicked(int x1, int x2, int y1, int y2) {
	if (this->x2 >= x1 && this->x1 <= x1) {
		if (this->y1 >= y1 && this->y1 <= y2 || this->y2 >= y1 && this->y2 <= y2) {
			return true;
		}
	}
	return false;
}



void Weapon::Initialization() {
	x2 = x1 + 20;
	y2 = y1 - 20;
}
