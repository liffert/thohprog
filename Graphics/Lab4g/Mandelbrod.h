#pragma once
#include <cmath>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>

class Mandelbrod {
public:
	Mandelbrod() {};
	~Mandelbrod() {};

	void start(QGraphicsScene*& scene);
private:
	void Draw(QGraphicsScene*& scene, int width, int height);

};

