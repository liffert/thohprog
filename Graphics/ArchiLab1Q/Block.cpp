#include "Block.h"

Block::Block(int x, int y, int w, int h){
	rect.setX(x);
	rect.setY(y);
	rect.setWidth(w);
	rect.setHeight(h);
	pen.setWidth(4);
}

Block::~Block() {}

void Block::draw_rect() {
	pen.setColor(color);
	painter->setPen(pen);
	painter->drawRect(rect);
}

void Block::draw_circle_in_rect() {
	painter->drawEllipse(rect.x() + rect.width()/4, rect.y() + rect.height()/2, 50, 50);
	painter->drawLine(rect.x() + rect.width() / 2, rect.y() + rect.height() - 75, rect.x() + rect.width()/2 - 20, rect.y() + rect.height() - 60);
	painter->drawLine(rect.x() + rect.width() / 2, rect.y() + rect.height() - 75, rect.x() + rect.width() / 2 + 20, rect.y() + rect.height() - 60);
	painter->drawLine(rect.x() + rect.width() / 2, rect.y() + rect.height() - 75, rect.x() + rect.width() / 2 + 20, rect.y() + rect.height() - 90);
	painter->drawLine(rect.x() + rect.width() / 2, rect.y() + rect.height() - 75, rect.x() + rect.width() / 2 - 20, rect.y() + rect.height() - 90);
}

void Block::set_painter(QPainter* pointer) {
	painter = pointer;
	painter->setPen(pen);
}

void Block::set_color(const QColor temp) {
	color = temp;
}

void Block::set_name(QString name, QLabel *temp){ 
	temp->setText(name);
	temp->setGeometry(rect.x() + rect.width()/3 - name.length(), rect.y() + rect.height() / 3, name.length()*temp->fontInfo().pixelSize(), 30);
	temp->show();
}

void Block::on() {
	pen.setColor(Qt::gray);
	painter->setPen(pen);
	painter->drawRect(rect);
}

void Block::off() {
	draw_rect();
}

QRect Block::get() {
	return rect;
}

bool Block::get_blink_status() {
	return blink_status;
}

void Block::set_blink_status(bool status){
	blink_status = status;
}
