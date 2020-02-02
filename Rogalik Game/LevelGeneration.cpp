#include "LevelGeneration.h"
#include <iostream>
#include <ctime>
#include "Game.h"

LevelGeneration::LevelGeneration(int width, int height) : rows(height), columns(width) {
	std::srand(time(NULL));
	Rect = new char* [height]();
	for (int i = 0; i < height; i++) {
		Rect[i] = new char[width]();
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Rect[i][j] = 'N';
		}
	}
	placeRooms();
}

LevelGeneration::~LevelGeneration() {
}

void LevelGeneration::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << Rect[i][j] << " ";
		}
		std::cout << std::endl;
	}
	bool a = false;
}



void LevelGeneration::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//sf::CircleShape temp(10);
	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(pixelSize, pixelSize));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			temp.setPosition(j * pixelSize, i * pixelSize);
			switch (Rect[i][j]) {
			case 'N':
				temp.setFillColor(sf::Color(128, 128, 128));
				break;
			case 'A':
				temp.setFillColor(sf::Color::Green);
				break;
			}
			target.draw(temp, states);
		}

	}
}

char** LevelGeneration::get() const {
	return Rect;
}

void LevelGeneration::get_start(int& x, int& y) {
	x = rooms.begin()->x1;
	y = rooms.begin()->y1;

	for (const auto& iter : rooms) {
		if (iter.x1 < x) {
			x = iter.x1;
			y = iter.y1;
		}
		else if (iter.x1 == x && iter.y1 < y) {
			x = iter.x1;
			y = iter.y1;
		}
	}

	x = x + minRoomSize / 2;
	y = y + minRoomSize / 2;
}

LevelGeneration::Room::Room(int x, int y, int width, int height) : x1(x), x2(x + width), y1(y), y2(y + height){
	center.x = std::floor((x1 + x2) / 2);
	center.y = std::floor((y1 + y2) / 2);
}

bool LevelGeneration::Room::intersects(const Room& obj) {
	return (x1 <= obj.x2 && x2 >= obj.x1 && y1 <= obj.y2 && y2 >= obj.y1);
}

void LevelGeneration::placeRooms() {
	for (int i = 0; i < maxRooms; i++) {
		int w = minRoomSize + std::rand() % (maxRoomSize - minRoomSize + 1);
		int h = minRoomSize + std::rand() % (maxRoomSize - minRoomSize + 1);
		int x = (std::rand() % (columns - w - 1)) + 1;
		int y = (std::rand() % (rows - h - 1)) + 1;

		Room temp(x, y, w, h);

		bool failed = false;
		for (auto iter : rooms) {
			if (iter.intersects(temp)) {
				failed = true;
				break;
			}
		}
		if (!failed) {

			Point newCenter = temp.center;
			for (int i = temp.x1; i <= temp.x2; i++) {
				for (int j = temp.y1; j <= temp.y2; j++) {
					Rect[j][i] = 'A';
				}
			}
			for (int i = temp.y1; i <= temp.y2; i++) {
				for (int j = temp.x1; j <= temp.x2; j++) {
					Rect[i][j] = 'A';
				}

			}

			if (rooms.size() != 0) {
				Point prevCenter = rooms.back().center;
				if (std::rand() % 2 == 1) {
					hcoridor(prevCenter.x, newCenter.x, prevCenter.y);
					ycoridor(prevCenter.y, newCenter.y, newCenter.x);
				}
				else {
					ycoridor(prevCenter.y, newCenter.y, prevCenter.x);
					hcoridor(prevCenter.x, newCenter.x, newCenter.y);
				}
			}

			rooms.push_back(temp);
		}
	}
}

void LevelGeneration::hcoridor(int x1, int x2, int y) {
	for (int x = std::min(x1, x2); x < std::max(x1, x2) + 1; x++) {
		Rect[y][x] = 'A';
	}
}

void LevelGeneration::ycoridor(int y1, int y2, int x) {
	for (int y = std::min(y1, y2); y < std::max(y1, y2) + 1; y++) {
		Rect[y][x] = 'A';
	}
}
