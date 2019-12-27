#pragma once
#include <QPainter>
#include <Qlabel>

class Lines {

public:
	Lines(int x1, int y1, int x2, int y2, bool L, bool R);
	~Lines();

	void draw();
	void on();
	void off();
	void set_painter(QPainter *pointer);
	void set_color(const QColor temp);
	bool get_blink_status();
	void set_blink_status(bool status);

	void set_name(QString name, QLabel *temp);

	void draw_left();
	void draw_right();
private:
	QPen pen;
	QPainter* painter;
	QPoint point1;
	QPoint point2;
	QColor color;
	bool blink_status = false;

	bool left = false;
	bool right = false;
};

