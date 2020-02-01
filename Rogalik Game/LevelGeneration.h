#pragma once
#include "SFML/Graphics.hpp"

class LevelGeneration : public sf::Drawable {
public:
	LevelGeneration(int width, int height);
	~LevelGeneration();

	void print();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:

	char** Rect;
	int rows;
	int columns;

	//alive
	int step = 22;
	void doSimualtionStep();
	int birthLimit = 4;
	int deathLimit = 3;
	int countAliveNeighbours(int x, int y);
	//

	//BSP
	class leaf {

	public:
		leaf(int x, int y, int width, int height);
		~leaf();
		int x;
		int y;
		int width;
		int height;

	};

	typedef struct element {
		LevelGeneration::leaf* el;
		struct element* L;
		struct element* R;
	}element_t;

	element_t* head;
	
	void split(element_t *&pointer);

	//


	typedef struct point {
		double x;
		double y;
	}Point;

	class Room {
	public:
		int x1;
		int x2;
		int y1;
		int y2;

		Point center;

		Room(int x, int y, int width, int height);
		bool intersects(const Room& obj);
	private:


	};

	std::vector<Room> rooms;
	int maxRooms = 40;
	int maxRoomSize = 14;
	int minRoomSize = 4;
	void placeRooms();
	void hcoridor(int x1, int x2, int y);
	void ycoridor(int y1, int y2, int x);
	int pixelSize = 30;
	
};
