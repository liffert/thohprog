#include "Lab3g.h"

Lab3g::Lab3g(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	setUPpolyhedron();
	scene = new QGraphicsScene(this);
	view = new QGraphicsView(scene);
	scene->addWidget(this);
	view->show();
	pen.setColor(Qt::black);
	connect(ui.createF, SIGNAL(clicked()), this, SLOT(createFig()));
	connect(ui.createP, SIGNAL(clicked()), this, SLOT(createPoly()));
	connect(ui.Start, SIGNAL(clicked()), this, SLOT(start()));
}

void Lab3g::createPoly() {
	po = true;
	fig = false;
	QLine line;
	for (int i = 0; i < polyhedron.size() - 1; i++) {
		line = QLine(polyhedron[i], polyhedron[i + 1]);
		scene->addLine(line, pen);
	}
	line = QLine(polyhedron[polyhedron.size() - 1], polyhedron[0]);
	scene->addLine(line, pen);
	if (count >= 0) {
		count--;
		setUPpolyhedron(step);
		step = step + 20;
		createPoly();
	}
}

void Lab3g::start() {
	if (po) {
		time = new QTime();
		setUPpolyhedron();
		time->start();
		ALG1(QPoint(polyhedron[0].x() + 2, polyhedron[0].y() + 2), Qt::green, Qt::black);
		pen.setColor(Qt::black);
		times[0] = QString::number(time->elapsed());
		setUPpolyhedron(20);
		time->restart();
		ALG2(QPoint(polyhedron[0].x() + 2, polyhedron[0].y() + 2), Qt::green, Qt::black);
		pen.setColor(Qt::black);
		times[1] = QString::number(time->elapsed());
		setUPpolyhedron(40);
		time->restart();
		ALG3(polyhedron, Qt::green, Qt::black);
		times[2] = QString::number(time->elapsed());
		pen.setColor(Qt::black);
		setUPpolyhedron(60);
		time->restart();
		ALG4(polyhedron, Qt::green, Qt::black);
		times[3] = QString::number(time->elapsed());
		pen.setColor(Qt::black);
		delete time;
		showtimes();
	}
	else if (fig) {
		ALG2(QPoint(points[0].x() + 10, points[0].y()), Qt::green, Qt::black);
		pen.setColor(Qt::black);
	}
}

void Lab3g::setUPpolyhedron(int left) {
	polyhedron = { QPoint(50 + left, 50), QPoint(60 + left, 50), QPoint(60 + left, 60), QPoint(50 + left, 60)};
}

void Lab3g::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::MouseButton::LeftButton) {
		QPoint pos = QCursor::pos();
		points.push_back(mapFromGlobal(pos));
		QLine line(points[points.size() - 1], points[points.size() - 1]);
		scene->addLine(line, pen);
	}
}


void Lab3g::ALG1(QPoint point, QColor New, QColor Old) {
	QPixmap map(scene->sceneRect().width(), scene->sceneRect().height());
	QImage img;
	QPainter painter(&map);
	scene->render(&painter);
	painter.end();
	
	img = map.toImage();
	img.save("pix.png");

	QColor s = img.pixel(point);
	if (s != New && s!= Old) {
		QLine line(point, point);
		pen.setColor(New);
		scene->addLine(line, pen);
		qDebug() << "x: " << point.x() << " y: " << point.y();
	}
	else {
		return;
	}
	ALG1(QPoint(point.x() + 1, point.y()), New, Old);
	ALG1(QPoint(point.x(), point.y() + 1), New, Old);
	ALG1(QPoint(point.x(), point.y() - 1), New, Old);
	ALG1(QPoint(point.x() - 1, point.y()), New, Old);
}

void Lab3g::ALG2(QPoint point, QColor New, QColor Old) {
	int xr = point.x();
	int xl = point.x();

	QPixmap map(scene->sceneRect().width(), scene->sceneRect().height());
	QImage img;
	QPainter painter(&map);
	scene->render(&painter);
	painter.end();

	img = map.toImage();
	img.save("pix.png");

	QColor s = img.pixel(xr + 1, point.y());
	while (s != Old && s != New) {
		xr++;
		s = img.pixel(xr + 1, point.y());
	}
	s = img.pixel(xl - 1, point.y());
	while (s != Old && s != New) {
		xl--;
		s = img.pixel(xl - 1, point.y());
	}
	pen.setColor(New);
	qDebug() << "x1: " << xr << " y: " << point.y() << " x2: " << xl;
	scene->addLine(xr, point.y(), xl, point.y(), pen);
	painter.begin(&map);
	scene->render(&painter);
	painter.end();

	img = map.toImage();
	img.save("pix.png");
	for (int i = xl; i <= xr; i++) {
		s = img.pixel(i, point.y() + 1);
		if (s != Old && s != New) {
			ALG2(QPoint(i, point.y() + 1), New, Old);
			painter.begin(&map);
			scene->render(&painter);
			painter.end();

			img = map.toImage();
			img.save("pix.png");
		}
	}
	painter.begin(&map);
	scene->render(&painter);
	painter.end();

	img = map.toImage();
	img.save("pix.png");
	for (int i = xl; i <= xr; i++) {
		s = img.pixel(i, point.y() - 1);
		if (s != Old && s != New) {
			ALG2(QPoint(i, point.y() - 1), New, Old);
			painter.begin(&map);
			scene->render(&painter);
			painter.end();

			img = map.toImage();
			img.save("pix.png");
		}
	}
}

void Lab3g::ALG3(std::vector<QPoint> points, QColor New, QColor Old) {
	struct search {
		int min(const std::vector<QPoint> &points) {
			int min = points[0].y();
			for (auto iter = points.begin(); iter != points.end(); iter++) {
				if (min > (*iter).y()) {
					min = (*iter).y();
				}
			}
			return min;
		}
		int max(const std::vector<QPoint>& points) {
			int max = points[0].y();
			for (auto iter = points.begin(); iter != points.end(); iter++) {
				if (max < (*iter).y()) {
					max = (*iter).y();
				}
			}
			return max;
		}
	}; struct search temp;


	QPixmap map(scene->sceneRect().width(), scene->sceneRect().height());
	QImage img;
	QPainter painter(&map);
	scene->render(&painter);
	painter.end();

	img = map.toImage();
	img.save("pix.png");

	QColor s1;
	QColor s2;

	int min = temp.min(points);
	int max = temp.max(points);

	std::vector<int> X;

	for (int y = min; y < max; y++) {
		for (int x = points[0].x() - 2; x < points[1].x() + 2; x++) {
			s1 = img.pixel(x, y);
			s2 = img.pixel(x + 1, y);
			if (s1 == Old && s2 != Old && s2 != New) {
				X.push_back(x);
			}
		}

		if (X.size() % 2 == 0) {
			for (int i = 0; i < X.size(); i = i + 2) {
				pen.setColor(New);
				scene->addLine(X[i] + 1, y, X[i + 1] - 1, y, pen);
			}
		}
		X.clear();
		painter.begin(&map);
		scene->render(&painter);
		painter.end();

		img = map.toImage();
		img.save("pix.png");
	}
}
void Lab3g::link(int x, int y, int& up, int& down, QColor Old) {
	QPixmap map(scene->sceneRect().width(), scene->sceneRect().height());
	QImage img;
	QPainter painter(&map);
	scene->render(&painter);
	painter.end();

	img = map.toImage();
	img.save("pix.png");

	QColor s1;
	QColor s2;

	up = 0;
	down = 0;

	s1 = img.pixel(x - 1, y + 1);
	if (s1 == Old) {
		up++;
	}
	s1 = img.pixel(x - 1, y - 1);
	if (s1 == Old) {
		down++;
	}
	s1 = img.pixel(x, y);

	while (s1 == Old) {
		s1 = img.pixel(x, y + 1);
		s2 = img.pixel(x - 1, y + 1);
		if (s1 == Old && s2 != Old) {
			up++;
		}
		s1 = img.pixel(x, y - 1);
		s2 = img.pixel(x - 1, y - 1);
		if (s1 == Old && s2 != Old) {
			down++;
		}
		x++;
		s1 = img.pixel(x, y);
	}
	s1 = img.pixel(x - 1, y + 1);
	s2 = img.pixel(x, y + 1);
	if (s1 != Old && s2 == Old) {
		up++;
	}
	s1 = img.pixel(x - 1, y - 1);
	s2 = img.pixel(x, y - 1);
	if (s1 != Old && s2 == Old) {
		down++;
	}
}
void Lab3g::ALG4(std::vector<QPoint> points, QColor New, QColor Old) {
	
	QPixmap map(scene->sceneRect().width(), scene->sceneRect().height());
	QImage img;
	QPainter painter(&map);
	scene->render(&painter);
	painter.end();

	img = map.toImage();
	img.save("pix.png");

	int minx = points[0].x();
	int miny = points[0].y();
	int maxx = points[1].x();
	int maxy = points[2].y();

	int l = 0;

	int up = 0;
	int down = 0;
	QColor s1;

	for (int y = miny; y < maxy; y++) {
		l = 0;
		for (int x = minx; x < maxx; x++) {
			s1 = img.pixel(x, y);
			if (s1 != Old) {
				if (l % 2 != 0) {
					pen.setColor(New);
					scene->addLine(x, y, x, y, pen);
					painter.begin(&map);
					scene->render(&painter);
					painter.end();

					img = map.toImage();
					img.save("pix.png");
				}
			}
			else {
				link(x, y, up, down, Old);
				if (up == 1 && down == 1) {
					l++;
				}
				if (up + down == 2) {
					qDebug() << "ERROR";
				}
			}
		}
	}

}

void Lab3g::showtimes() {
	QString str = "Alg 1(recusive point): " + times[0] + "\tAlg2(recursive line) : " + times[1] + "\tAlg3(XY) : " + times[2] + "\tAlg4 : " + times[3];
	scene->addText(str);
}

void Lab3g::createFig() {
	if (points.size() == 0) {
		QMessageBox warn;
		warn.setText("Please draw some points");
		warn.setIcon(QMessageBox::Warning);
		warn.exec();
	}
	else {
		fig = true;
		po = false;
		QLine line;
		for (int i = 0; i < points.size() - 1; i++) {
			line = QLine(points[i], points[i + 1]);
			scene->addLine(line, pen);
		}
		line = QLine(points[points.size() - 1], points[0]);
		scene->addLine(line, pen);
	}
}