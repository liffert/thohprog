#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "LevelGeneration.h"
int main() {

	sf::View view;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rogalik");
	window.setFramerateLimit(60);


	sf::Event event;

	view.setSize(sf::Vector2f(400, 400));

	Game newGame(1920 / pixelSize, 1080 / pixelSize);
	
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up) {
					newGame.Move_hero(Game::MOVE::UP);
				}
				if (event.key.code == sf::Keyboard::Down) {
					newGame.Move_hero(Game::MOVE::DOWN);
				}
				if (event.key.code == sf::Keyboard::Right) {
					newGame.Move_hero(Game::MOVE::RIGHT);
				}
				if (event.key.code == sf::Keyboard::Left) {
					newGame.Move_hero(Game::MOVE::LEFT);
				}
				if(event.key.code == sf::Keyboard::Enter){
					newGame.kick_hero(true);
					newGame.check_kick();
				}
				break;
			}
		}
		view.setCenter(100 + newGame.get_hero_X(), newGame.get_hero_Y());
		window.setView(view);
		window.clear();
		sf::CircleShape temp(10);
		temp.setPosition(70, 80);
		window.draw(temp);
		temp.setRadius(1);
		temp.setFillColor(sf::Color::Red);
		window.draw(temp);
		newGame.draw(window);
		window.display();
	}
}