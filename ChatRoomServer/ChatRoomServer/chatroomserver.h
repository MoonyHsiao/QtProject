#ifndef CHATROOMSERVER_H
#define CHATROOMSERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_chatroomserver.h"
#include "tcpserver.h"
#include <QLabel>
#include <QObject>
#include <QNetworkInterface>
#pragma execution_character_set("utf-8") //中文不亂碼顯示
class ChatRoomServer : public QMainWindow
{
	Q_OBJECT
public:
	ChatRoomServer(QWidget *parent = 0);
	~ChatRoomServer();
	QString serverStr = "Server IP : %1";
	QLabel *lblServerIp;
	QString onlineUser = "Online User : %1";
	QLabel *lblOnlineUser;
public slots :
	void getPeople(int num);
private:
	QString getIP();
	Ui::ChatRoomServerClass ui;
};

#endif // CHATROOMSERVER_H
