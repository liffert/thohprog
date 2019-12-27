#include "Rect.h"
void add_line(QGraphicsScene*& scene, int& x, int& y, int deltaX, int deltaY) {
	scene->addLine(x, y, x + deltaX, y + deltaY);
	x = x + deltaX;
	y = y + deltaY;
}
void Rect::start(QGraphicsScene* &scene) {

	rect(n, scene, 0, 0, 400);
	/*dist = dist0;
	for(int i = n; i > 1; i--) {
		dist = dist / 2;
	}
	x = 2 * dist;
	y = dist;
	sierpA(n, scene);
	add_line(scene, x, y, dist, dist);
	sierpB(n, scene);
	add_line(scene, x, y, -dist, dist);
	sierpC(n, scene);
	add_line(scene, x, y, -dist, -dist);
	sierpD(n, scene);
	add_line(scene, x, y, dist, -dist);*/
}

void Rect::rect(int n, QGraphicsScene*& scene, int x, int y, int size) {
	QPen pen;
	QBrush brush;

	pen.setColor(Qt::gray);
	brush.setStyle(Qt::SolidPattern);
	if (n == 0) {
		scene->addRect(x, y, size, size, pen, brush);
		return;
	}


	double sizet = size / 3;
	double x1 = x;
	double x2 = x1 + sizet;
	double x3 = x1 + 2 * sizet;
	double y1 = y;
	double y2 = y1 + sizet;
	double y3 = y1 + 2 * sizet;

	rect(n - 1, scene, x1, y1, sizet);
	rect(n - 1, scene, x2, y1, sizet);
	rect(n - 1, scene, x3, y1, sizet);
	rect(n - 1, scene, x1, y2, sizet);
	rect(n - 1, scene, x3, y2, sizet);
	rect(n - 1, scene, x1, y3, sizet);
	rect(n - 1, scene, x2, y3, sizet);
	rect(n - 1, scene, x3, y3, sizet);

}

void Rect::sierpA(int n, QGraphicsScene*& scene) {
	if (n > 0) {
		sierpA(n - 1, scene);
		add_line(scene, x, y, dist, dist);
		sierpB(n - 1, scene);
		add_line(scene, x, y, 2 * dist, 0);
		sierpD(n - 1, scene);
		add_line(scene, x, y, dist, -dist);
		sierpA(n - 1, scene);
	}
}
void Rect::sierpB(int n, QGraphicsScene*& scene) {
	if (n > 0) {
		sierpB(n - 1, scene);
		add_line(scene, x, y, -dist, dist);
		sierpC(n - 1, scene);
		add_line(scene, x, y, 0, 2 * dist);
		sierpA(n - 1, scene);
		add_line(scene, x, y, dist, dist);
		sierpB(n - 1, scene);
	}
}
void Rect::sierpC(int n, QGraphicsScene*& scene) {
	if (n > 0) {
		sierpC(n - 1, scene);
		add_line(scene, x, y, -dist, -dist);
		sierpD(n - 1, scene);
		add_line(scene, x, y, -2 * dist, 0);
		sierpB(n - 1, scene);
		add_line(scene, x, y, -dist, +dist);
		sierpC(n - 1, scene);
	}
}
void Rect::sierpD(int n, QGraphicsScene*& scene) {
	if (n > 0) {
		sierpD(n - 1, scene);
		add_line(scene, x, y, dist, -dist);
		sierpA(n - 1, scene);
		add_line(scene, x, y, 0, -2 * dist);
		sierpC(n - 1, scene);
		add_line(scene, x, y, -dist, -dist);
		sierpD(n - 1, scene);
	}
}
