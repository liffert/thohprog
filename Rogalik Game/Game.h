#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include <vector>
#include "Weapon.h"

class Game : public sf::Drawable{

public:
	Game();
	~Game();
	void Inintialization();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Move_hero(int move);
	void kick_hero(bool state);
	int get_hero_X() const;
	int get_hero_Y() const;

	void check_kick();

	static enum MOVE {
		UP = 1201,
		DOWN,
		LEFT,
		RIGHT
	};

private:
	std::vector<std::pair<Character, Weapon>> characters;
};

