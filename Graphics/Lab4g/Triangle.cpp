#include "Triangle.h"

QPoint midpoint(QPoint p1, QPoint p2) {
	return QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
}

void Triangle::start(QGraphicsScene* scene) {
	Draw(scene, QPoint(500, 10), QPoint(390, 200), QPoint(610, 200), n);
}

void Triangle::Draw(QGraphicsScene *&scene, QPoint top, QPoint left, QPoint right, int n) {
	if (n == 0) {
		QPolygon pol;
		pol.push_back(top);
		pol.push_back(left);
		pol.push_back(right);
		QPen pen;
		pen.setColor(Qt::gray);
		QBrush brush;
		brush.setColor(Qt::gray);
		brush.setStyle(Qt::SolidPattern);
		scene->addPolygon(pol, pen, brush);
	}
	else {
		QPoint p12 = midpoint(top, left);
		QPoint p23 = midpoint(left, right);
		QPoint p31 = midpoint(right, top);

		Draw(scene, top, p12, p31, n - 1);
		Draw(scene, p12, left, p23, n - 1);
		Draw(scene, p31, p23, right, n - 1);

	}
}
