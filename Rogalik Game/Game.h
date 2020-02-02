#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include <vector>
#include "Weapon.h"
#include "LevelGeneration.h"
const int pixelSize = 30;

class Game {

public:
	Game(int n, int m);
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
	std::vector<std::pair<Character, Weapon>> characters;

	LevelGeneration* lvl;
};

