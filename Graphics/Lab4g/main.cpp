#include "Lab4g.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	Lab4g w;
	w.showMaximized();
	return a.exec();
}
