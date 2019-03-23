#include "tcpclientsocket.h"

#include <QDataStream>
#include "tcpserver.h"
#include "tcpuser.h"
#include "tcpgroup.h"

#include "clientuser.h"
#include <QDebug>

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}

void TcpClientSocket::linkServer(TcpServer * tcpserver)
{
	_tcpserver = tcpserver;
}

ClientUser *TcpClientSocket::getClientUser()
{
	return _clientUser;
}



void TcpClientSocket::dataLoginSend()
{
    serverLoginAnswerStruct loginAnswer;
    loginAnswer.sureLogin = m_sureLogin;
    //構造數據包
    qint64 totalBytes = 2*sizeof(qint64) + sizeof(serverLoginAnswerStruct);
    QByteArray outBlock;
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_2);
    outBlock.resize(totalBytes);
    //向緩衝區寫入文件頭
    sendOut<<totalBytes<<qint64(Login_answer);
    mutex.lock();
    memcpy(outBlock.data() + 2*sizeof(qint64),&loginAnswer,sizeof(serverLoginAnswerStruct));
    mutex.unlock();
    write(outBlock);
    outBlock.resize(0);
}

void TcpClientSocket::dataAddGroupSend(QString groupid, QString groupname)
{
    serverAddGroupStruct addGroupData;

    QByteArray id = groupid.toLocal8Bit();
    char *idchar = id.data();
    strcpy(addGroupData.id, idchar);

    QByteArray name = groupname.toLocal8Bit();
    char *namechar = name.data();
    strcpy(addGroupData.name, namechar);
    //構造數據包
    qint64 totalBytes = 2*sizeof(qint64) + sizeof(serverAddGroupStruct);
    QByteArray outBlock;
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_2);
    outBlock.resize(totalBytes);
    //向緩衝區寫入文件頭
    sendOut<<totalBytes<<qint64(AddGroup_answer);
    mutex.lock();
    memcpy(outBlock.data() + 2*sizeof(qint64),&addGroupData,sizeof(serverAddGroupStruct));
    mutex.unlock();
    write(outBlock);
    outBlock.resize(0);
}



void TcpClientSocket::doLogin(QString loginname, QString loginpower)
{
    //回到tcpServer裡面去取得DB裡面有註冊的user
	for(auto temp : _tcpserver->tcpusers())
    {
        //if(temp->name() == loginname && temp->powerpoint() == loginpower)
		if (temp->name() == loginname)
        {
            m_sureLogin = true;
            dataLoginSend();

            _clientUser = new ClientUser(loginname, loginpower);
			
            //
            return;
        }
    }
    m_sureLogin = false;
    dataLoginSend();
}

void TcpClientSocket::flush()
{
    //刷新聊天室
    for(auto temp : _tcpserver->tcpgroups())
    {
        dataAddGroupSend(temp->id(), temp->name());
    }
}


void TcpClientSocket::dataReceived()
{
    qDebug() << "data received()";
    if(bytesAvailable() <= 0)
    {
        return;
    }

    //從緩存區中去除數據，但是不確定取出來的字節數
    QByteArray  buffer;
    buffer = readAll();
    m_buffer.append(buffer);
    unsigned int totalLen = m_buffer.size();
	//這邊確實需要利用長度做while循環，因為有可能一下子讀取到兩條以上的完整記錄，就需要進行循環處理了
	//超過一條完整小於第二條完整記錄時，如果已經達到包頭長度就先把包頭保存下來，整個過程循環往復
    while (totalLen) {
        //與QDataStream綁定，方便操作
        QDataStream  packet(m_buffer);
        packet.setVersion(QDataStream::Qt_5_2);
        //不夠包頭長度的不處理，結束while循環
        if(totalLen < 2*sizeof(qint64))
            break;
        //將包頭讀入了進來按照定義的協議 先讀命令長度，再讀命令的類型
        packet>>totalBytes>>serverCmd;
        //緩存中的內容長度沒有達到命令的長度，那就先結束，等足夠了再來解析
        if(totalLen<totalBytes)
            break;
        //足夠長了就開始解析
        switch(serverCmd)
        {

        case Connet_Success:
        {
            flush();
           
            break;
        }
        case Login:
        {
            qDebug() << "received login";

            loginStruct loginData;
            QByteArray realStateData = m_buffer.mid(2*sizeof(qint64),totalBytes-2*sizeof(qint64));
            motionMutex.lock();
            memcpy(&loginData,realStateData.data(),sizeof(loginStruct));
            motionMutex.unlock();

            QString name = QString::fromLocal8Bit(loginData.name);
            QString power = QString::fromLocal8Bit(loginData.powerpoint);
            doLogin(name, power);

            break;
        }
        case AddGroup:
        {
            addGroupStruct addGroupData;
            QByteArray realStateData = m_buffer.mid(2*sizeof(qint64),totalBytes-2*sizeof(qint64));
            motionMutex.lock();
            memcpy(&addGroupData,realStateData.data(),sizeof(addGroupStruct));
            motionMutex.unlock();

            QString name = QString::fromLocal8Bit(addGroupData.name);
            emit doAddGroup(name);

            break;
        }
      
		case Msg:
        {
            dataChatMsgStruct dataChatData;
            QByteArray realStateData = m_buffer.mid(2*sizeof(qint64),totalBytes-2*sizeof(qint64));
            motionMutex.lock();
            memcpy(&dataChatData,realStateData.data(),sizeof(dataChatMsgStruct));
            motionMutex.unlock();

            QString name = QString::fromLocal8Bit(dataChatData.user_name);
            QString id = QString::fromLocal8Bit(dataChatData.group_id);
            QString msg = QString::fromLocal8Bit(dataChatData.msg);
            emit doSendChatData(name, id, msg);
			qDebug() << name << id << msg;
            break;
        }
		case LoginNotifi:
		{
			dataChatMsgStruct dataChatData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&dataChatData, realStateData.data(), sizeof(dataChatMsgStruct));
			motionMutex.unlock();

			QString name = QString::fromLocal8Bit(dataChatData.user_name);
			//QString id = QString::fromLocal8Bit(dataChatData.group_id);
			//QString msg = QString::fromLocal8Bit(dataChatData.msg);
			emit doSendUserEnter(name);
			//qDebug() << name << id << msg;
			break;
		}
		case UesrInfo:
		{
			dataChatMsgStruct dataChatData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&dataChatData, realStateData.data(), sizeof(dataChatMsgStruct));
			motionMutex.unlock();

			//QString name = QString::fromLocal8Bit(dataChatData.user_name);
			//QString id = QString::fromLocal8Bit(dataChatData.group_id);
			//QString msg = QString::fromLocal8Bit(dataChatData.msg);
			emit doSendRefreshUserInfo();
			//qDebug() << name << id << msg;
			break;
		}

		case FileName:
		{
			dataFileNameStruct dataFileNameData;
			QByteArray realStateData = m_buffer.mid(2 * sizeof(qint64), totalBytes - 2 * sizeof(qint64));
			motionMutex.lock();
			memcpy(&dataFileNameData, realStateData.data(), sizeof(dataFileNameStruct));
			motionMutex.unlock();

			QString serverAddr = QString::fromLocal8Bit(dataFileNameData.serverAddr);
			QString clientAddr = QString::fromLocal8Bit(dataFileNameData.clientAddr);
			QString fileName = QString::fromLocal8Bit(dataFileNameData.fileName);
			emit doSendFileNameData(serverAddr, clientAddr, fileName);
			//qDebug() << name << id << msg;
			break;
		}
        }
        //缓存多余的数据
        buffer = m_buffer.right(totalLen - totalBytes); //截取下一个数据包的数据，留作下次读取
        totalLen = buffer.size();
        //更新多余的数据
        m_buffer = buffer;
    }
}

void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
