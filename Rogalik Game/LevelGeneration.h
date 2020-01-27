#pragma once
#include "SFML/Graphics.hpp"

class LevelGeneration : public sf::Drawable {
public:
	LevelGeneration(int width, int height);
	~LevelGeneration();

	void print();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	int **Rect;
	int rows;
	int columns;


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
};
