#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include <array>
class Character : public sf::Drawable {

public:
	Character(std::string name, int x, int y, char **MAP, int n, int m);
	~Character();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void move(int move);

	int getY() const;
	int getX() const;
protected:

	void init();
	bool ability_to_move(int x, int  y);
	bool enemy;
	std::string name;

	enum hero_path {
		left,
		right,
		front,
		back
	};
	int now_move = hero_path::right;
	std::array<sf::Texture, 4> Hero_textures;
	std::string Hero_path[4];
	int x;
	int y;

	int step = 5;
	const int size = 15;

	int n;
	int m;
	char** MAP;

};




class Hero : public Character {
public:

	Hero(std::string name, int x, int y, char** MAP, int n, int m);
	~Hero();

private:

};


class Enemy : public Character {
public:
	Enemy(std::string name, int x, int y, char** MAP, int n, int m);
	~Enemy();
	void draw(sf::RenderTarget& target);
private:

};