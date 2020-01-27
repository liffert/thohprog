#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class Character : public sf::Drawable {

public:
	Character(std::string name, bool enemy);
	~Character();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void move(int move);
private:
	bool enemy;
	std::string name;
	std::string path = "Characters/Hero.png";
	sf::Texture texture;

	int x = 10;
	int y = 10;



	int step = 5;
};