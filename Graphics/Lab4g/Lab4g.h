#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab4g.h"
#include <QGraphicsView>
#include "KohLine.h"
#include <QMessageBox>
#include "KohSnow.h"
#include "Triangle.h"
#include "Rect.h"
#include "Mandelbrod.h"
#include "Paporot.h"

class Lab4g : public QMainWindow {
	Q_OBJECT

public:
	Lab4g(QWidget *parent = Q_NULLPTR);

private:
	Ui::Lab4gClass ui;

	struct flags {
		bool kl = false;
		bool ks = false;
		bool tr = false;
		bool rt = false;
		bool pt = false;
		bool mn = false;
		bool func() {
			if (ks || kl || tr || rt || pt || mn) {
				return true;
			}
			return false;
		};
	}; struct flags *status = new struct flags;

	KohLine* temp;
	KohSnow* tempSnow;
	Triangle* tempTri;
	Rect* tempRec;
	Paporot* tempPap;
	Mandelbrod* tempMan;

	bool check();
	void error(QString err);

private slots:
	void kohl();
	void kohs();
	void tri();
	void rect();
	void pap();
	void man();

	void RtP();
	void RtM();
	
	void lvlup();
	void lvldw();

protected:
	
	QGraphicsScene *scene;
};
