#include "Lines.h"

Lines::Lines(int x1, int y1, int x2, int y2, bool L, bool R){
	point1.setX(x1);
	point2.setX(x2);
	point1.setY(y1);
	point2.setY(y2);
	pen.setWidth(2);
	left = L;
	right = R;
}

Lines::~Lines(){}

void Lines::draw() {
	pen.setColor(color);
	painter->setPen(pen);
	painter->drawLine(point1, point2);
	if (left) {
		draw_left();
	}
	if (right) {
		draw_right();
	}
}

void Lines::on() {
	pen.setColor(Qt::red);
	painter->setPen(pen);
	painter->drawLine(point1, point2);
	if (left) {
		draw_left();
	}
	if (right) {
		draw_right();
	}
}

void Lines::off(){ 
	draw();
}

void Lines::set_painter(QPainter* pointer){
	painter = pointer;
}

void Lines::set_color(const QColor temp) {
	color = temp;
}

bool Lines::get_blink_status() {
	return blink_status;
}

void Lines::set_blink_status(bool status){ 
	blink_status = status;
}

void Lines::set_name(QString name, QLabel *temp){
	temp->setText(name);
	temp->setGeometry(point1.x() + (point2.x() / 4) - name.length() * temp->fontInfo().pixelSize(), point1.y() - 20, name.length()*temp->fontInfo().pixelSize(), 20);
	temp->show();
}

void Lines::draw_left() {
	QPoint temp(point1.x() + 10, point1.y() - 3);
	painter->drawLine(point1, temp);
	temp.setY(point1.y() + 3);
	painter->drawLine(point1, temp);
}

void Lines::draw_right() {
	QPoint temp(point2.x() - 10, point2.y() - 3);
	painter->drawLine(point2, temp);
	temp.setY(point2.y() + 3);
	painter->drawLine(point2, temp);
}
