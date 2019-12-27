#include "Lab4g.h"

Lab4g::Lab4g(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	scene = new QGraphicsScene;
	ui.graphicsView->setScene(scene);
	ui.graphicsView->scale(2, 2);

	connect(ui.Kline, SIGNAL(clicked()), this, SLOT(kohl()));
	connect(ui.Ksnow, SIGNAL(clicked()), this, SLOT(kohs()));
	connect(ui.tri, SIGNAL(clicked()), this, SLOT(tri()));
	connect(ui.rect, SIGNAL(clicked()), this, SLOT(rect()));
	connect(ui.pap, SIGNAL(clicked()), this, SLOT(pap()));
	connect(ui.man, SIGNAL(clicked()), this, SLOT(man()));
	
	

	connect(ui.RtP, SIGNAL(clicked()), this, SLOT(RtP()));
	connect(ui.RtM, SIGNAL(clicked()), this, SLOT(RtM()));

	connect(ui.lvlup, SIGNAL(clicked()), this, SLOT(lvlup()));
	connect(ui.lvldw, SIGNAL(clicked()), this, SLOT(lvldw()));

}

void Lab4g::kohl() {
	if (check()) {
		temp = new KohLine();
		temp->start(scene);
		status->kl = true;
	}
}

bool Lab4g::check() {
	if (status->func()) {
		QMessageBox warn;
		warn.setIcon(QMessageBox::Warning);
		warn.setText("This action will clear the screen");
		warn.addButton(QMessageBox::Button::Yes);
		warn.addButton(QMessageBox::Button::No);
		int ret = warn.exec();
		if (ret == QMessageBox::Button::Yes) {
			if (status->ks) {
				tempSnow->~KohSnow();
			}
			else if (status->kl) {
				temp->~KohLine();
			}
			else if (status->tr) {
				tempTri->~Triangle();
			}
			else if (status->rt) {
				tempRec->~Rect();
			}
			else if (status->pt) {
				ui.graphicsView->scale(2, 2);
				tempPap->~Paporot();
			}
			else if (status->mn) {
				ui.graphicsView->scale(2, 2);
				tempMan->~Mandelbrod();
			}
			status = new struct flags;
			scene->~QGraphicsScene();
			scene = new QGraphicsScene;
			ui.graphicsView->setScene(scene);
			return true;
		}
		else {
			return false;
		}
	}
	return true;
	
}
void Lab4g::error(QString err) {
	QMessageBox ERR;
	ERR.setIcon(QMessageBox::Icon::Critical);
	ERR.setText(err);
	ERR.exec();
}
void Lab4g::kohs() {
	if (check()) {
		tempSnow = new KohSnow;
		tempSnow->start(scene);
		status->ks = true;
	}
}
void Lab4g::tri() {
	if (check()) {
		tempTri = new Triangle;
		tempTri->start(scene);
		status->tr = true;
	}
}
void Lab4g::rect() {
	if (check()) {
		tempRec = new Rect;
		tempRec->start(scene);
		status->rt = true;
	}
}
void Lab4g::pap() {
	if (check()) {
		ui.graphicsView->resetMatrix();
		tempPap = new Paporot;
		tempPap->start(scene);
		status->pt = true;
	}
}
void Lab4g::man() {
	if (check()) {
		ui.graphicsView->resetMatrix();
		tempMan = new Mandelbrod;
		tempMan->start(scene);
		status->pt = true;
	}
}
void Lab4g::RtP() {
	ui.graphicsView->rotate(30);
}

void Lab4g::RtM() {
	ui.graphicsView->rotate(-30);
}

void Lab4g::lvlup() {
	if (status->kl) {
		int n = temp->get_n();
		if (n > 4) {
			error("Level is to large, max level 5");
		}
		else {
			scene->clear();
			temp->set_n(n + 1);
			temp->start(scene);
		}
	}
	else if (status->ks) {

		int n = tempSnow->get_n();
		if (n > 4) {
			error("Level is to large, max level 5");
		}
		else {
			scene->clear();
			tempSnow->set_n(n + 1);
			tempSnow->start(scene);
		}
	}
	else if (status->tr) {
		int n = tempTri->get_n();
		if (n > 4) {
			error("Level is to large, max level 5");
		}
		else {
			scene->clear();
			tempTri->set_n(n + 1);
			tempTri->start(scene);
		}
	}
	else if (status->rt) {
		int n = tempRec->get_n();
		if (n > 4) {
			error("Level is to large, max level 5");
		}
		else {
			scene->clear();
			tempRec->set_n(n + 1);
			tempRec->start(scene);
		}
	}

}

void Lab4g::lvldw() {
	if (status->kl) {
		int n = temp->get_n();
		if (n < 1) {
			error("Level is to small, min level 0");
		}
		else {
			scene->clear();
			temp->set_n(n - 1);
			temp->start(scene);
		}
	}
	else if (status->ks) {
		int n = tempSnow->get_n();
		if (n < 1) {
			error("Level is to small, min level 0");
		}
		else {
			scene->clear();
			tempSnow->set_n(n - 1);
			tempSnow->start(scene);
		}
	}
	else if (status->tr) {
		int n = tempTri->get_n();
		if (n < 1) {
			error("Level is to small, min level 0");
		}
		else {
			scene->clear();
			tempTri->set_n(n - 1);
			tempTri->start(scene);
		}
	}
	else if (status->rt) {
		int n = tempRec->get_n();
		if (n < 1) {
			error("Level is to small, min level 0");
		}
		else {
			scene->clear();
			tempRec->set_n(n - 1);
			tempRec->start(scene);
		}
	}
}
