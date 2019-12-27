#pragma once
#include <cmath>
#include <QGraphicsScene>


class KohLine {

public:
	KohLine() {};
	~KohLine() {};
	void start(QGraphicsScene *&scene);
	void set_n(int N) { n = N; }
	int get_n() { return n; }

	

protected:

	int n = 0;

	void Draw(QGraphicsScene*& scene, double x, double y, double x2, double y2, int n);
};

