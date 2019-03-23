#include "chatroomclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChatRoomClient w;
	w.show();
	return a.exec();
}
