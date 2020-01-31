#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "LevelGeneration.h"
int main() {

	sf::View view;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rogalik");
	window.setFramerateLimit(60);

	LevelGeneration gen(96, 54);
	//gen.print();

	sf::Event event;
	view.reset(sf::FloatRect(0, 0, 1280, 720));
	
	Game newGame;
	
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					newGame.Move_hero(Game::MOVE::UP);
					break;
				case sf::Keyboard::Down:
					newGame.Move_hero(Game::MOVE::DOWN);
					break;
				case sf::Keyboard::Right:
					newGame.Move_hero(Game::MOVE::RIGHT);
					break;
				case sf::Keyboard::Left:
					newGame.Move_hero(Game::MOVE::LEFT);
					break;
				}
			}
		}
		/*view.setCenter(100 + newGame.get_hero_X(), newGame.get_hero_Y());
		window.setView(view);*/
		window.clear();
		window.draw(gen);
		window.draw(newGame);
		window.display();
	}
}