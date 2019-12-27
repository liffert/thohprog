#include "SFML\Graphics.hpp"
#include <ctime>
#include <stdlib.h>
#include <sstream>

const int HEIGHT_MAP = 10;
const int WIDTH_MAP = 10;


sf::String map[HEIGHT_MAP] = 
{
	"0000000000",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0000000000",
};

sf::String stockmap[HEIGHT_MAP] = 
{
	"0000000000",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0        0",
	"0000000000",
};

void returnStockMap() 
{
	for (int i = 0; i < HEIGHT_MAP; i++) 
	{
		for (int j = 0; j < WIDTH_MAP; j++) 
		{
			map[i][j] = stockmap[i][j];
		}
	}
}
void randMap() 
{
	srand(time(NULL));
	for (int p = 0; p < 8; p++) 
	{
		pos:
		int j = rand() % WIDTH_MAP;
		int i = rand() % HEIGHT_MAP;
		if (i == 0) 
		{
			i++;
		}
		else if (i == HEIGHT_MAP - 1) 
		{
			i--;
		}
		if (j == 0) 
		{
			j++;
		}
		if (j == WIDTH_MAP - 1) 
		{
			j--;
		}
		if (map[i][j] == 'l') 
		{
			goto pos;
		}
		map[i][j] = 'l';
	}
}
void go() 
{
	int couter = 0;
	int lis = 0;
	int vert = 0;
	int gorizont = 0;
	int diag = 0;
	int diag2 = 0;
	bool keyboardControl = 0;
	sf::RectangleShape hero(sf::Vector2f(20, 20));
	hero.setFillColor(sf::Color::Red);
	float herox = 43;
	float heroy = 43;
	hero.setPosition(herox, heroy);
	sf::Texture maptexture;
	sf::Sprite Map;
	maptexture.loadFromFile("map.png");
	Map.setTexture(maptexture);
	sf::Font font;
	font.loadFromFile("FONT.otf");
	sf::RenderWindow window(sf::VideoMode(600, 500), "Saper", sf::Style::Close);
	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::KeyPressed) 
			{
				if (event.key.code == sf::Keyboard::Escape) 
				{
					window.close();
				}
			}
			else if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
			if (keyboardControl == 1) 
			{
				if (event.type == sf::Event::KeyPressed) 
				{
					switch (event.key.code) 
					{
					case sf::Keyboard::Left: 
						if (herox > 43) 
						{
							herox = herox - 35;
						}
						break;
					case sf::Keyboard::Right: 
						if (herox < 43 + (35 * 7)) 
						{
							herox = herox + 35;
						}
						break;
					case sf::Keyboard::Down: 
						if (heroy < 43 + (35 * 7)) 
						{
							heroy = heroy + 35;
						}
						break;
					case sf::Keyboard::Up: 
						if (heroy > 43) 
						{
							heroy = heroy - 35;
						}
						break;
					}
					hero.setPosition(herox, heroy);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) 
					{
						if (keyboardControl == 0) 
						{
							keyboardControl = 1;
						}
						else 
						{
							keyboardControl = 0;
						}
					}
					break;
				}
			}
		}
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++) 
		{
			for (int j = 0; j < WIDTH_MAP; j++) 
			{
				if (map[i][j] == '0') 
				{
					Map.setTextureRect(sf::IntRect(0, 0, 35, 35));
				}
				if (map[i][j] == 'l') 
				{
					Map.setTextureRect(sf::IntRect(35, 0, 35, 35));
				}
				if (map[i][j] == ' ') 
				{
					Map.setTextureRect(sf::IntRect(35, 0, 35, 35));
				}
				if (map[i][j] == 'w') 
				{
					Map.setTextureRect(sf::IntRect(70, 0, 35, 35));
				}
				Map.setPosition(j * 35, i * 35);
				window.draw(Map);
			}
		}
		if (keyboardControl == 0) 
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				keyboardControl = 1;
			}
		}
		if (keyboardControl == 1) 
		{
			window.draw(hero);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
			{
				gorizont = 0;
				vert = 0;
				diag = 0;
				diag2 = 0;
				int i = (int)(heroy / 35);
				int j = (int)(herox / 35);
				if (map[i][j] == ' ') 
				{
					map[i][j] = '0';
					couter++;
				}
				if (map[i][j] == 'l') 
				{
					map[i][j] = 'w';
					lis++;
					couter++;
				}
				for (int k = 0; k < WIDTH_MAP; k++) 
				{
					if (map[i][k] == 'l') 
					{
						gorizont++;
					}
				}
				for (int k = 0; k < HEIGHT_MAP; k++) 
				{
					if (map[k][j] == 'l') 
					{
						vert++;
					}
				}
				int p = i;
				int t = j;
				while (t < WIDTH_MAP - 1 && p > 0) 
				{
					t++;
					p--;
				}
				while (t > 0 && p < HEIGHT_MAP) 
				{
					if (map[p][t] == 'l') 
					{
						diag++;
					}
					p++;
					t--;
				}
				p = i;
				t = j;
				while (t > 0 && p > 0) 
				{
					t--;
					p--;
				}
				while (t < WIDTH_MAP && p < HEIGHT_MAP) 
				{
					if (map[p][t] == 'l') 
					{
						diag2++;
					}
					t++;
					p++;
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			sf::Vector2f pixelpos = window.mapPixelToCoords(pos);
			int i = (int)(pixelpos.y / 35);
			int j = (int)(pixelpos.x / 35);
			if (i > HEIGHT_MAP - 2 || j > WIDTH_MAP - 2 || i < 1 || j < 1) {}
			else 
			{
				gorizont = 0;
				vert = 0;
				diag = 0;
				diag2 = 0;
				if (map[i][j] == ' ') 
				{
					map[i][j] = '0';
					couter++;
				}
				if (map[i][j] == 'l') 
				{
					map[i][j] = 'w';
					lis++;
					couter++;
				}
				for (int k = 0; k < WIDTH_MAP; k++) 
				{
					if (map[i][k] == 'l') 
					{
						gorizont++;
					}
				}
				for (int k = 0; k < HEIGHT_MAP; k++) 
				{
					if (map[k][j] == 'l') 
					{
						vert++;
					}
				}
				int p = i;
				int t = j;
				while (t < WIDTH_MAP - 1 && p > 0) 
				{
					t++;
					p--;
				}
				while (t > 0 && p < HEIGHT_MAP) 
				{
					if (map[p][t] == 'l') 
					{
						diag++;
					}
					p++;
					t--;
				}
				p = i;
				t = j;
				while (t > 0 && p > 0) 
				{
					t--;
					p--;
				}
				while (t < WIDTH_MAP && p < HEIGHT_MAP) 
				{
					if (map[p][t] == 'l') 
					{
						diag2++;
					}
					t++;
					p++;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
		{
			returnStockMap();
			randMap();
			keyboardControl = 0;
			couter = 0;
			diag = 0;
			diag2 = 0;
			gorizont = 0;
			lis = 0;
			vert = 0;
		}
		std::ostringstream goriz;
		std::ostringstream vertical;
		std::ostringstream diagonal;
		std::ostringstream diagonal2;
		std::ostringstream CounterStr;
		goriz << gorizont;
		vertical << vert;
		diagonal << diag;
		diagonal2 << diag2;
		CounterStr << couter;
		sf::Text gor("", font, 15);
		gor.setString("Gorizont: " + goriz.str());
		sf::Text v("", font, 15);
		v.setString("Vertical: " + vertical.str());
		sf::Text d("", font, 15);
		d.setString("Diagonal Pobichna: " + diagonal.str());
		sf::Text d2("", font, 15);
		d2.setString("Diagonal Golovna: " + diagonal2.str());
		sf::Text c("", font, 15);
		c.setString("Moves: " + CounterStr.str());
		gor.setPosition(35 * 12, 25);
		v.setPosition(35 * 12, 50);
		d.setPosition(35 * 12, 75);
		d2.setPosition(35 * 12, 100);
		c.setPosition(35 * 12, 135);
		window.draw(gor);
		window.draw(v);
		window.draw(d);
		window.draw(d2);
		window.draw(c);
		if (lis == 8) 
		{
			sf::Text win("Done. \nPress R  for restart. \nClose window \nor press Escape for \nexit", font, 17);
			win.setPosition(35 * 11, 170);
			window.draw(win);
		}
		window.display();
	}
}
int main() 
{
	randMap();
	go();
}