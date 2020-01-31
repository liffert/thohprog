#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include <vector>

class Game : public sf::Drawable{

public:
	Game();
	~Game();
	void Inintialization();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Move_hero(int move);
	int get_hero_X() const;
	int get_hero_Y() const;

	static enum MOVE {
		UP = 1201,
		DOWN,
		LEFT,
		RIGHT
	};

private:
	std::vector<Character> characters;
};

