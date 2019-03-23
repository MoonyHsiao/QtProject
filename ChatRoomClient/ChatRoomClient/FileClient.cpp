#include "FileClient.h"


FileClient::FileClient(QWidget *parent) :
	QDialog(parent){
	
	setWindowTitle("receive");
	setFixedSize(400, 190);

	totalBytes = 0;
	bytesReceived = 0;
	fileNameSize = 0;

	CancleBtn = new QPushButton("Cancle", this);
	CancleBtn->setObjectName("down");
	CancleBtn->setGeometry(0, 140, 100, 20);
	connect(CancleBtn, SIGNAL(clicked()), this, SLOT(on_cCancleBtn_clicked()));


	CloseBtn = new QPushButton("Close", this);
	CloseBtn->setObjectName("down");
	CloseBtn->setGeometry(120, 140, 100, 20);
	connect(CloseBtn, SIGNAL(clicked()), this, SLOT(on_cCloseBtn_clicked()));


	tClnt = new QTcpSocket(this);
	tPort = 5555;
	connect(tClnt, SIGNAL(readyRead()), this, SLOT(readMsg()));
	connect(tClnt, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayErr(QAbstractSocket::SocketError)));

	myProgressBar = new QProgressBar(this);
	myProgressBar->setGeometry(10, 30, 210, 30); //設定位置大小

	StatusLbl = new QLabel(tr("Hub"), this);
	StatusLbl->setObjectName("title");
	StatusLbl->setGeometry(10, 60, 210, 20);
	StatusLbl->setAlignment(Qt::AlignCenter);
}

FileClient::~FileClient()
{
}

void FileClient::setFileName(QString name)
{
	locFile = new QFile(name);
}

void FileClient::setHostAddr(QHostAddress addr)
{
	hostAddr = addr;
	newConn();
}

void FileClient::newConn()
{
	blockSize = 0;
	tClnt->abort();
	tClnt->connectToHost(hostAddr, tPort);
	time.start();
}

void FileClient::readMsg()
{
	QDataStream in(tClnt);
	//in.setVersion(QDataStream::Qt_4_7);
	in.setVersion(QDataStream::Qt_5_7);

	float useTime = time.elapsed();

	if (bytesReceived <= sizeof(qint64) * 2) {
		if ((tClnt->bytesAvailable() >= sizeof(qint64) * 2) && (fileNameSize == 0))
		{
			in >> totalBytes >> fileNameSize;
			bytesReceived += sizeof(qint64) * 2;
		}
		if ((tClnt->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)) {
			in >> fileName;
			bytesReceived += fileNameSize;

			if (!locFile->open(QFile::WriteOnly)) {
				QMessageBox::warning(this, tr("application"), tr("Unable to read file %1:\n%2.").arg(fileName).arg(locFile->errorString()));
				return;
			}
		}
		else {
			return;
		}
	}
	if (bytesReceived < totalBytes) {
		bytesReceived += tClnt->bytesAvailable();
		inBlock = tClnt->readAll();
		locFile->write(inBlock);
		inBlock.resize(0);
	}
	myProgressBar->setMaximum(totalBytes);
	myProgressBar->setValue(bytesReceived);

	double speed = bytesReceived / useTime;
	StatusLbl->setText(tr("Has been sent %1MB (%2MB/s) \n Total%3MB Used time:%4second\n Estimated time remaining:%5second")
		.arg(bytesReceived / (1024 * 1024))
		.arg(speed * 1000 / (1024 * 1024), 0, 'f', 2)
		.arg(totalBytes / (1024 * 1024))
		.arg(useTime / 1000, 0, 'f', 0)
		.arg(totalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));

	if (bytesReceived == totalBytes)
	{
		locFile->close();
		tClnt->close();
		StatusLbl->setText(tr("transfer files %1 success").arg(fileName));
	}
}

void FileClient::displayErr(QAbstractSocket::SocketError sockErr)
{
	switch (sockErr)
	{
	case QAbstractSocket::RemoteHostClosedError: break;
	default: qDebug() << tClnt->errorString();
	}
}
void FileClient::on_cCancleBtn_clicked()
{
	tClnt->abort();
	if (locFile->isOpen())
		locFile->close();
}

void FileClient::on_cCloseBtn_clicked()
{
	tClnt->abort();
	if (locFile->isOpen())
		locFile->close();
	close();
}

void FileClient::closeEvent(QCloseEvent *)
{
	on_cCloseBtn_clicked();
}
