#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <vector>
#include <QMutex>
#include "clientuser.h"
class TcpClientSocket;
class TcpUser;
class TcpGroup;
class ClientUser;
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent=0,quint16 port=8010);
    //傳回客戶端的結構體
    struct serverAddGroupStruct
    {
        char id[1024];
        char name[1024];
    };
    struct serverMsgStruct
    {
        char user_name[1024];
        char group_id[1024];
        char msg_data[1024];
    };

	struct loginStruct
	{
		char name[1024];
		char powerpoint[1024];
		//改成ip吧
	};

	struct dataFileNameStruct
	{
		char serverAddr[1024];
		char clientAddr[1024];
		char fileName[1024];
	};
    //送msg给客戶端
	//void dataMsgSend(QString username, QString msg, QString groupid);
    //廣播addgroup给客戶端
    void dataAddGroupSend(QString groupid, QString groupname);   
    std::vector<TcpUser*> tcpusers();
    std::vector<TcpGroup*> tcpgroups();
	//當出現一個新的連接
    void incomingConnection(qintptr socketDescriptor);
public slots:
	//接收斷開連接的信息
	void slotDisconnection(qintptr);
    //接受要廣播的聊天信息
    void updateMsgClients(QString username, QString groupid, QString msg);
	//添加房間到DB並發送給客戶端
    void doAddGroup(QString groupname);  
	void doUpdateUserEnter(QString username);
	void doRefreshUserInfo();
	void doLeftRefreshUserInfo(QString leftUserName);
	void updateFileNameClients(QString serverAddr, QString clientAddr, QString fileName);
signals:
	void sentPeople(int);
private:
    QSqlDatabase db;
    QList<TcpClientSocket*> tcpClientSocketList;
    std::vector<TcpUser*> _tcpusers;
    std::vector<TcpGroup*> _tcpgroups;
    void connectDatabase();
	void createDatabase();
    QMutex mutex;
    QMutex motionMutex;
	QByteArray m_buffer; //緩存上一次或多次的未處理的數據
	qint64 totalBytes; //一個數據包MSG部分的完整大小
	qint64 recvdBytes; //已經收到的字節數
	qint64 serverCmd; //接受數據包的類型
	QByteArray inBlock; //接受緩衝
	
protected:

};

#endif // TCPSERVER_H
