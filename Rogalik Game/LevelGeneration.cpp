#include "LevelGeneration.h"
#include <iostream>
#include <ctime>

LevelGeneration::LevelGeneration(int width, int height) : rows(height), columns(width) {
	std::srand(time(NULL));
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
	}

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

	for (int i = pointer->L->el->x; i < pointer->L->el->width; i++) {
		Rect[pointer->L->el->y][i] = 1;
		Rect[pointer->L->el->y + pointer->L->el->height - 1][i] = 1;
	}
	for (int i = pointer->L->el->y; i < pointer->L->el->height; i++) {
		Rect[i][pointer->L->el->x] = 1;
		Rect[i][pointer->L->el->x + pointer->L->el->width - 1] = 1;
	}
	for (int i = pointer->R->el->x; i < pointer->R->el->x + pointer->R->el->width; i++) {
		Rect[pointer->R->el->y][i] = 1;
		Rect[pointer->R->el->y + pointer->R->el->height - 1][i] = 1;
	}
	for (int i = pointer->R->el->y; i < pointer->R->el->y + pointer->R->el->height; i++) {
		Rect[i][pointer->R->el->x] = 1;
		Rect[i][pointer->R->el->x + pointer->R->el->width - 1] = 1;
	}
}

LevelGeneration::leaf::leaf(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
}

LevelGeneration::leaf::~leaf() {
}


void LevelGeneration::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::CircleShape temp(10);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			temp.setPosition(j*10, i*10);
			if (Rect[i][j] == 1) {
				temp.setFillColor(sf::Color::White);
				target.draw(temp, states);
			}
		}
	}
}