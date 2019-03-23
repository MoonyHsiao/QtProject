#include "sockethelper.h"


SocketHelper::SocketHelper(QObject *parent, int _serverID, QString _serverName)
	: QObject(parent), m_serverID(_serverID), m_serverName(_serverName)
{

	server = new QTcpServer(this);
	connect(server, SIGNAL(newConnection()), SLOT(newConnection()));

	server->listen(QHostAddress::Any, m_serverID);
	//qDebug() << "Listening:" << server->listen(QHostAddress::Any, 5488);

}

SocketHelper::~SocketHelper()
{

}

void SocketHelper::newConnection()
{

	while (server->hasPendingConnections())
	{
		socket = server->nextPendingConnection();
		connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
		connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
		QByteArray *buffer = new QByteArray();
		qint32 *s = new qint32(0);
		buffers.insert(socket, buffer);
		sizes.insert(socket, s);
		QHostInfo hostInfo;
		QString powerInfoString = m_serverName + "!" + hostInfo.localHostName() + "&";
		QString re = powerInfoString;
		QByteArray response = re.toUtf8();
		socket->write(response);
		m_connectCount += 1;
		qDebug() << "新連線";
	}

}

void SocketHelper::disconnected()
{
	qInfo("Socket:disconnected");
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	QByteArray *buffer = buffers.value(socket);
	qint32 *s = sizes.value(socket);
	socket->deleteLater();
	delete buffer;
	delete s;
	m_connectCount -= 1;

}

void SocketHelper::readyRead() {

	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	char buffer[8192] = { 0 };
	socket->read(buffer, socket->bytesAvailable());
	QString re = appSetupMode_Duo(buffer);
}

void SocketHelper::initMsgFromMain(QByteArray source) {

	QString re = (QString)source;
	QStringList splitRe = re.split(" ");
	//{"command":"0", "Data":{"Light":"01", "LightMode":"01", "rColor":"255", "gColor":"0", "bColor":"255", "Brightness":"99"}}

	QJsonObject data_json_obj;
	data_json_obj.insert("Light", splitRe[1]);
	data_json_obj.insert("LightMode", splitRe[2]);
	data_json_obj.insert("rColor", splitRe[3]);
	data_json_obj.insert("gColor", splitRe[4]);
	data_json_obj.insert("bColor", splitRe[5]);
	data_json_obj.insert("Brightness", splitRe[6]);
	QJsonObject command_json_obj;
	command_json_obj.insert("command", "1");
	command_json_obj.insert("Data", data_json_obj);
	QJsonDocument doc(command_json_obj);

	QString string1(doc.toJson());
	QString enCodeString1 = base64_encode(string1);
	QByteArray response = enCodeString1.toUtf8() + "&";
	socket->write(response); //送回去給Client
}


QString SocketHelper::appSetupMode_Duo(char * appMode)
{
	CString appModeStr = (CString)appMode;
	QString decodeString;
	for (int i = 0; i < appModeStr.GetLength(); i++)
	{
		decodeString += appModeStr[i];
	}

	//emit socketHelperMessage(base64_decode(decodeString));
	emit socketHelperMessage(decodeString);
	return appMode;
}

QString SocketHelper::base64_decode(QString string) {
	QByteArray ba;
	ba.append(string);
	return QByteArray::fromBase64(ba);
}

QString SocketHelper::base64_encode(QString string) {
	QByteArray ba;
	ba.append(string);
	return ba.toBase64();
}