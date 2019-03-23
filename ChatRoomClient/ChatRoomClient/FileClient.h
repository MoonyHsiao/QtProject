#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QTime>
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class FileClient : public QDialog
{
	Q_OBJECT

public:
	explicit FileClient(QWidget *parent = 0);
	~FileClient();

	void setHostAddr(QHostAddress addr);
	void setFileName(QString name);

protected:
	void closeEvent(QCloseEvent *);
private:
	QPushButton *CancleBtn;
	QPushButton *CloseBtn;
	QProgressBar *myProgressBar;
	QTcpSocket *tClnt;
	quint16 blockSize;
	QHostAddress hostAddr;
	qint16 tPort;
	QLabel *StatusLbl;
	qint64 totalBytes;
	qint64 bytesReceived;
	qint64 fileNameSize;
	QString fileName;
	QFile *locFile;
	QByteArray inBlock;

	QTime time;

	private slots:

	void newConn();
	void readMsg();
	void displayErr(QAbstractSocket::SocketError);
	void on_cCancleBtn_clicked();
	void on_cCloseBtn_clicked();
};
#endif // CLIENT_H