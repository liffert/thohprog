#pragma once
#include <cmath>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>

class Paporot {
public:
	Paporot() {};
	~Paporot() {};

	void start(QGraphicsScene*& scene);
private:
	void Draw(QGraphicsScene*& scene, int width, int height);

};

