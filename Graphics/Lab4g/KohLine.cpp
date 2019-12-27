#include "KohLine.h"

void KohLine::start(QGraphicsScene*& scene) {
	Draw(scene, 300, 300, 700, 300, n);
}

void KohLine::Draw(QGraphicsScene*& scene, double x, double y, double x2, double y2, int n) {
	QPen pen;
	pen.setWidth(1);
	pen.setColor(Qt::black);


	double angle = 3.14 / 3.0;

	double x3 = (x * 2.0 + x2) / 3.0;
	double y3 = (y * 2.0 + y2) / 3.0;
	double x4 = (x + x2 * 2.0) / 3.0;
	double y4 = (y + 2.0 * y2) / 3.0;
	double x5 = x3 + (x4 - x3) * cos(angle) + (y4 - y3) * sin(angle);
	double y5 = y3 - (x4 - x3) * sin(angle) + (y4 - y3) * cos(angle);

	if (n > 0) {

		Draw(scene, x, y, x3, y3, n - 1);
		Draw(scene, x3, y3, x5, y5, n - 1);
		Draw(scene, x5, y5, x4, y4, n - 1);
		Draw(scene, x4, y4, x2, y2, n - 1);
	}
	else {
		scene->addLine(x, y, x3, y3, pen);
		scene->addLine(x3, y3, x5, y5, pen);
		scene->addLine(x5, y5, x4, y4, pen);
		scene->addLine(x4, y4, x2, y2, pen);
	}

}
