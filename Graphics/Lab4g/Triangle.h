#pragma once
#include <cmath>
#include <QGraphicsScene>
#include <QPoint>

class Triangle {

public:

	Triangle() {};
	~Triangle() {};
	void start(QGraphicsScene* scene);
	int get_n() { return n; }
	void set_n(int N) { n = N; };

private:
	void Draw(QGraphicsScene*& scene, QPoint top, QPoint left, QPoint right, int n);
	int n = 0;
};

