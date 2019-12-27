#include "Paporot.h"
#include <QDebug>
#include <QRgb>



const int n = 1000000;
const int w = 400, h = 400;
const int xc = 0, yc = 10;
const int l = 600;
const int m = 4;
const double s[] = { 0, 0.01, 0.86, 0.93 };
const double f[][3] = { {0.0, 0.0, 0.5},

					   {0.85, 0.04, 0.075},

					   {0.2, -0.26, 0.4},

					   {-0.15, 0.28, 0.575} };

const double g[][3] = { {0.0, 0.16, 0.0},

					   {-0.04, 0.85, 0.18},

					   {0.23, 0.22, 0.045},

					   {0.26, 0.24, -0.086} };


int get_random_value() {

	double r = (double)rand() / RAND_MAX;
	int c = 1;

	while (s[c] < r && ++c < m) {}

	return c - 1;

}

void Paporot::start(QGraphicsScene*& scene) {
	Draw(scene, 480, 640);
}

void Paporot::Draw(QGraphicsScene*& scene, int width, int height) {
	QPen pen;
	pen.setWidth(1);
	pen.setColor(Qt::green);

	QImage image(640, 640, QImage::Format::Format_RGB32);
	image.fill(Qt::white);
	double x = 0, y = 0;

	for (int i = 0; i < n; i++) {
		int r = get_random_value();

		double x1 = f[r][0] * x + f[r][1] * y + f[r][2];
		double y1 = g[r][0] * x + g[r][1] * y + g[r][2];
		x = x1;
		y = y1;
		image.setPixel(round(x * l) + xc, round(y * l) + yc, QColor(Qt::yellow).rgba());
	}
	image.save("pix.png");
	QPixmap map;
	map = QPixmap::fromImage(image);
	scene->addPixmap(map);

}