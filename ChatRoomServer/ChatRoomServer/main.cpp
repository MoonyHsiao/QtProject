#include "chatroomserver.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChatRoomServer w;
	w.show();
	return a.exec();
}
