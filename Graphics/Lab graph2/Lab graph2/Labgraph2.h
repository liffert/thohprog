#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Labgraph2.h"
#include <Qpainter>
#include <QDebug>
#include <vector>

class Labgraph2 : public QMainWindow {
	Q_OBJECT
public:
	Labgraph2(QWidget *parent = Q_NULLPTR);

private:
	Ui::Labgraph2Class ui;
	double F(double num);
	QPoint calculate(double t, std::vector<QPoint> points);
	void draw_def(QPainter *painter, std::vector<QPoint> points);
	int rotate = 0;
	int scale = 1;

private slots:
	void rotateP();
	void scaleP();
	void rotateM();
	void scaleM();

protected:
	void paintEvent(QPaintEvent* event);
};
