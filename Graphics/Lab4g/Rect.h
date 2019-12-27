#pragma once
#include <cmath>
#include <QGraphicsScene>
#include <QPoint>

class Rect {

public:
	Rect() {};
	~Rect() {};
	int get_n() { return n; }
	void set_n(int N) { n = N; x = 0; y = 0;}
	void start(QGraphicsScene* &scene);
	int dist = 0;

private:
	int x = 0;
	int y = 0;

	void rect(int n, QGraphicsScene*& scene, int x, int y, int size);
	int n = 0;
	int dist0 = 50;
	void sierpA(int n, QGraphicsScene*& scene);
	void sierpB(int n, QGraphicsScene*& scene);
	void sierpC(int n, QGraphicsScene*& scene);
	void sierpD(int n, QGraphicsScene*& scene);

};

