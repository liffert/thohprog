#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include <vector>
#include "Weapon.h"
#include "LevelGeneration.h"

class Game {

public:
	Game(LevelGeneration &lvl, int n, int m, int pixelSize);
	~Game();
	void Inintialization(int x, int y);
	void Move_hero(int move);
	void kick_hero(bool state);
	int get_hero_X() const;
	int get_hero_Y() const;

	void check_kick();

	virtual void draw(sf::RenderTarget& target);
	static enum MOVE {
		UP = 1201,
		DOWN,
		LEFT,
		RIGHT
	};
private:
	char** MAP;
	int n;
	int m;
	int pixelSize;
	std::vector<std::pair<Character, Weapon>> characters;
};

