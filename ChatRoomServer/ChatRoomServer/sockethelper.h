#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include <QObject>

#include <atlstr.h>
#pragma execution_character_set("utf-8") //中文不亂碼顯示

//Socket
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>

class SocketHelper : public QObject
{
	Q_OBJECT

public:
	SocketHelper(QObject *parent, int _serverID,QString _serverName);
	~SocketHelper();

	enum SockCommEnumDuo
	{
		GetInit,
		SetupLight,
		SetLightOn
	};

private:
	int m_serverID = 0;
	QString m_serverName = "aa";
	int m_connectCount = 0;
	QTcpServer *server;
	QHash<QTcpSocket*, QByteArray*> buffers;
	QHash<QTcpSocket*, qint32*> sizes;
	QString appSetupMode_Duo(char* appMode);
	QString base64_decode(QString);
	QString base64_encode(QString string);

	QTcpSocket *socket;


	public slots :
	void newConnection();
	void disconnected();
	void readyRead();
	void initMsgFromMain(QByteArray);

signals:
	void socketHelperMessage(QString);
};

#endif // SOCKETHELPER_H
