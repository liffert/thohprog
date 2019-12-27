#include "ArchiLab1Q.h"

ArchiLab1Q::ArchiLab1Q(QWidget *parent): QMainWindow(parent) {
	ui.setupUi(this);
	start = new QPushButton("Start", this);
	stop = new QPushButton("Stop", this);
	connect(start, SIGNAL(clicked()), this, SLOT(Start()));
	connect(stop, SIGNAL(clicked()), this, SLOT(Stop()));
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	QRect temp = OBJ->get();
	start->setGeometry(temp.x() + 2, temp.y() + temp.height() - 32, 4 * start->fontInfo().pixelSize(), 30);
	stop->setGeometry(temp.x() + temp.width() - 4 * start->fontInfo().pixelSize() - 2, temp.y() + temp.height() - 32, 4 * start->fontInfo().pixelSize(), 30);
	CPU->set_name("CPU", Cpu);
	DLU->set_name("PPI", Dlu);
	OBJ->set_name("OBJ", Obj);

	AB->set_name("AB", Ab);
	CB->set_name("CB", Cb);
	DB->set_name("DB 8", Db);
	Ready->set_name("Ready", Rd);
	Control->set_name("Control", Co);
	DC->set_name("DC", Dc);
	ABL2->set_name("AB7", abl2);
	ABL3->set_name("AB6", abl3);
	ABL4->set_name("AB5", abl4);
	ABL5->set_name("AB4", abl5);
	ABL6->set_name("AB3", abl6);
	ABL7->set_name("AB2", abl7);


	cs->setText("CS");
	cs->setGeometry(240, 240, 50, 20);
	cs->show();
	
	a0->setText("A0");
	a0->setGeometry(240, 150, 50, 20);
	a0->show();
	
	a1->setText("A1");
	a1->setGeometry(240, 140, 50, 20);
	a1->show();

	rd->setText("!RD");
	rd->setGeometry(240, 130, 50, 20);
	rd->show();


	wr->setText("!WR");
	wr->setGeometry(240, 120, 50, 20);
	wr->show();

	d->setText("D");
	d->setGeometry(240, 100, 50, 20);
	d->show();

	pc0->setText("PC(0)");
	pc4->setGeometry(290, 280, 50, 20);
	pc0->show();

	pc4->setText("PC(4)");
	pc0->setGeometry(290, 100, 50, 20);
	pc4->show();
}

void ArchiLab1Q::update() {
	Control->set_blink_status(!Control->get_blink_status());
	ui.centralWidget->repaint();
}
void ArchiLab1Q::Start() {
	status = true;
	timer->start(1000);
	ui.centralWidget->repaint();
}
void ArchiLab1Q::Stop() {
	timer->stop();
	status = false;
	Control->set_blink_status(false);
	ui.centralWidget->repaint();
}
void ArchiLab1Q::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
	QPainter* painter = new QPainter(this);

	CPU->set_painter(painter);
	DLU->set_painter(painter);
	OBJ->set_painter(painter);
	AB->set_painter(painter);
	CB->set_painter(painter);
	DB->set_painter(painter);
	DC->set_painter(painter);
	DB_->set_painter(painter);
	Control->set_painter(painter);
	Ready->set_painter(painter);
	CB_->set_painter(painter);
	CB_2->set_painter(painter);
	AB_->set_painter(painter);
	AB_2->set_painter(painter);
	AB_L->set_painter(painter);
	ABL2->set_painter(painter);
	ABL3->set_painter(painter);
	ABL4->set_painter(painter);
	ABL5->set_painter(painter);
	ABL6->set_painter(painter);
	ABL7->set_painter(painter);
	CS->set_painter(painter);

	if (status) {
		CPU->on();
		DLU->on();
		OBJ->on();
		DC->on();
		DB->on();
		AB->on();
		CB->on();
		DB_->on();
		CB_->on();
		CB_2->on();
		AB_->on();
		AB_2->on();
		AB_L->on();
		ABL2->on();
		ABL3->on();
		ABL4->on();
		ABL5->on();
		ABL6->on();
		ABL7->on();
		CS->on();
		Ready->on();
	}
	else {
		CPU->off();
		DLU->off();
		OBJ->off();
		DC->off();
		DB->off();
		AB->off();
		CB->off();
		DB_->off();
		CB_->off();
		CB_2->off();
		AB_->off();
		AB_2->off();
		AB_L->off();
		ABL2->off();
		ABL3->off();
		ABL4->off();
		ABL5->off();
		ABL6->off();
		ABL7->off();
		CS->off();
		Ready->off();
	}

	if (Control->get_blink_status()) {
		Control->on();
		OBJ->draw_circle_in_rect();
	}
	else {
		painter->setPen(Qt::black);
		OBJ->draw_circle_in_rect();
		Control->off();
	}
}