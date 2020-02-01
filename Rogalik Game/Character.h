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
private:

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
	std::string Hero_path[4] = {"Characters/Left.png", "Characters/Right.png", "Characters/Front.png", "Characters/Front.png"};
	int x;
	int y;

	int step = 5;

	int n;
	int m;
	char** MAP;

};