#include "FileServer.h"



FileServer::FileServer(QWidget *parent) :
	QDialog(parent)
{
	setFixedSize(400, 207);

	tPort = 5555;
	tSrv = new QTcpServer(this);
	connect(tSrv, SIGNAL(newConnection()), this, SLOT(sndMsg()));


	OpenBtn = new QPushButton("OpenFile",this);
	OpenBtn->setObjectName("down");
	OpenBtn->setGeometry(0, 150, 100, 20);
	connect(OpenBtn, SIGNAL(clicked()), this, SLOT(on_sOpenBtn_clicked()));

	SendBtn = new QPushButton("Send", this);
	SendBtn->setObjectName("down");
	SendBtn->setGeometry(120, 150, 100, 20);
	connect(SendBtn, SIGNAL(clicked()), this, SLOT(on_sSendBtn_clicked()));


	CancleBtn = new QPushButton("Cancle", this);
	CancleBtn->setObjectName("down");
	CancleBtn->setGeometry(0, 180, 100, 20);
	connect(CancleBtn, SIGNAL(clicked()), this, SLOT(on_cCancleBtn_clicked()));


	CloseBtn = new QPushButton("Close", this);
	CloseBtn->setObjectName("down");
	CloseBtn->setGeometry(120, 180, 100, 20);
	connect(CloseBtn, SIGNAL(clicked()), this, SLOT(on_sCloseBtn_clicked()));

	myProgressBar = new QProgressBar(this);
	myProgressBar->setGeometry(10, 30, 210, 30); //設定位置大小

	StatusLbl = new QLabel(tr("Hub"), this);
	StatusLbl->setObjectName("title");
	StatusLbl->setGeometry(10, 60, 210, 20);
	StatusLbl->setAlignment(Qt::AlignCenter);

	initSrv();
}

FileServer::~FileServer()
{

}

void FileServer::initSrv()
{
	payloadSize = 64 * 1024;
	totalBytes = 0;
	bytesWritten = 0;
	bytesTobeWrite = 0;

	StatusLbl->setText(tr("Please select the file to transfer"));
	myProgressBar->reset();
	OpenBtn->setEnabled(true);
	SendBtn->setEnabled(false);

	tSrv->close();
}

void FileServer::sndMsg()
{
	SendBtn->setEnabled(false);
	clntConn = tSrv->nextPendingConnection();
	connect(clntConn, SIGNAL(bytesWritten(qint64)), this, SLOT(updClntProgress(qint64)));

	StatusLbl->setText(tr("Start transferring files %1!").arg(theFileName));

	locFile = new QFile(fileName);
	if (!locFile->open((QFile::ReadOnly))) {
		QMessageBox::warning(this, tr("application"), tr("Unable to read file %1:\n%2").arg(fileName).arg(locFile->errorString()));
		return;
	}
	totalBytes = locFile->size();
	QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_7);
	time.start();  
	QString curFile = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
	sendOut << qint64(0) << qint64(0) << curFile;
	totalBytes += outBlock.size();
	sendOut.device()->seek(0);
	sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));
	bytesTobeWrite = totalBytes - clntConn->write(outBlock);
	outBlock.resize(0);
}

void FileServer::updClntProgress(qint64 numBytes)
{
	qApp->processEvents();

	bytesWritten += (int)numBytes;
	if (bytesTobeWrite > 0) {
		outBlock = locFile->read(qMin(bytesTobeWrite, payloadSize));
		bytesTobeWrite -= (int)clntConn->write(outBlock);
		outBlock.resize(0);
	}
	else {
		locFile->close();
	}
	myProgressBar->setMaximum(totalBytes);
	myProgressBar->setValue(bytesWritten);

	float useTime = time.elapsed();
	double speed = bytesWritten / useTime;
	StatusLbl->setText(tr("Has been sent %1MB (%2MB/s) \n Total%3MB Used time:%4second\n Estimated time remaining:%5second")
		.arg(bytesWritten / (1024 * 1024))
		.arg(speed * 1000 / (1024 * 1024), 0, 'f', 2)
		.arg(totalBytes / (1024 * 1024))
		.arg(useTime / 1000, 0, 'f', 0)
		.arg(totalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));

	if (bytesWritten == totalBytes) {
		locFile->close();
		tSrv->close();
		StatusLbl->setText(tr("transfer files %1 success").arg(theFileName));
	}
}
void FileServer::on_sOpenBtn_clicked()
{
	fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty())
	{
		theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
		StatusLbl->setText(tr("The file to be transferred is:%1 ").arg(theFileName));
		SendBtn->setEnabled(true);
		OpenBtn->setEnabled(false);
	}
}

void FileServer::on_sSendBtn_clicked()
{
	if (!tSrv->listen(QHostAddress::Any, tPort))//開始監聽
	{
		qDebug() << tSrv->errorString();
		close();
		return;
	}

	StatusLbl->setText(tr("Waiting for the other party to receive..."));
	emit sndFileName(theFileName);
}

void FileServer::on_cCancleBtn_clicked()
{
	if (tSrv->isListening())
	{
		tSrv->close();
		if (locFile->isOpen())
			locFile->close();
		clntConn->abort();
	}
	close();
}

void FileServer::on_sCloseBtn_clicked()
{
	if (tSrv->isListening())
	{
		tSrv->close();
		if (locFile->isOpen())
			locFile->close();
		clntConn->abort();
	}
	close();
}

void FileServer::refused()
{
	tSrv->close();
	StatusLbl->setText(tr("The other party refuses to accept!"));
}

void FileServer::closeEvent(QCloseEvent *)
{
	on_sCloseBtn_clicked();
}
