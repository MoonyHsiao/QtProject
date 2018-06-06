#include "qtcontrol.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtControl w;
	w.show();
	return a.exec();
}
