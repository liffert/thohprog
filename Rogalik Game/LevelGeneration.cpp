#include "LevelGeneration.h"
#include <iostream>
#include <ctime>

LevelGeneration::LevelGeneration(int width, int height) : rows(height), columns(width) {
	/*std::srand(time(NULL));
	Rect = new int *[height]();
	for (int i = 0; i < height; i++) {
		Rect[i] = new int[width]();
	}
	head = new element_t;
	head->el = new leaf(0, 0, width, height);
	element_t* pointer = head;
	split(pointer);
	for (int i = 0; i < 3; i++) {
		pointer = pointer->L;
		split(pointer);
	}
	pointer = head;
	for (int i = 0; i < 3; i++) {
		pointer = pointer->R;
		split(pointer);
	}*/

	/*std::srand(time(NULL));

	Rect = new bool* [height]();
	for (int i = 0; i < height; i++) {
		Rect[i] = new bool[width]();
	}

	double startAlive = 40;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (std::rand() % 101 < startAlive) {
				Rect[i][j] = true;
			}
		}
	}

	for (int i = 0; i < step; i++) {
		doSimualtionStep();
	}
	*/
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
	for (int i = 0; i < head->el->height; i++) {
		for (int j = 0; j < head->el->width; j++) {
			std::cout << Rect[i][j] << " ";
		}
		std::cout << std::endl;
	}
	bool a = false;
}

void LevelGeneration::split(element_t *&pointer) {
	int split_point;
	if ((std::rand() % 100) % 2 != 0) {
		split_point = pointer->el->width / 2;

		pointer->L = new element_t;
		pointer->R = new element_t;

		pointer->L->el = new leaf(pointer->el->x, pointer->el->y, split_point, pointer->el->height);
		pointer->R->el = new leaf(split_point, pointer->el->y, pointer->el->width - split_point, pointer->el->height);
	}
	else {
		split_point = pointer->el->height / 2 + std::rand() % pointer->el->height / 4;

		pointer->L = new element_t;
		pointer->R = new element_t;

		pointer->L->el = new leaf(pointer->el->x, pointer->el->y, pointer->el->width, split_point);
		pointer->R->el = new leaf(pointer->el->x, split_point, pointer->el->width, pointer->el->height - split_point);
	}

	if (!pointer->L->el || !pointer->R->el) { return; }
	for (int i = pointer->L->el->x; i < pointer->L->el->width; i++) {
		Rect[pointer->L->el->y][i] = true;
		Rect[pointer->L->el->y + pointer->L->el->height - 1][i] = true;
	}
	for (int i = pointer->L->el->y; i < pointer->L->el->height; i++) {
		Rect[i][pointer->L->el->x] = true;
		Rect[i][pointer->L->el->x + pointer->L->el->width - 1] = true;
	}
	for (int i = pointer->R->el->x; i < pointer->R->el->x + pointer->R->el->width; i++) {
		Rect[pointer->R->el->y][i] = true;
		Rect[pointer->R->el->y + pointer->R->el->height - 1][i] = true;
	}
	for (int i = pointer->R->el->y; i < pointer->R->el->y + pointer->R->el->height; i++) {
		Rect[i][pointer->R->el->x] = true;
		Rect[i][pointer->R->el->x + pointer->R->el->width - 1] = true;
	}
}

LevelGeneration::leaf::leaf(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
}

LevelGeneration::leaf::~leaf() {
}


void LevelGeneration::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//sf::CircleShape temp(10);
	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(20, 20));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			temp.setPosition(j * 20, i * 20);
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

/*int LevelGeneration::countAliveNeighbours(int x, int y) {
	int count = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int neighbour_x = x + i;
			int neighbour_y = y + j;
			if (i == 0 && j == 0) {}
			else if (neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= columns || neighbour_y >= rows) {
				count++;
			}
			else if (Rect[neighbour_y][neighbour_x]) {
				count++;
			}
		}
	}

	return count;
}
void LevelGeneration::doSimualtionStep() {
	bool** newRect;
	newRect = new bool* [rows]();
	for (int i = 0; i < rows; i++) {
		newRect[i] = new bool[columns]();
	}

	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			int nbs = countAliveNeighbours(i, j);
			if (Rect[j][i]) {
				if (nbs < deathLimit) {
					newRect[j][i] = false;
				}
				else {
					newRect[j][i] = true;
				}
			}
			else {
				if (nbs > birthLimit) {
					newRect[j][i] = true;
				}
				else {
					newRect[j][i] = false;
				}
			}
		}
	}
	Rect = std::move(newRect);
}
*/
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

		/*if ((x + w) >= columns) {
			int buf = x;
			x = w;
			w = x;
		}
		if ((y + h) >= rows) {
			int buf = y;
			y = h;
			h = buf;
		}*/
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
