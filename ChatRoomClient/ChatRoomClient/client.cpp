#include "client.h"
#include <QDataStream>
#include "chatCMD.h"
#include <QDebug>
#include <QTimer>
Client::Client(QObject *parent, int _port, QString _serverIP) :
	QObject(parent), m_port(_port), m_serverIP(_serverIP)
{
	tcpConnected();
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(dataChatMsgSend2()));
	//timer->start(5000);
}

QString Client::userId() const
{
	return m_userId;
}

void Client::setUserId(const QString &userId)
{
	if (m_userId != userId)
	{
		m_userId = userId;
		emit userIdChanged();
	}
}

QString Client::userName() const
{
	return m_userName;
}

void Client::setUserName(const QString &userName)
{
	if (m_userName != userName)
	{
		m_userName = userName;
		emit userNameChanged();
	}
}

QString Client::userPower() const
{
	return m_userPower;
}

void Client::setUserPower(const QString &userPower)
{
	if (m_userPower != userPower)
	{
		m_userPower = userPower;
		emit userPowerChanged();
	}
}

QString Client::groupId() const
{
	return m_groupId;
}

void Client::setGroupId(const QString &groupId)
{
	if (m_groupId != groupId)
	{
		m_groupId = groupId;
		emit groupIdChanged();
	}
}

QString Client::groupName() const
{
	return m_groupName;
}

void Client::setGroupName(const QString &groupName)
{
	if (m_groupName != groupName)
	{
		m_groupName = groupName;
		emit groupNameChanged();
	}
}

void Client::tcpConnected()
{
	tcpSocket = new QTcpSocket(this);
	serverIP = new QHostAddress();
	serverIP->setAddress(m_serverIP); //連接IP
									   // tcpSocket->connectToHost();
	tcpSocket->connectToHost(*serverIP, m_port);

	connect(tcpSocket, SIGNAL(connected()), this, SLOT(sureConnected()));
	connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(sureDisConnected()));
}

void Client::dataLoginSend()
{
	qDebug() << "loginsend";

	loginStruct loginData;
	QByteArray name = m_userName.toLocal8Bit();
	char*namechar = name.data();
	strcpy(loginData.name, namechar);
	//QByteArray power = m_userPower.toLocal8Bit();
	QString IP = getIP();
	QByteArray power = IP.toLocal8Bit();
	char *powerchar = power.data();
	strcpy(loginData.powerpoint, powerchar);
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(loginStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(Login);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &loginData, sizeof(loginStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::dataChatMsgSend(QString groupid, QString username, QString chatmsg)
{
	dataChatMsgStruct dataChatMsgData;
	
	QByteArray id = groupid.toLocal8Bit();
	char *idchar = id.data();
	strcpy(dataChatMsgData.group_id, idchar);

	QByteArray name = username.toLocal8Bit();
	char *namechar = name.data();
	strcpy(dataChatMsgData.user_name, namechar);

	QByteArray msg = chatmsg.toLocal8Bit();
	char *msgchar = msg.data();
	strcpy(dataChatMsgData.msg, msgchar);
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(dataChatMsgStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(Msg);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &dataChatMsgData, sizeof(dataChatMsgStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::dataChatRoomEnter(QString groupid, QString username, QString chatmsg)
{
	dataChatMsgStruct dataChatMsgData;

	QByteArray id = groupid.toLocal8Bit();
	char *idchar = id.data();
	strcpy(dataChatMsgData.group_id, idchar);

	QByteArray name = username.toLocal8Bit();
	char *namechar = name.data();
	strcpy(dataChatMsgData.user_name, namechar);

	QByteArray msg = chatmsg.toLocal8Bit();
	char *msgchar = msg.data();
	strcpy(dataChatMsgData.msg, msgchar);
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(dataChatMsgStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(LoginNotifi);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &dataChatMsgData, sizeof(dataChatMsgStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::dataSendFileName(QString serverAddress, QString clientAddress, QString fileName)
{
	dataFileNameStruct dataFileNameData;
	
	QByteArray serverAddr = serverAddress.toLocal8Bit();
	char *serverAddrchar = serverAddr.data();
	strcpy(dataFileNameData.serverAddr, serverAddrchar);

	QByteArray clientAddr = clientAddress.toLocal8Bit();
	char *clientAddrchar = clientAddr.data();
	strcpy(dataFileNameData.clientAddr, clientAddrchar);

	QByteArray fileN = fileName.toLocal8Bit();
	char *fileNchar = fileN.data();
	strcpy(dataFileNameData.fileName, fileNchar);
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(dataFileNameStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(FileName);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &dataFileNameData, sizeof(dataFileNameStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::dataFileRefuse(QString serverAddress)
{
}

void Client::dataRefreshUserInfo()
{
	dataChatMsgStruct dataChatMsgData;
	QString groupid = "aaa";
	QString username = "aaa";
	QString chatmsg = "aaa";

	QByteArray id = groupid.toLocal8Bit();
	char *idchar = id.data();
	strcpy(dataChatMsgData.group_id, idchar);

	QByteArray name = username.toLocal8Bit();
	char *namechar = name.data();
	strcpy(dataChatMsgData.user_name, namechar);

	QByteArray msg = chatmsg.toLocal8Bit();
	char *msgchar = msg.data();
	strcpy(dataChatMsgData.msg, msgchar);
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(dataChatMsgStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(UesrInfo);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &dataChatMsgData, sizeof(dataChatMsgStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::dataChatMsgSend2()
{
	QString groupid = "121";
	QString username = "aaa";
	QString chatmsg = "hello";
	dataChatMsgStruct dataChatMsgData;
	
	QByteArray id = groupid.toLocal8Bit();
	char *idchar = id.data();
	strcpy(dataChatMsgData.group_id, idchar);

	QByteArray name = username.toLocal8Bit();
	char *namechar = name.data();
	strcpy(dataChatMsgData.user_name, namechar);

	QByteArray msg = chatmsg.toLocal8Bit();
	char *msgchar = msg.data();
	strcpy(dataChatMsgData.msg, msgchar);
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(dataChatMsgStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(Msg);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &dataChatMsgData, sizeof(dataChatMsgStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::dataAddGroupSend(QString group_name)
{
	addGroupStruct addGroupData;

	QByteArray name = group_name.toLocal8Bit();
	char *namechar = name.data();
	strcpy(addGroupData.name, namechar);

	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(addGroupStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(AddGroup);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &addGroupData, sizeof(addGroupStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}


void Client::dataConnectSend()
{
	connectSuccessStruct connectSuce;
	// connectSuce.str = "connect success";
	strcpy(connectSuce.str, "connect success");
	//構造數據包
	qint64 totalBytes = 2 * sizeof(qint64) + sizeof(connectSuccessStruct);
	QByteArray outBlock;
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_2);
	outBlock.resize(totalBytes);
	//向緩衝區寫入文件頭
	sendOut << totalBytes << qint64(Connet_Success);
	mutex.lock();
	memcpy(outBlock.data() + 2 * sizeof(qint64), &connectSuce, sizeof(connectSuccessStruct));
	mutex.unlock();
	tcpSocket->write(outBlock);
	outBlock.resize(0);
}




void Client::dataReceived()
{
	if (tcpSocket->bytesAvailable() <= 0)
	{
		return;
	}


	QByteArray  buffer;//從緩存區中去除數據 但是不確定取出來的字節數
	buffer = tcpSocket->readAll();
	m_buffer.append(buffer);//Need to use the length to do a while loop. It is possible to read more than two complete records at once.
	unsigned int totalLen = m_buffer.size();//When more than one complete less than the second complete record, if the length of the header has been reached, the header is saved first.

	while (totalLen) {
		//Bind with QDataStream for easy operation
		QDataStream  packet(m_buffer);
		packet.setVersion(QDataStream::Qt_5_2);
		//Not enough length of the header is not processed, ending the while loop
		if (totalLen < 2 * sizeof(qint64))
			break;
		//Read the header into the protocol according to the definition. Read the command length first, then read the type of the command.
		packet >> totalBytes >> serverCmd;
		//If the length of the content in the cache does not reach the length of the command, then it will end first, and then it will be enough to parse it.
		if (totalLen < totalBytes)
			break;
		//Start long enough to start parsing
		switch (serverCmd)
		{
		case Login_answer:
		{
			serverLoginAnswerStruct serverLoginData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&serverLoginData, realStateData.data(), sizeof(serverLoginAnswerStruct));
			motionMutex.unlock();

			emit getLoginAnswer(serverLoginData.sureLogin);

			break;
		}
		
		case AddGroup_answer:
		{
			serverAddGroupStruct serverAddGroupData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&serverAddGroupData, realStateData.data(), sizeof(serverAddGroupStruct));
			motionMutex.unlock();

			QString name = QString::fromLocal8Bit(serverAddGroupData.name);
			QString id = QString::fromLocal8Bit(serverAddGroupData.id);
			emit signalAddGroup(id, name);

			break;
		}
		case Msg_send:
		{
			serverMsgStruct serverMsgData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&serverMsgData, realStateData.data(), sizeof(serverMsgStruct));
			motionMutex.unlock();

			QString user_name = QString::fromLocal8Bit(serverMsgData.user_name);
			QString group_id = QString::fromLocal8Bit(serverMsgData.group_id);
			QString msg = QString::fromLocal8Bit(serverMsgData.msg_data);
			emit signalMsg(user_name, group_id, msg);

			break;
		}

		case LoginNotifi_Broadcast:
		{
			serverMsgStruct serverMsgData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&serverMsgData, realStateData.data(), sizeof(serverMsgStruct));
			motionMutex.unlock();

			QString user_name = QString::fromLocal8Bit(serverMsgData.user_name);
			emit signalUserEnterRoom(user_name);

			break;
		}

		case UesrInfo_Broadcast:
		{
			loginStruct loginData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&loginData, realStateData.data(), sizeof(loginStruct));
			motionMutex.unlock();

			QString user_name = QString::fromLocal8Bit(loginData.name);
			QString powerpoint = QString::fromLocal8Bit(loginData.powerpoint);
			emit signalRefreshUserInfo(user_name, powerpoint);

			break;
		}
		case LeftUesrInfo_Broadcast:
		{
			loginStruct loginData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&loginData, realStateData.data(), sizeof(loginStruct));
			motionMutex.unlock();

			QString user_name = QString::fromLocal8Bit(loginData.name);
			QString powerpoint = QString::fromLocal8Bit(loginData.powerpoint);
			emit signalLeftRefreshUserInfo(user_name, powerpoint);

			break;
		}

		case FileName_send:
		{
			dataFileNameStruct fileData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&fileData, realStateData.data(), sizeof(dataFileNameStruct));
			motionMutex.unlock();

			QString serverAdd = QString::fromLocal8Bit(fileData.serverAddr);
			QString clientAdd = QString::fromLocal8Bit(fileData.clientAddr);
			QString file = QString::fromLocal8Bit(fileData.fileName);
			if (clientAdd == getIP()) {
				//emit signalLeftRefreshUserInfo(user_name, powerpoint);
				qDebug() << "this get fileName";
				emit hasPendingFile(serverAdd, clientAdd, file);
			}
			break;
		}
		}
		//緩存多餘的數據
		buffer = m_buffer.right(totalLen - totalBytes); //截取下一個數據包的數據，留作下次讀取
		totalLen = buffer.size();
		//更新多餘的數據
		m_buffer = buffer;
	}
}

void Client::sureConnected()
{
	qDebug() << "have connected";
	//emit getLoginAnswer(true);
}

void Client::sureDisConnected()
{
	qDebug() << "have Disconnected";
	emit serverLeft();
}

QString Client::getIP()
{
	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress addr, list) {
		if (addr.protocol() == QAbstractSocket::IPv4Protocol)
			return addr.toString();
	}
	return 0;
}