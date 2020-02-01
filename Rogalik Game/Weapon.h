#pragma once
#include "SFML/Graphics.hpp"

class Weapon : public sf::Drawable{
public:
	Weapon(int x1, int y1);
	~Weapon();

	void set_kick(bool state);
	void move(int x, int y);
	void rotate();
	bool kicked(int x1, int x2, int y1, int y2);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Initialization();
	int x1;
	int y1;
	int x2;
	int y2;

	bool kick = false;
};

