#include "tcpserver.h"
#include "tcpclientsocket.h"
#include "tcpgroup.h"
#include "tcpuser.h"

#include "chatCMD.h"
#include <QDataStream>
#include <iostream>
#include <QDebug>

TcpServer::TcpServer(QObject *parent, quint16 port)
	:QTcpServer(parent)
{
	if (!listen(QHostAddress::Any, port))
	{
		qDebug() << "do not listen";
	}
	else {
		connectDatabase();
		//createDatabase();
		qDebug() << "start\n";

	}
}



void TcpServer::incomingConnection(qintptr socketDescriptor)
{
	TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
	tcpClientSocket->linkServer(this);

	connect(tcpClientSocket, SIGNAL(doAddGroup(QString)), this, SLOT(doAddGroup(QString)));
	connect(tcpClientSocket, SIGNAL(doSendChatData(QString, QString, QString)), this, SLOT(updateMsgClients(QString, QString, QString)));
	connect(tcpClientSocket, SIGNAL(doSendUserEnter(QString)), this, SLOT(doUpdateUserEnter(QString)));
	connect(tcpClientSocket, SIGNAL(doSendRefreshUserInfo()), this, SLOT(doRefreshUserInfo()));
	connect(tcpClientSocket, SIGNAL(disconnected(qintptr)), this, SLOT(slotDisconnection(qintptr)));

	connect(tcpClientSocket, SIGNAL(doSendFileNameData(QString, QString, QString)), this, SLOT(updateFileNameClients(QString, QString, QString)));
	tcpClientSocket->setSocketDescriptor(socketDescriptor);
	qDebug() << "connect:" << socketDescriptor;

	tcpClientSocketList.append(tcpClientSocket);
}

void TcpServer::dataAddGroupSend(QString groupid, QString groupname)
{
	serverAddGroupStruct addGroupData;
	QByteArray id = groupid.toLocal8Bit();
	char *idchar = id.data();
	strcpy(addGroupData.id, idchar);

	QByteArray name = groupname.toLocal8Bit();
	char *namechar = name.data();
	strcpy(addGroupData.name, namechar);
	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		QTcpSocket *item = tcpClientSocketList.at(i);

		//构造数据包
		qint64 totalBytes = 2 * sizeof(qint64) + sizeof(serverAddGroupStruct);
		QByteArray outBlock;
		QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
		sendOut.setVersion(QDataStream::Qt_5_2);
		outBlock.resize(totalBytes);
		//向缓冲区写入文件头
		sendOut << totalBytes << qint64(AddGroup_answer);
		mutex.lock();
		memcpy(outBlock.data() + 2 * sizeof(qint64), &addGroupData, sizeof(serverAddGroupStruct));
		mutex.unlock();
		item->write(outBlock);
		outBlock.resize(0);
	}
}

void TcpServer::updateMsgClients(QString username, QString groupid, QString msg)
{
	serverMsgStruct msgData;
	QByteArray id = groupid.toLocal8Bit();
	char *idchar = id.data();
	strcpy(msgData.group_id, idchar);

	QByteArray msg_data = msg.toLocal8Bit();
	char *msgchar = msg_data.data();
	strcpy(msgData.msg_data, msgchar);

	QByteArray name = username.toLocal8Bit();
	char *namechar = name.data();
	strcpy(msgData.user_name, namechar);
	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		QTcpSocket *item = tcpClientSocketList.at(i);

		//构造数据包
		qint64 totalBytes = 2 * sizeof(qint64) + sizeof(serverMsgStruct);
		QByteArray outBlock;
		QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
		sendOut.setVersion(QDataStream::Qt_5_2);
		outBlock.resize(totalBytes);
		//向缓冲区写入文件头
		sendOut << totalBytes << qint64(Msg_send);
		mutex.lock();
		memcpy(outBlock.data() + 2 * sizeof(qint64), &msgData, sizeof(serverMsgStruct));
		mutex.unlock();
		item->write(outBlock);
		outBlock.resize(0);
	}
}

void TcpServer::doAddGroup(QString groupname)
{
	int i = 0;
	for (auto temp : tcpgroups())
	{
		i++;
	}

	++i;
	db.open();
	QSqlQuery query;
	QString sql = "insert into chatgroup values('" + QString::number(i) + "', '" + groupname + "')";
	query.exec(sql);

	//发送给客户端
	dataAddGroupSend(QString::number(i), groupname);
}

void TcpServer::doUpdateUserEnter(QString username)
{
	serverMsgStruct msgData;

	QByteArray name = username.toLocal8Bit();
	char *namechar = name.data();
	strcpy(msgData.user_name, namechar);
	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		QTcpSocket *item = tcpClientSocketList.at(i);

		//构造数据包
		qint64 totalBytes = 2 * sizeof(qint64) + sizeof(serverMsgStruct);
		QByteArray outBlock;
		QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
		sendOut.setVersion(QDataStream::Qt_5_2);
		outBlock.resize(totalBytes);
		//向缓冲区写入文件头
		sendOut << totalBytes << qint64(LoginNotifi_Broadcast);
		mutex.lock();
		memcpy(outBlock.data() + 2 * sizeof(qint64), &msgData, sizeof(serverMsgStruct));
		mutex.unlock();
		item->write(outBlock);
		outBlock.resize(0);
	}
	int online = tcpClientSocketList.count();
	emit sentPeople(online);
}

void TcpServer::doRefreshUserInfo()
{


	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		loginStruct msgData;
		QTcpSocket *item = tcpClientSocketList.at(i);

		for (size_t j = 0; j < tcpClientSocketList.count(); j++)
		{
			ClientUser *aaaa = tcpClientSocketList.at(j)->getClientUser();
			QByteArray name = aaaa->username().toLocal8Bit();
			char *namechar = name.data();
			strcpy(msgData.name, namechar);
			QByteArray powerpoint = aaaa->userpowerpoint().toLocal8Bit();
			char *powerpointchar = powerpoint.data();
			strcpy(msgData.powerpoint, powerpointchar);
			//构造数据包
			qint64 totalBytes = 2 * sizeof(qint64) + sizeof(loginStruct);
			QByteArray outBlock;
			QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
			sendOut.setVersion(QDataStream::Qt_5_2);
			outBlock.resize(totalBytes);
			//向缓冲区写入文件头
			sendOut << totalBytes << qint64(UesrInfo_Broadcast);
			mutex.lock();
			memcpy(outBlock.data() + 2 * sizeof(qint64), &msgData, sizeof(loginStruct));
			mutex.unlock();
			item->write(outBlock);
			outBlock.resize(0);
		}

	}

}

void TcpServer::doLeftRefreshUserInfo(QString leftUserName)
{
	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		loginStruct msgData;
		QTcpSocket *item = tcpClientSocketList.at(i);
		
		QByteArray name = leftUserName.toLocal8Bit();
		char *namechar = name.data();
		strcpy(msgData.name, namechar);
		QByteArray powerpoint = "111";
		char *powerpointchar = powerpoint.data();
		strcpy(msgData.powerpoint, powerpointchar);
		//构造数据包
		qint64 totalBytes = 2 * sizeof(qint64) + sizeof(loginStruct);
		QByteArray outBlock;
		QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
		sendOut.setVersion(QDataStream::Qt_5_2);
		outBlock.resize(totalBytes);
		//向缓冲区写入文件头
		sendOut << totalBytes << qint64(LeftUesrInfo_Broadcast);
		mutex.lock();
		memcpy(outBlock.data() + 2 * sizeof(qint64), &msgData, sizeof(loginStruct));
		mutex.unlock();
		item->write(outBlock);
		outBlock.resize(0);
	}
	int online = tcpClientSocketList.count();
	emit sentPeople(online);
}

void TcpServer::updateFileNameClients(QString serverAddr, QString clientAddr, QString fileName)
{

	dataFileNameStruct dataFileNameData;

	QByteArray serverAddre = serverAddr.toLocal8Bit();
	char *serverAddrchar = serverAddre.data();
	strcpy(dataFileNameData.serverAddr, serverAddrchar);

	QByteArray clientAddre = clientAddr.toLocal8Bit();
	char *clientAddrchar = clientAddre.data();
	strcpy(dataFileNameData.clientAddr, clientAddrchar);

	QByteArray fileN = fileName.toLocal8Bit();
	char *fileNchar = fileN.data();
	strcpy(dataFileNameData.fileName, fileNchar);

	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		QTcpSocket *item = tcpClientSocketList.at(i);

		//构造数据包
		qint64 totalBytes = 2 * sizeof(qint64) + sizeof(dataFileNameStruct);
		QByteArray outBlock;
		QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
		sendOut.setVersion(QDataStream::Qt_5_2);
		outBlock.resize(totalBytes);
		//向缓冲区写入文件头
		sendOut << totalBytes << qint64(FileName_send);
		mutex.lock();
		memcpy(outBlock.data() + 2 * sizeof(qint64), &dataFileNameData, sizeof(dataFileNameStruct));
		mutex.unlock();
		item->write(outBlock);
		outBlock.resize(0);
	}
}

void TcpServer::slotDisconnection(qintptr descriptor)
{
	for (int i = 0; i < tcpClientSocketList.count(); i++)
	{
		QTcpSocket *item = tcpClientSocketList.at(i);

		if (item->socketDescriptor() == descriptor)
		{
			ClientUser *leftUser = tcpClientSocketList.at(i)->getClientUser();
			tcpClientSocketList.removeAt(i);
			doLeftRefreshUserInfo(leftUser->username());
			qDebug() << "remove socket:" << descriptor;

			//return;
		}
	}

	return;
}

std::vector<TcpUser *> TcpServer::tcpusers()
{
	//删除以前的vector
	for (auto &temp : _tcpusers)
	{
		delete temp;
	}
	_tcpusers.clear();

	db.open();

	QSqlQuery query;
	query.exec("select * from user");
	while (query.next()) {
		QString name = query.value(0).toString();
		QString powerpoint = query.value(1).toString();
		_tcpusers.push_back(new TcpUser(name, powerpoint));
	}
	return _tcpusers;


}

std::vector<TcpGroup *> TcpServer::tcpgroups()
{
	//删除以前的vector
	for (auto &temp : _tcpgroups)
	{
		delete temp;
	}
	_tcpgroups.clear();

	db.open();

	QSqlQuery query;
	query.exec("select * from chat"
		"group");
	while (query.next()) {
		QString id = query.value(0).toString();
		QString name = query.value(1).toString();
		_tcpgroups.push_back(new TcpGroup(id, name));
	}
	return _tcpgroups;

	//push_back https://mropengate.blogspot.com/2015/07/cc-vector-stl.html
}


void TcpServer::connectDatabase()
{

	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("chatServer.db");
	if (!db.open())
	{
		qDebug() << " db notOpen";
	}



}

void TcpServer::createDatabase()
{
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("chatServer.db");
	//database.setUserName("Tt");
	//database.setPassword("password123@");

	if (!database.open())
	{
		qDebug() << "notOpen";
	}

	QSqlQuery sql_query(database);


	/*QString create_sql =
		"create table user (name varchar(50) primary key, powerpoint varchar(20))"
		//"create table chatgroup (id varchar(20) primary key, name varchar(50))"
		//"create table groupidmax (id varchar(20) primary key)"
		//"create table moodmsg (name varchar(50), msg varchar(2048))"
		;*/

	QString create_sql =
		"create table user"
		"("
		"name varchar(50) primary key ,"
		"powerpoint varchar(20)"
		")"
		;
	//sql_query.prepare(create_sql);
	sql_query.exec(QObject::tr("create table user (name varchar(50) primary key, powerpoint varchar(20))"));
	sql_query.exec(QObject::tr("create table chatgroup (id varchar(20) primary key, name varchar(50))"));
	sql_query.exec(QObject::tr("create table groupidmax (id varchar(20) primary key)"));
	sql_query.exec(QObject::tr("create table moodmsg (name varchar(50), msg varchar(2048))"));
	if (!sql_query.exec())
	{
		qDebug() << "!sql_query.exec!";
	}
	else
	{
		qDebug() << "table created!";
	}

}




