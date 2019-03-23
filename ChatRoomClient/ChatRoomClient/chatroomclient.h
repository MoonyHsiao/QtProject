#ifndef CHATROOMCLIENT_H
#define CHATROOMCLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_chatroomclient.h"
#include <QtNetwork/QTcpSocket>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets>
#include "client.h"
#include "chatCMD.h"
#include "FileServer.h"
#include "FileClient.h"
//enum MsgType { Msg, UsrEnter, UsrLeft, FileName, Refuse };
class ChatRoomClient : public QMainWindow
{
	Q_OBJECT

public:
	ChatRoomClient(QWidget *parent = 0);
	~ChatRoomClient();
	QTcpSocket *m_socket;
	QString userRunLocat = "";
	QString m_userName = "user";
	
	QStackedWidget *settingStackedWidget;
	QLineEdit *leLogInAcc;
	QLineEdit *leServer;
	QLabel *lblIPTitle;
	QLabel *lblLoginTitle;
	QPushButton *btnLoginLogin;
	QComboBox *sizeCbx;
	QToolButton *boldTBtn;
	QToolButton *italicTBtn;
	QToolButton *sendTBtn;
	QToolButton *saveTBtn;
	QToolButton *clearTBtn;
	QPushButton *SendBtn;
	QTextEdit *msgTxtEdit;
	QTableWidget *usrTblWidget;
	QLabel *usrNumLbl;
	QTextBrowser *msgBrowser;
	QFontComboBox* fontCbx;
	QColor color;
	Client *aaa;
	void sndMsg(qint64 type, QString srvaddr = "");
	bool saveFile(const QString& filename);
public slots:
	void slotConnected();
	void slotDisConnected();
	void slotLoginAnswer(bool state);
	void loginFrameEvent();
	void on_sendBtn_clicked();
	void curFmtChanged(const QTextCharFormat &fmt);
	void on_fontCbx_currentFontChanged(const QFont &f);
	void on_sizeCbx_currentIndexChanged(const QString &arg1);
	void on_boldTBtn_clicked(bool checked);
	void on_italicTBtn_clicked(bool checked);
	void on_sendTBtn_clicked(bool checked);
	void on_saveTBtn_clicked(bool checked);
	void on_clearTBtn_clicked(bool checked);
	void getFileName(QString);
	void slotMsg(QString user_name, QString group_id, QString msg);
	void slotUserEnterRoom(QString user_name);
	void slotRefreshUserInfo(QString user_name, QString powerpoint);
	void slotLeftRefreshUserInfo(QString user_name, QString powerpoint);

	void slotDownLoad(QString serverAdd, QString clientAdd, QString file);
private:
	Ui::ChatRoomClientClass ui;
	QString fileName;
	QString getIP();
	QString serverAddress;
	FileServer *srv;
};

#endif // CHATROOMCLIENT_H
