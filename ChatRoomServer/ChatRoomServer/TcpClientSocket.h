#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QTcpSocket>
#include <QObject>
#include "tcpserver.h"
#include <QMutex>
#include "chatCMD.h"
#pragma execution_character_set("utf-8")
class TcpServer;
class ClientUser;

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:

    TcpClientSocket(QObject *parent=0);
	void linkServer(TcpServer* tcpserver);
	ClientUser *getClientUser();
   
    void dataLoginSend();
//    void dataChatMsgSend();
    void dataAddGroupSend(QString groupid, QString groupname);
    void doLogin(QString loginname, QString loginpower);
    void flush();      //登录后第一次进入主界面刷新
   

    
    struct serverLoginAnswerStruct
    {
        bool sureLogin;
    };

    struct serverAddGroupStruct
    {
        char id[1024];
        char name[1024];
    };
    

    struct loginStruct
    {
        char name[1024];
        char powerpoint[1024];
        //改成ip吧
	};

    struct addGroupStruct
    {
        char name[1024];
    };
  
    struct dataChatMsgStruct
    {
        char user_name[1024];
        char group_id[1024];
        char msg[1024];
    };

	struct dataFileNameStruct
	{
		char serverAddr[1024];
		char clientAddr[1024];
		char fileName[1024];
	};

signals:
    void doAddGroup(QString groupname);
    void doSendChatData(QString username, QString groupid, QString msg);
	void doSendUserEnter(QString username);
	void doSendRefreshUserInfo();
	void doSendFileNameData(QString serverAddr, QString clientAddr, QString fileName);
    void disconnected(qintptr);
private slots:
    void dataReceived();
    void slotDisconnected();
private:
    TcpServer* _tcpserver;
    bool m_sureLogin;   //注册是否成功
    ClientUser* _clientUser;
    QMutex mutex;
    QMutex motionMutex;
    QByteArray m_buffer;    //缓存上一次或多次的未处理的数据
    qint64 totalBytes;      //一个数据包MSG部分的完整大小
    qint64 recvdBytes;      //已经收到的字节数
    qint64 serverCmd;       //接受数据包的类型
    QByteArray inBlock;     //接受缓冲
};

#endif // TCPCLIENTSOCKET_H
