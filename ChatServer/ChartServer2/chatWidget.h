#ifndef CHATWIDGET_H
#define CHATWIDGET_H


#include <QWidget>
#include <QTextCharFormat>
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include "server.h"
#include "client.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QFont>
#include <QLabel>
#include <QComboBox>
#include <QToolButton>
#include <QTableWidget>
#include <QTableWidgetItem>

class QUdpSocket;

class Server;


enum MsgType{Msg, UsrEnter, UsrLeft, FileName, Refuse};

class chatWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit chatWidget(QWidget *parent,QString usrname);
    ~chatWidget();
protected:
    void usrEnter(QString usrname,QString ipaddr);
    void usrLeft(QString usrname,QString time);
    void sndMsg(MsgType type, QString srvaddr="");

    QString getIP();
    QString getUsr();
    QString getMsg();

    void hasPendingFile(QString usrname, QString srvaddr,QString clntaddr, QString filename);

    bool saveFile(const QString& filename);

    void closeEvent(QCloseEvent *);

private:
    QUdpSocket *udpSocket;
    qint16 port;
    QString uName;
	QTextBrowser *msgBrowser;
    QString fileName;
    Server *srv;
	QFontComboBox* fontCbx;
    QColor color;
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
private slots:
    void processPendingDatagrams();
    void on_sendBtn_clicked();

    void getFileName(QString);
   
    void on_fontCbx_currentFontChanged(const QFont &f);
    void on_sizeCbx_currentIndexChanged(const QString &arg1);
    void on_boldTBtn_clicked(bool checked);
    void on_italicTBtn_clicked(bool checked);
    void on_underlineTBtn_clicked(bool checked);
    void on_colorTBtn_clicked();

    void curFmtChanged(const QTextCharFormat &fmt);
    void on_saveTBtn_clicked(bool checked);
    void on_clearTBtn_clicked(bool checked);
    void on_exitBtn_clicked(bool checked);

	void on_sendTBtn_clicked(bool checked);
};

#endif // WIDGET_H
