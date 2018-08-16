#include "chatWidget.h"
#pragma execution_character_set("utf-8")
chatWidget::chatWidget(QWidget *parent, QString usrname) :
	QWidget(parent)
{
	/*========server模擬===========
	
	server = new QTcpServer(this);
	connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
	//qDebug() << "Listening:" << server->listen(QHostAddress::Any, 5489);
	server->listen(QHostAddress::Any, 5488);
	//qDebug() << "Listening:" << server->listen(QHostAddress::Any, 5488);
	//-----------------------------------------------end-----------------------------------------------------------//

	//isOpenPassword = false;
	//passwordString = "0000";

	connectCount = 0;
	
	*/


	/*========手機端模擬===========
	m_socket = new QTcpSocket(this);
	setWindowTitle("手機端模擬");
	userRunLocat = QApplication::applicationDirPath() + "/"; //取得使用者跑這隻程式的位置
	//Connect事件觸發的Function
	//在收到Server的訊息時會觸發readRead()
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	//連線成功的事件
	connect(m_socket, SIGNAL(connected()), this, SLOT(slotConnected()));
	//斷線的事件
	connect(m_socket, SIGNAL(disconnected()), this, SLOT(slotDisConnected()));

	//連線到Server
	QString ip_address = "127.0.0.1";
	int port = 5488;
	m_socket->connectToHost(ip_address, port);
	*/

	this->resize(1000, 550);
	uName = usrname;
	udpSocket = new QUdpSocket(this);
	port = 23232;
	udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	//udpSocket->bind(QHostAddress("192.168.3.168"), port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
	
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
	sndMsg(UsrEnter);

	srv = new Server(this);
	connect(srv, SIGNAL(sndFileName(QString)), this, SLOT(getFileName(QString)));


	usrTblWidget = new QTableWidget(this);
	usrTblWidget->setGeometry(0, 0, 250, 300);
	usrTblWidget->setColumnCount(2);
	usrTblWidget->setWindowTitle("QTableWidget & Item");

	QStringList header;
	header << "user name" << "IP address";
	usrTblWidget->setHorizontalHeaderLabels(header);


	msgBrowser = new QTextBrowser(this);
	msgBrowser->setGeometry(260, 0, 300, 300);

	int messageY = 320;

	msgTxtEdit = new QTextEdit(this);
	msgTxtEdit->setGeometry(0, messageY, 200, 20);
	msgTxtEdit->setAlignment(Qt::AlignTop);
	msgTxtEdit->setFrameShape(QFrame::NoFrame);
	msgTxtEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	msgTxtEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	msgTxtEdit->setLineWrapMode(QTextEdit::WidgetWidth);
	msgTxtEdit->show();
	connect(msgTxtEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(curFmtChanged(const QTextCharFormat)));


	SendBtn = new QPushButton("SendBtn", this);
	SendBtn->setObjectName("down");
	SendBtn->setGeometry(210, messageY, 100, 20);
	connect(SendBtn, SIGNAL(clicked()), this, SLOT(on_sendBtn_clicked()));


	fontCbx = new QFontComboBox(this);
	fontCbx->setGeometry(320, messageY, 100, 20);
	connect(fontCbx, SIGNAL(currentFontChanged(QFont)), this, SLOT(on_fontCbx_currentFontChanged(QFont)));

	sizeCbx = new QComboBox(this);
	sizeCbx->setGeometry(430, messageY, 40, 20);  //設定位置大小
	sizeCbx->insertItem(0, tr("10"));
	sizeCbx->insertItem(1, tr("12"));
	sizeCbx->insertItem(2, tr("14"));
	sizeCbx->insertItem(3, tr("16"));
	connect(sizeCbx, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sizeCbx_currentIndexChanged(int)));

	boldTBtn = new QToolButton(this);
	boldTBtn->setGeometry(480, messageY, 20, 20);
	boldTBtn->setToolTip("boldTBtn");
	boldTBtn->setCheckable(true);
	boldTBtn->setStyleSheet("QToolButton{border-image: url(Image/bold.png);}");
	connect(boldTBtn, SIGNAL(toggled(bool)), this, SLOT(on_boldTBtn_clicked(bool)));

	italicTBtn = new QToolButton(this);
	italicTBtn->setGeometry(510, messageY, 20, 20);
	italicTBtn->setToolTip("italicTBtn");
	italicTBtn->setCheckable(true);
	italicTBtn->setStyleSheet("QToolButton{border-image: url(Image/italic.png);}");
	connect(italicTBtn, SIGNAL(toggled(bool)), this, SLOT(on_italicTBtn_clicked(bool)));

	sendTBtn = new QToolButton(this);
	sendTBtn->setGeometry(540, messageY, 20, 20);
	sendTBtn->setToolTip("sendTBtn");
	sendTBtn->setCheckable(true);
	sendTBtn->setStyleSheet("QToolButton{border-image: url(Image/send.png);}");
	connect(sendTBtn, SIGNAL(toggled(bool)), this, SLOT(on_sendTBtn_clicked(bool)));

	saveTBtn = new QToolButton(this);
	saveTBtn->setGeometry(570, messageY, 20, 20);
	saveTBtn->setToolTip("saveTBtn");
	saveTBtn->setCheckable(true);
	saveTBtn->setStyleSheet("QToolButton{border-image: url(Image/save.png);}");
	connect(saveTBtn, SIGNAL(toggled(bool)), this, SLOT(on_saveTBtn_clicked(bool)));

	clearTBtn = new QToolButton(this);
	clearTBtn->setToolTip("clearTBtn");
	clearTBtn->setGeometry(600, messageY, 20, 20);
	clearTBtn->setCheckable(true);
	clearTBtn->setStyleSheet("QToolButton{border-image: url(Image/clear.png);}");
	connect(clearTBtn, SIGNAL(toggled(bool)), this, SLOT(on_clearTBtn_clicked(bool)));

	usrNumLbl = new QLabel(tr("Hub"), this);
	usrNumLbl->setObjectName("title");
	usrNumLbl->setGeometry(580, 10, 80, 20);
	usrNumLbl->setAlignment(Qt::AlignCenter);

}

chatWidget::~chatWidget()
{

}

void chatWidget::sndMsg(MsgType type, QString srvaddr)
{
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	QString address = getIP();
	out << type << getUsr();

	switch (type)
	{
	case Msg:
		if (msgTxtEdit->toPlainText() == "") {
			QMessageBox::warning(0, tr("warning"), tr("Sending content cannot be empty"), QMessageBox::Ok);
			return;
		}
		out << address << getMsg();
		msgBrowser->verticalScrollBar()->setValue(msgBrowser->verticalScrollBar()->maximum());
		break;

	case UsrEnter:
		out << address;
		break;

	case UsrLeft:
		break;

	case FileName: {
		int row = usrTblWidget->currentRow();
		QString clntaddr = usrTblWidget->item(row, 1)->text();
		out << address << clntaddr << fileName;
		break;
	}

	case Refuse:
		out << srvaddr;
		break;
	}
	udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

void chatWidget::processPendingDatagrams()
{
	while (udpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size());
		QDataStream in(&datagram, QIODevice::ReadOnly);
		int msgType;
		in >> msgType;
		QString usrName, ipAddr, msg;
		QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

		switch (msgType)
		{
		case Msg:
			in >> usrName >> ipAddr >> msg;
			//if (usrName != uName) {
				msgBrowser->setTextColor(Qt::blue);
				msgBrowser->setCurrentFont(QFont("Times New Roman", 12));
				msgBrowser->append("[ " + usrName + " ] " + time);
				msgBrowser->append(msg);
			//}
			break;

		case UsrEnter:
			in >> usrName >> ipAddr;
			usrEnter(usrName, ipAddr);
			break;

		case UsrLeft:
			in >> usrName;
			usrLeft(usrName, time);
			break;

		case FileName: {
			in >> usrName >> ipAddr;
			QString clntAddr, fileName;
			in >> clntAddr >> fileName;
			hasPendingFile(usrName, ipAddr, clntAddr, fileName);
			break;
		}

		case Refuse: {
			in >> usrName;
			QString srvAddr;
			in >> srvAddr;
			QString ipAddr = getIP();

			if (ipAddr == srvAddr)
			{
				srv->refused();
			}
			break;
			}
		}
	}
}

void chatWidget::usrEnter(QString usrname, QString ipaddr)
{
	bool isEmpty = usrTblWidget->findItems(usrname, Qt::MatchExactly).isEmpty();
	if (isEmpty) {
		QTableWidgetItem *usr = new QTableWidgetItem(usrname);
		QTableWidgetItem *ip = new QTableWidgetItem(ipaddr);

		usrTblWidget->insertRow(0);
		usrTblWidget->setItem(0, 0, usr);
		usrTblWidget->setItem(0, 1, ip);
		msgBrowser->setTextColor(Qt::gray);
		msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
		msgBrowser->append(tr("%1 Online!").arg(usrname));
		//qDebug() <<"usrTblWidget->rowCount():" << usrTblWidget->rowCount();
		usrNumLbl->setText(tr("online users:%1").arg(usrTblWidget->rowCount()));

		sndMsg(UsrEnter);
	}
}

void chatWidget::usrLeft(QString usrname, QString time)
{
	int rowNum = usrTblWidget->findItems(usrname, Qt::MatchExactly).first()->row();
	usrTblWidget->removeRow(rowNum);
	msgBrowser->setTextColor(Qt::gray);
	msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
	msgBrowser->append(tr("%1 to %2 leave!").arg(usrname).arg(time));
	usrNumLbl->setText(tr("online users:%1").arg(usrTblWidget->rowCount()));
}

QString chatWidget::getIP()
{
	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress addr, list) {
		if (addr.protocol() == QAbstractSocket::IPv4Protocol)
			return addr.toString();
	}
	return 0;
}

QString chatWidget::getUsr()
{
	return uName;
}

QString chatWidget::getMsg()
{
	QString msg = msgTxtEdit->toHtml();

	msgTxtEdit->clear();
	msgTxtEdit->setFocus();
	return msg;
}

void chatWidget::on_sendBtn_clicked()
{
	sndMsg(Msg);
}

void chatWidget::getFileName(QString name)
{
	fileName = name;
	sndMsg(FileName);
}

void chatWidget::hasPendingFile(QString usrname, QString srvaddr, QString clntaddr, QString filename)
{
	QString ipAddr = getIP();
	if (ipAddr == clntaddr)
	{
		int btn = QMessageBox::information(this, tr("Accept file"), tr("File from %1 (%2): %3, is it received?").arg(usrname).arg(srvaddr).arg(filename), QMessageBox::Yes, QMessageBox::No);
		if (btn == QMessageBox::Yes) {
			QString name = QFileDialog::getSaveFileName(0, tr("save document"), filename);
			if (!name.isEmpty())
			{
				Client *clnt = new Client(this);
				clnt->setFileName(name);
				clnt->setHostAddr(QHostAddress(srvaddr));
				clnt->show();
			}
		}

		else {
			sndMsg(Refuse, srvaddr);
		}
	}
}

void chatWidget::on_fontCbx_currentFontChanged(const QFont &f)
{
	msgTxtEdit->setCurrentFont(f);
	msgTxtEdit->setFocus();
}

void chatWidget::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
	msgTxtEdit->setFontPointSize(arg1.toDouble());
	msgTxtEdit->setFocus();
}

void chatWidget::on_boldTBtn_clicked(bool checked)
{
	if (checked)
		msgTxtEdit->setFontWeight(QFont::Bold);
	else
		msgTxtEdit->setFontWeight(QFont::Normal);
	msgTxtEdit->setFocus();
}

void chatWidget::on_italicTBtn_clicked(bool checked)
{
	msgTxtEdit->setFontItalic(checked);
	msgTxtEdit->setFocus();
}

void chatWidget::on_underlineTBtn_clicked(bool checked)
{
	msgTxtEdit->setFontUnderline(checked);
	msgTxtEdit->setFocus();
}

void chatWidget::on_colorTBtn_clicked()
{
	color = QColorDialog::getColor(color, this);
	if (color.isValid()) {
		msgTxtEdit->setTextColor(color);
		msgTxtEdit->setFocus();
	}
}

void chatWidget::curFmtChanged(const QTextCharFormat &fmt)
{
	fontCbx->setCurrentFont(fmt.font());

	if (fmt.fontPointSize() < 8) {
		sizeCbx->setCurrentIndex(4);
	}
	else {
		sizeCbx->setCurrentIndex(sizeCbx->findText(QString::number(fmt.fontPointSize())));
	}
	boldTBtn->setChecked(fmt.font().bold());
	//ui->italicTBtn->setChecked(fmt.font().italic());
	//ui->underlineTBtn->setChecked(fmt.font().underline());
	color = fmt.foreground().color();
}

void chatWidget::on_saveTBtn_clicked(bool checked)
{
	if (msgBrowser->document()->isEmpty()) {
		QMessageBox::warning(0, tr("warning"), tr("Chat history is empty and cannot be saved!"), QMessageBox::Ok);
	}
	else {
		QString fname = QFileDialog::getSaveFileName(this, tr("Save chat history"), tr("chat history"), tr("file(*.txt);;All files(*.*)"));
		if (!fname.isEmpty())
			saveFile(fname);
	}
}

bool chatWidget::saveFile(const QString &filename)
{
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("save document"), tr("Unable to save file %1:\n %2").arg(filename).arg(file.errorString()));
		return false;
	}
	QTextStream out(&file);
	out << msgBrowser->toPlainText();

	return true;
}

void chatWidget::on_clearTBtn_clicked(bool checked)
{
	msgBrowser->clear();
}

void chatWidget::on_exitBtn_clicked(bool checked)
{
	close();
}

void chatWidget::on_sendTBtn_clicked(bool checked)
{
	if (usrTblWidget->selectedItems().isEmpty())
	{
		QMessageBox::warning(0, tr("Select user"), tr("Please select the target user first!"), QMessageBox::Ok);
		return;
	}
	srv->show();
	srv->initSrv();
}

void chatWidget::closeEvent(QCloseEvent *e)
{
	sndMsg(UsrLeft);
	QWidget::closeEvent(e);
}
