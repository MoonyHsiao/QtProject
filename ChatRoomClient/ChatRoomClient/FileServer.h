#pragma once
#ifndef FILESERVER_H
#define FILESERVER_H

#include <QDialog>
#include <QTime>
#include <QProgressBar>
#include <QLabel>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QApplication>
class QFile;
class QTcpServer;
class QTcpSocket;

class FileServer : public QDialog
{
	Q_OBJECT

public:
	explicit FileServer(QWidget *parent = 0);
	~FileServer();

	void initSrv();
	void refused();
protected:
	void closeEvent(QCloseEvent *);
private:
	QPushButton *CancleBtn;
	QPushButton *CloseBtn;
	QPushButton *OpenBtn;
	QPushButton *SendBtn;
	QProgressBar *myProgressBar;
	QLabel *StatusLbl;
	qint16 tPort;
	QTcpServer *tSrv;
	QString fileName;
	QString theFileName;
	QFile *locFile;
	qint64 totalBytes;
	qint64 bytesWritten;
	qint64 bytesTobeWrite;
	qint64 payloadSize;
	QByteArray outBlock;

	QTcpSocket *clntConn;

	QTime time;

	private slots:
	void sndMsg();
	void updClntProgress(qint64 numBytes);
	void on_sOpenBtn_clicked();

	void on_sSendBtn_clicked();
	void on_cCancleBtn_clicked();
	void on_sCloseBtn_clicked();

signals:
	void sndFileName(QString fileName);
};

#endif // SERVER_H
