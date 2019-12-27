#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab3g.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPoint>
#include <vector>
#include <QMouseEvent>
#include <QCursor>
#include <QMessageBox>
#include <QColor>
#include <QDebug>
#include <QRgb>
#include <QTime>

class Lab3g : public QMainWindow {
	Q_OBJECT

public:
	Lab3g(QWidget *parent = Q_NULLPTR);

private slots:
	void createFig();
	void createPoly();
	void start();

private:
	Ui::Lab3gClass ui;
	QGraphicsScene* scene;
	QGraphicsView* view;
	
	std::vector<QPoint> points;
	std::vector<QPoint> polyhedron;
	void setUPpolyhedron(int left = 0);
	void mousePressEvent(QMouseEvent *event);

	void ALG1(QPoint point, QColor New, QColor Old);
	void ALG2(QPoint point, QColor New, QColor Old);
	void ALG3(std::vector<QPoint> points, QColor New, QColor Old);
	void link(int x, int y, int& up, int& down, QColor Old);
	void ALG4(std::vector<QPoint> points, QColor New, QColor Old);

	void showtimes();
	QPen pen;

	bool fig = false;
	bool po = false;
	
	QTime *time;

	QString times[4];
	int count = 3;
	int step = 0;
};
