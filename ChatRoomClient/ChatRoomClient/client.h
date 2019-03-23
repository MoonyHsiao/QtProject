
#ifndef CLIENT_H
#define CLIENT_H
#include <QHostAddress>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QMutex>
#include <QNetworkInterface>
class Client : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
		Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
		Q_PROPERTY(QString userPower READ userPower WRITE setUserPower NOTIFY userPowerChanged)
		Q_PROPERTY(QString groupId READ groupId WRITE setGroupId NOTIFY groupIdChanged)
		Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
		//https://www.twblogs.net/a/5bddab932b717720b51aa48b
public:

	//Client(QObject *parent = 0);
	Client(QObject *parent, int _port, QString _serverIP);
	QString userId() const;
	void setUserId(const QString &userId);

	QString userName() const;
	void setUserName(const QString &userName);

	QString userPower() const;
	void setUserPower(const QString &userPower);

	QString groupId() const;
	void setGroupId(const QString &groupId);

	//Connection server
	void tcpConnected();

	QString groupName() const;
	void setGroupName(const QString &groupName);

	

	//The structure sent by the client

	struct loginStruct
	{
		char name[1024];
		char powerpoint[1024];
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
	struct connectSuccessStruct
	{
		char str[1024];
	};

	struct dataFileNameStruct
	{
		char serverAddr[1024];
		char clientAddr[1024];
		char fileName[1024];
	};
	
	//Structure sent from the server
	
	struct serverLoginAnswerStruct
	{
		bool sureLogin;
	};
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

	

signals:
	void userIdChanged();
	void userNameChanged();
	void userPowerChanged();
	void groupIdChanged();
	void groupNameChanged();
	void registerNameChanged();
	void registerPowerChanged();

	void serverLeft(); //得到登錄的反饋信息
	void getLoginAnswer(bool sureLogin); //得到登錄的反饋信息
	
	void signalAddGroup(QString group_id, QString group_name); //得到添加聊天室的信息
	void signalMsg(QString user_name, QString group_id, QString msg); //得到聊天信息的信息
	void signalUserEnterRoom(QString user_name); //得到聊天信息的信息
	void signalRefreshUserInfo(QString user_name, QString powerpoint); //得到聊天信息的信息
	void signalLeftRefreshUserInfo(QString user_name, QString powerpoint); //得到聊天信息的信息
	void signalAddMood(QString user_name, QString msg); //get add mood's message

	void hasPendingFile(QString serverAdd, QString clientAdd, QString file); //得到聊天信息的信息
public slots:
	void dataReceived(); //收到來自服務器的數據
	void sureConnected();
	void sureDisConnected();
	void dataChatMsgSend(QString groupid, QString username, QString chatmsg);
	void dataChatRoomEnter(QString groupid, QString username, QString chatmsg);
	void dataSendFileName(QString serverAddress, QString clientAddress, QString fileName);
	void dataFileRefuse(QString serverAddress);
	void dataRefreshUserInfo();
	void dataChatMsgSend2();
	void dataLoginSend();
	void dataAddGroupSend(QString group_name);
	void dataConnectSend();
private:
	int m_port = 1127;
	QString m_serverIP = "127.0.0.1";
	QString m_userId;
	QString m_userName;
	QString m_userPower="111";
	QString m_groupId;
	QString m_groupName;
	QString m_registerName;
	QString m_registerPower;

	QHostAddress *serverIP;
	QTcpSocket *tcpSocket;
	QString m_chatMsg;
	QMutex mutex;
	QMutex motionMutex;
	QByteArray m_buffer; //緩存上一次或多次的未處理的數據
	qint64 totalBytes; //一個數據包MSG部分的完整大小
	qint64 recvdBytes; //已經收到的字節數
	qint64 serverCmd; //接受數據包的類型
	QByteArray inBlock; //接受緩衝
	QString getIP();
	//void connected();
};

#endif // CLIENT_H
