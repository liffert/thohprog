#include "Mandelbrod.h"
#include <QRgb>

void Mandelbrod::start(QGraphicsScene*& scene) {
	Draw(scene, 700, 700);
}

void Mandelbrod::Draw(QGraphicsScene*& scene, int width, int height) {
	const int max = 1000;
	QImage image(width, height, QImage::Format::Format_RGB32);
	image.fill(Qt::white);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			const double c_re = (col - width / 2) * 4.0 / width;
			const double c_im = (row - height / 2) * 4.0 / width;
			double x = 0.0;
			double y = 0.0;
			int i = 0;
			while (x * x + y * y < 4 && i < max) {
				double x_new = x * x - y * y + c_re;
				y = 2.0 * x * y + c_im;
				x = x_new;
				i++;
			}
			if (i < max) {
				double r = 0.1 + i * 0.03 * 0.2;
				double g = 0.2 + i * 0.03 * 0.3;
				double b = 0.3 + i * 0.03 * 0.1;
				if (i % 2 == 0) {
					image.setPixel(col, row, QColor().fromHslF(r, g, b).rgb());
				}
				else {
					image.setPixel(col, row, QColor().fromRgbF(r, g, b).rgb());
				}

				//image.setPixel(col, row, QColor(i | (i << 20)).rgb());
			}
			else {
				image.setPixel(col, row, QColor(Qt::black).rgb());
			}
		}
	}

	QPixmap map;
	image.save("Pix2.png");
	map = QPixmap::fromImage(image);
	scene->addPixmap(map);
}
