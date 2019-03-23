#include "chatroomclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include<QMessageBox>


ChatRoomClient::ChatRoomClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->resize(500, 500);
	setWindowIcon(QPixmap("Image/message.png"));


	settingStackedWidget = new QStackedWidget(ui.centralWidget);
	settingStackedWidget->setGeometry(0, 0, 1000, 550);
	QString widgetStyleSheet =
		"QWidget#loginFrame"
		"{"
		"background:rgb(250, 250, 0);"
		"}"

		"QWidget#charFrame"
		"{"
		"background: rgb(0, 0, 255);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: 5px;"
		"}"
		;

	QWidget *loginFrame = new QWidget(this);
	//loginFrame->setObjectName(QStringLiteral("loginFrame"));
	loginFrame->setStyleSheet(widgetStyleSheet);
	settingStackedWidget->addWidget(loginFrame);
	loginFrame->show();

	int lineEditPos = 150;

	srv = new FileServer(this);
	connect(srv, SIGNAL(sndFileName(QString)), this, SLOT(getFileName(QString)));

	leLogInAcc = new QLineEdit(loginFrame);
	leLogInAcc->setObjectName(QStringLiteral("leLogInAcc"));
	leLogInAcc->setGeometry(QRect(lineEditPos, 150, 180, 20));

	lblLoginTitle = new QLabel(tr("UserName:"), loginFrame);
	lblLoginTitle->setObjectName(QStringLiteral("lblLoginTitle"));
	lblLoginTitle->setGeometry(QRect(lineEditPos - 120, 150, 120, 20));

	lblIPTitle = new QLabel(tr("ServerIP:"), loginFrame);
	lblIPTitle->setObjectName(QStringLiteral("lblIPTitle"));
	lblIPTitle->setGeometry(QRect(lineEditPos - 120, 120, 120, 20));

	leServer = new QLineEdit(loginFrame);
	leServer->setObjectName(QStringLiteral("leLogInAcc"));
	leServer->setGeometry(QRect(lineEditPos, 120, 180, 20));

	btnLoginLogin = new QPushButton(tr("LOGIN"), loginFrame);
	btnLoginLogin->setObjectName(QStringLiteral("btnLoginLogin"));
	btnLoginLogin->setGeometry(QRect(lineEditPos, 180, 100, 20));
	btnLoginLogin->setCursor(Qt::PointingHandCursor);
	connect(btnLoginLogin, SIGNAL(clicked()), this, SLOT(loginFrameEvent()));

	

	QWidget *charFrame = new QWidget(this);
	//charFrame->setObjectName(QStringLiteral("charFrame"));
	charFrame->setStyleSheet(widgetStyleSheet);
	settingStackedWidget->addWidget(charFrame);
	settingStackedWidget->setCurrentIndex(0);

	usrTblWidget = new QTableWidget(charFrame);
	usrTblWidget->setGeometry(260, 0, 200, 300);
	usrTblWidget->setColumnCount(2);
	usrTblWidget->setWindowTitle("QTableWidget & Item");

	QStringList header;
	header << "user" << "IP address";
	usrTblWidget->setHorizontalHeaderLabels(header);


	msgBrowser = new QTextBrowser(charFrame);
	msgBrowser->setGeometry(0, 0, 250, 300);

	int messageY1 = 350;
	int messageY = 320;

	msgTxtEdit = new QTextEdit(charFrame);
	msgTxtEdit->setGeometry(0, messageY1, 250, 100);
	msgTxtEdit->setAlignment(Qt::AlignTop);
	msgTxtEdit->setFrameShape(QFrame::NoFrame);
	msgTxtEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	msgTxtEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	msgTxtEdit->setLineWrapMode(QTextEdit::WidgetWidth);
	msgTxtEdit->show();
	connect(msgTxtEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(curFmtChanged(const QTextCharFormat)));


	SendBtn = new QPushButton("SendBtn", charFrame);
	SendBtn->setObjectName("down");
	SendBtn->setGeometry(260, messageY1, 100, 100);
	connect(SendBtn, SIGNAL(clicked()), this, SLOT(on_sendBtn_clicked()));


	fontCbx = new QFontComboBox(charFrame);
	fontCbx->setGeometry(320, messageY, 100, 20);
	connect(fontCbx, SIGNAL(currentFontChanged(QFont)), this, SLOT(on_fontCbx_currentFontChanged(QFont)));
	fontCbx->setHidden(true);

	sizeCbx = new QComboBox(charFrame);
	sizeCbx->setGeometry(430, messageY, 40, 20);  //設定位置大小
	sizeCbx->insertItem(0, tr("10"));
	sizeCbx->insertItem(1, tr("12"));
	sizeCbx->insertItem(2, tr("14"));
	sizeCbx->insertItem(3, tr("16"));
	connect(sizeCbx, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sizeCbx_currentIndexChanged(int)));
	sizeCbx->setHidden(true);


	boldTBtn = new QToolButton(charFrame);
	boldTBtn->setGeometry(480, messageY, 20, 20);
	boldTBtn->setToolTip("boldTBtn");
	boldTBtn->setCheckable(true);
	boldTBtn->setStyleSheet("QToolButton{border-image: url(Image/bold.png);}");
	connect(boldTBtn, SIGNAL(toggled(bool)), this, SLOT(on_boldTBtn_clicked(bool)));
	boldTBtn->setHidden(true);

	italicTBtn = new QToolButton(charFrame);
	italicTBtn->setGeometry(510, messageY, 20, 20);
	italicTBtn->setToolTip("italicTBtn");
	italicTBtn->setCheckable(true);
	italicTBtn->setStyleSheet("QToolButton{border-image: url(Image/italic.png);}");
	connect(italicTBtn, SIGNAL(toggled(bool)), this, SLOT(on_italicTBtn_clicked(bool)));
	italicTBtn->setHidden(true);

	sendTBtn = new QToolButton(charFrame);
	sendTBtn->setGeometry(10, messageY, 20, 20);
	sendTBtn->setToolTip("sendTBtn");
	sendTBtn->setCheckable(true);
	sendTBtn->setStyleSheet("QToolButton{border-image: url(Image/send.png);}");
	connect(sendTBtn, SIGNAL(toggled(bool)), this, SLOT(on_sendTBtn_clicked(bool)));

	saveTBtn = new QToolButton(charFrame);
	saveTBtn->setGeometry(570, messageY, 20, 20);
	saveTBtn->setToolTip("saveTBtn");
	saveTBtn->setCheckable(true);
	saveTBtn->setStyleSheet("QToolButton{border-image: url(Image/save.png);}");
	connect(saveTBtn, SIGNAL(toggled(bool)), this, SLOT(on_saveTBtn_clicked(bool)));
	saveTBtn->setHidden(true);

	clearTBtn = new QToolButton(charFrame);
	clearTBtn->setToolTip("clearTBtn");
	clearTBtn->setGeometry(40, messageY, 20, 20);
	clearTBtn->setCheckable(true);
	clearTBtn->setStyleSheet("QToolButton{border-image: url(Image/clear.png);}");
	connect(clearTBtn, SIGNAL(toggled(bool)), this, SLOT(on_clearTBtn_clicked(bool)));

	usrNumLbl = new QLabel(tr("Hub"), charFrame);
	usrNumLbl->setObjectName("title");
	usrNumLbl->setGeometry(70, messageY, 80, 20);
	usrNumLbl->setAlignment(Qt::AlignCenter);
	//settingStackedWidget->setCurrentIndex(1);
}

ChatRoomClient::~ChatRoomClient()
{

}

void ChatRoomClient::slotConnected()
{
	qDebug() << "Connected";
}

void ChatRoomClient::slotDisConnected()
{
	qDebug() << "DisConnected";
	settingStackedWidget->setCurrentIndex(0);
}

void ChatRoomClient::slotLoginAnswer(bool state)
{

	qDebug() << "Login State" << state;
	if (state) {
		setWindowTitle(m_userName);
		settingStackedWidget->setCurrentIndex(1);
		sndMsg(LoginNotifi);
		sndMsg(UesrInfo);
	}

}

void ChatRoomClient::loginFrameEvent()
{
	if (leServer->text() != "") {
		aaa = new Client(this, 8010, leServer->text());
		connect(aaa, SIGNAL(getLoginAnswer(bool)), this, SLOT(slotLoginAnswer(bool)));
		connect(aaa, SIGNAL(serverLeft()), this, SLOT(slotDisConnected()));
		connect(aaa, SIGNAL(signalMsg(QString, QString, QString)), this, SLOT(slotMsg(QString, QString, QString)));
		connect(aaa, SIGNAL(signalUserEnterRoom(QString)), this, SLOT(slotUserEnterRoom(QString)));
		connect(aaa, SIGNAL(signalRefreshUserInfo(QString, QString)), this, SLOT(slotRefreshUserInfo(QString, QString)));
		connect(aaa, SIGNAL(signalLeftRefreshUserInfo(QString, QString)), this, SLOT(slotLeftRefreshUserInfo(QString, QString)));
		connect(aaa, SIGNAL(hasPendingFile(QString, QString, QString)), this, SLOT(slotDownLoad(QString, QString, QString)));
		m_userName = leLogInAcc->text();
		aaa->setUserName(m_userName);
		sndMsg(Login);
	}
	else {
		QMessageBox::warning(0, tr("warning"), tr("server ip can't be empty"), QMessageBox::Ok);
	
	}
}


void ChatRoomClient::curFmtChanged(const QTextCharFormat &fmt)
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

void ChatRoomClient::on_sendBtn_clicked()
{
	sndMsg(Msg);
}

void ChatRoomClient::sndMsg(qint64 type, QString srvaddr)
{
	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	QString address = "nouse";
	//out << type << getUsr();


	switch (type)
	{
	case Msg:
		if (msgTxtEdit->toPlainText() == "") {
			QMessageBox::warning(0, tr("warning"), tr("Sending content cannot be empty"), QMessageBox::Ok);
			return;
		}
		//out << address << getMsg();
		aaa->dataChatMsgSend("123", m_userName, msgTxtEdit->toPlainText());
		msgBrowser->verticalScrollBar()->setValue(msgBrowser->verticalScrollBar()->maximum());
		break;

	case Login:
		//out << address;
		aaa->dataLoginSend();
		break;

	case Left:
		break;

	case FileName: {
		int row = usrTblWidget->currentRow();
		QString clntaddr = usrTblWidget->item(row, 1)->text();
		QString serAddr = getIP();
		//out << address << clntaddr << fileName;
		aaa->dataSendFileName(serAddr, clntaddr, fileName);
		break;
	}

	case Refuse:
		//out << srvaddr;
		aaa->dataFileRefuse(srvaddr);
		break;

	case LoginNotifi:
		//out << srvaddr;
		aaa->dataChatRoomEnter("123", m_userName, msgTxtEdit->toPlainText());
		break;

	case UesrInfo:
		aaa->dataRefreshUserInfo();
		break;
	}

	//udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}


void ChatRoomClient::on_fontCbx_currentFontChanged(const QFont &f)
{
	msgTxtEdit->setCurrentFont(f);
	msgTxtEdit->setFocus();
}

void ChatRoomClient::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
	msgTxtEdit->setFontPointSize(arg1.toDouble());
	msgTxtEdit->setFocus();
}

void ChatRoomClient::on_boldTBtn_clicked(bool checked)
{
	if (checked)
		msgTxtEdit->setFontWeight(QFont::Bold);
	else
		msgTxtEdit->setFontWeight(QFont::Normal);
	msgTxtEdit->setFocus();
}

void ChatRoomClient::on_italicTBtn_clicked(bool checked)
{
	msgTxtEdit->setFontItalic(checked);
	msgTxtEdit->setFocus();
}

void ChatRoomClient::on_sendTBtn_clicked(bool checked)
{
	if (usrTblWidget->selectedItems().isEmpty())
	{
		QMessageBox::warning(0, tr("Select user"), tr("Please select the target user first!"), QMessageBox::Ok);
		return;
	}
	srv->show();
	srv->initSrv();
}

void ChatRoomClient::on_saveTBtn_clicked(bool checked)
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
bool ChatRoomClient::saveFile(const QString &filename)
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

void ChatRoomClient::on_clearTBtn_clicked(bool checked)
{
	msgBrowser->clear();
}

void ChatRoomClient::slotMsg(QString user_name, QString group_id, QString msg)
{
	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	msgBrowser->setTextColor(Qt::blue);
	msgBrowser->setCurrentFont(QFont("Times New Roman", 12));
	msgBrowser->append("[ " + user_name + " ] " + time);
	msgBrowser->append(msg);
}

void ChatRoomClient::slotUserEnterRoom(QString user_name)
{
	msgBrowser->append("[ " + user_name + " ] " + "Online!");
}

void ChatRoomClient::slotRefreshUserInfo(QString user_name, QString powerpoint)
{

	bool isEmpty = usrTblWidget->findItems(user_name, Qt::MatchExactly).isEmpty();
	if (isEmpty) {
		QTableWidgetItem *usr = new QTableWidgetItem(user_name);
		QTableWidgetItem *ip = new QTableWidgetItem(powerpoint);

		usrTblWidget->insertRow(0);
		usrTblWidget->setItem(0, 0, usr);
		usrTblWidget->setItem(0, 1, ip);
		usrNumLbl->setText(tr("online users:%1").arg(usrTblWidget->rowCount()));
	}
}

void ChatRoomClient::slotLeftRefreshUserInfo(QString user_name, QString powerpoint)
{
	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	int rowNum = usrTblWidget->findItems(user_name, Qt::MatchExactly).first()->row();
	usrTblWidget->removeRow(rowNum);
	msgBrowser->setTextColor(Qt::gray);
	msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
	msgBrowser->append(tr("%1 to %2 leave!").arg(user_name).arg(time));
	usrNumLbl->setText(tr("online users:%1").arg(usrTblWidget->rowCount()));
}

void ChatRoomClient::slotDownLoad(QString serverAdd, QString clientAdd, QString file)
{
	serverAddress = serverAdd;
	int btn = QMessageBox::information(this, tr("Accept file"), tr("File from %1 (%2): %3, is it received?").arg(serverAdd).arg(serverAdd).arg(file), QMessageBox::Yes, QMessageBox::No);
	if (btn == QMessageBox::Yes) {
		QString name = QFileDialog::getSaveFileName(0, tr("save document"), file);
		if (!name.isEmpty())
		{
			FileClient *clnt = new FileClient(this);
			clnt->setFileName(name);
			clnt->setHostAddr(QHostAddress(serverAdd));
			clnt->show();
		}
	}

	else {
		sndMsg(Refuse, serverAdd);
	}
}

void ChatRoomClient::getFileName(QString name)
{
	fileName = name;
	sndMsg(FileName);
}

QString ChatRoomClient::getIP()
{
	QList<QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress addr, list) {
		if (addr.protocol() == QAbstractSocket::IPv4Protocol)
			return addr.toString();
	}
	return 0;
}