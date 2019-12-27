#include "Labgraph2.h"

Labgraph2::Labgraph2(QWidget *parent): QMainWindow(parent) {
	ui.setupUi(this);
	connect(ui.RotateL, SIGNAL(clicked()), this, SLOT(rotateM()));
	connect(ui.RotateR, SIGNAL(clicked()), this, SLOT(rotateP()));
	connect(ui.scaleM, SIGNAL(clicked()), this, SLOT(scaleM()));
	connect(ui.ScaleP, SIGNAL(clicked()), this, SLOT(scaleP()));
}

double Labgraph2::F(double num) {
	if (num < 0) {
		qDebug() << "num < 0";
		return 1;
	}
	else if (num == 0) {
		return 1;
	}
	double result = 1;

	for (int i = 1; i <= num; i++) {
		result = result * i;
	}
	return result;
}

QPoint Labgraph2::calculate(double t, std::vector<QPoint> points) {
	double x = 0;
	double y = 0;

	const int size = points.size();

	for (int i = 0; i < size; i++) {
		const double X = points[i].x();
		const double Y = points[i].y();

		x = x + (F(size) / (F(i) - F(size - i)) * X * pow(t, i) * pow(1 - t, size -i));
		y = y + (F(size) / (F(i) - F(size - i)) * Y * pow(t, i) * pow(1 - t, size - i));

	}

	return QPoint(static_cast<int>(x), static_cast<int>(y));
}

void Labgraph2::draw_def(QPainter *painter, std::vector<QPoint> points) {
	QPoint nowPoint;
	QPoint prevPoint;

	for (double t = 0.0; t < 1.0; t = t + 0.01) {
		nowPoint = calculate(t, points);
		
		if (t == 0.0) {
			prevPoint = nowPoint;
			continue;
		}

		painter->drawLine(prevPoint, nowPoint);
		prevPoint = nowPoint;
	}
}

void Labgraph2::rotateP() {
	rotate = rotate + 20;
	this->repaint();
}

void Labgraph2::scaleP() {
	scale++;
	this->repaint();
}

void Labgraph2::scaleM() {
	scale--;
	this->repaint();
}
void Labgraph2::rotateM() {
	rotate = rotate - 20;
	this->repaint();
}

void Labgraph2::paintEvent(QPaintEvent* event){
	Q_UNUSED(event);
	QPainter *painter = new QPainter(this);
	std::vector<QPoint> points;
	QPen pen;
	pen.setWidth(10);
	pen.setColor(Qt::green);
	points.push_back(QPoint(50, 150));
	points.push_back(QPoint(70, 170));
	points.push_back(QPoint(400, 300));

	painter->rotate(rotate);
	painter->scale(scale, scale);
	draw_def(painter, points);
}