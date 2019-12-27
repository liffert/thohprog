#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ArchiLab1Q.h"
#include <QPainter>
#include "Block.h"
#include "Lines.h"
#include <Qlabel>
#include <QPushButton>
#include <QTimer>

class ArchiLab1Q : public QMainWindow {
	Q_OBJECT

public:
	ArchiLab1Q(QWidget *parent = Q_NULLPTR);

private slots:
	void Start();
	void Stop();
	void update();

private:
	Ui::ArchiLab1QClass ui;
	Block* CPU = new Block(30, 100, 100, 200);
	Block* DLU = new Block(230, 100, 100, 200);
	Block* OBJ = new Block(430, 100, 100, 200);
	Block* DC = new Block(170, 200, 40, 100);
	

	Lines* DB = new Lines(130, 110, 230, 110, true, true);
	Lines* DB_ = new Lines(170, 114, 174, 106, false, false);
	
	Lines* CB = new Lines(130, 130, 230, 130, true, true);
	Lines* CB_ = new Lines(200, 130, 200, 140, false, false);
	Lines* CB_2 = new Lines(200, 140, 230, 140, false, true);

	Lines* AB = new Lines(130, 150, 230, 150, false, true);
	Lines* AB_ = new Lines(200, 150, 200, 160, false, false);
	Lines* AB_2 = new Lines(200, 160, 230, 160, false, true);
	Lines* AB_L = new Lines(140, 150, 140, 300, false, false);

	Lines* ABL2 = new Lines(140, 300, 170, 300, false, true);
	Lines* ABL3 = new Lines(140, 280, 170, 280, false, true);
	Lines* ABL4 = new Lines(140, 260, 170, 260, false, true);
	Lines* ABL5 = new Lines(140, 240, 170, 240, false, true);
	Lines* ABL6 = new Lines(140, 220, 170, 220, false, true);
	Lines* ABL7 = new Lines(140, 200, 170, 200, false, true);

	Lines* CS = new Lines(210, 250, 230, 250, false, true);

	Lines* Control = new Lines(330, 110, 430, 110, false, true);
	Lines* Ready = new Lines(330, 290, 430, 290, true, false);


	QLabel* Cpu = new QLabel(this);
	QLabel* Dlu = new QLabel(this);
	QLabel* Obj = new QLabel(this);
	QLabel* Dc = new QLabel(this);
	
	QLabel* Ab = new QLabel(this);
	QLabel* Cb = new QLabel(this);
	QLabel* Db = new QLabel(this);
	QLabel* Rd = new QLabel(this);
	QLabel* Co = new QLabel(this);

	QLabel* abl2 = new QLabel(this);
	QLabel* abl3 = new QLabel(this);
	QLabel* abl4 = new QLabel(this);
	QLabel* abl5 = new QLabel(this);
	QLabel* abl6 = new QLabel(this);
	QLabel* abl7 = new QLabel(this);

	QLabel* cs = new QLabel(this);
	QLabel* a0 = new QLabel(this);
	QLabel* a1 = new QLabel(this);
	QLabel* rd = new QLabel(this);
	QLabel* wr = new QLabel(this);
	QLabel* d = new QLabel(this);

	QLabel* pc0 = new QLabel(this);
	QLabel* pc4 = new QLabel(this);


	QPushButton* start = nullptr;
	QPushButton* stop = nullptr;

	bool status = false;
	QTimer *timer = new QTimer(this);
protected:
	void paintEvent(QPaintEvent* event);
};
