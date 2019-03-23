#include "chatroomserver.h"

ChatRoomServer::ChatRoomServer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	TcpServer *tcpserver = new TcpServer(this,8010);
	setWindowIcon(QPixmap("Image/zero.png"));
	connect(tcpserver, SIGNAL(sentPeople(int)), this, SLOT(getPeople(int)));
	qDebug() << getIP();

	lblServerIp = new QLabel(this);
	lblServerIp->setObjectName(QStringLiteral("lblIPTitle"));
	lblServerIp->setGeometry(QRect(20, 100, 300, 40));
	lblServerIp->setText(serverStr.arg(getIP()));
	QFont fonta = lblServerIp->font();
	fonta.setPointSize(20);
	lblServerIp->setFont(fonta);


	lblOnlineUser = new QLabel(this);
	lblOnlineUser->setObjectName(QStringLiteral("lblIPTitle"));
	lblOnlineUser->setGeometry(QRect(20, 160, 300, 40));
	lblOnlineUser->setText(onlineUser.arg(0));
	lblOnlineUser->setFont(fonta);
}

ChatRoomServer::~ChatRoomServer()
{

}
void ChatRoomServer::getPeople(int num)
{
	qDebug() << num;
	lblOnlineUser->setText(onlineUser.arg(num));
}
QString ChatRoomServer::getIP()
{
	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress addr, list) {
		if (addr.protocol() == QAbstractSocket::IPv4Protocol)
			return addr.toString();
	}
	return 0;
}

