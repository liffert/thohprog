#pragma once
#include "QPainter"
#include "QLabel"

class Block {

public:
	Block(int x, int y, int w, int h);
	~Block();

	void draw_rect();
	void draw_circle_in_rect();

	void set_painter(QPainter* painter);
	void set_color(const QColor temp);
	void set_name(QString name, QLabel *temp);

	void on();
	void off();

	QRect get();

	bool get_blink_status();
	void set_blink_status(bool status);


protected:
	QColor color = Qt::black;

private:
	QPen pen;
	QPainter* painter;
	QRect rect;
	bool blink_status = false;
};