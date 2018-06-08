#include "qtcontrol.h"
extern QString userRunPath = "";
QtControl::QtControl(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QString appName = "../QtControl.png";
	userRunPath = QApplication::applicationDirPath() + "/"; //取得使用者跑這隻程式的位置


	translator = new QTranslator(this);
	qApp->installTranslator(translator);
	switch (systemLanguage)
	{
	case language::English:
		translator->load(userRunPath + "Language/en.qm");
		break;
	case language::Trad_Chinese:
		translator->load(userRunPath + "Language/tc.qm");
		break;
	default:
		break;
	}
	changeFont(systemLanguage); //改字型

	QColor pieColor(0, 168, 0);
	QBrush brush(pieColor);

	_switch = new QSwitchButton(this);
	_switch->setBrush(brush);
	_switch->setGeometry(20, 20, 40, 20);

	connect(_switch, SIGNAL(clicked()), this, SLOT(btnClick()));

	label = new QLabel("off", this);
	label->setGeometry(80, 20, 120, 20);
	//label->setObjectName("TXT_HELLO_WORLD");

	/*coverOverlay = new LoadingOverlay(this);
	coverOverlay->setWarningText("Loading....123");
	coverChangeTimer = new QTimer(this);
	coverChangeTimer->setInterval(2000);
	connect(coverChangeTimer, SIGNAL(timeout()), this, SLOT(coverShowSlot()), Qt::DirectConnection);
	coverChangeTimer->start();*/
	//MainCoverFrame = new QWidget(this);

	CustomFan = new CustomFanWidget(this);
	CustomFan->setGeometry(140, 20, 270, 270);

	btnGetBallPos = new QPushButton(tr("getBallPos"), this);
	btnGetBallPos->setObjectName("btnGetBallPos");
	btnGetBallPos->setGeometry(QRect(440, 20, 120, 30));
	btnGetBallPos->setCursor(Qt::PointingHandCursor);
	connect(btnGetBallPos, SIGNAL(clicked()), this, SLOT(getPosClick()));

	connect(CustomFan->fansWidget, SIGNAL(emitPos(QMap<int, QPointF>)), this, SLOT(transResult(QMap<int, QPointF>)));

	lblPos = new QLabel(this);
	lblPos->setGeometry(440, 60, 200, 20);

	btnPopUpTempUnitSelect = new QPushButton("pop", this);
	btnPopUpTempUnitSelect->setGeometry(20, 100, 120, 30);
	btnPopUpTempUnitSelect->setCheckable(true);
	btnPopUpTempUnitSelect->setCursor(Qt::PointingHandCursor);
	connect(btnPopUpTempUnitSelect, SIGNAL(clicked()), this, SLOT(popUpTempUnit()));


	tempUnitWidget = new popupWidget(btnPopUpTempUnitSelect, this);
	tempUnitWidget->initSize(122, 120);
	tempUnitWidget->setMove(145, 0);//設定跳出的距離
	tempUnitWidget->setBtnSize(80, 15);
	tempUnitWidget->initFunctionName(tr("PopWidget_TempUnit"));
	QStringList tempUnitString;
	tempUnitString << "TEMP_Celsius" << "TEMP_Fahrenheit";
	tempUnitWidget->initFuntionbtn(2, tempUnitString);
	connect(tempUnitWidget, SIGNAL(returnSelectFunction(QStringList)), this, SLOT(tempUnitSelected(QStringList)));
	tempUnitWidget->initBtnSelect(tempUnitIndex(globalTempUnit));
	tempUnitWidget->setHidden(true);

	btnLanguageSelect = new QPushButton(tr("PopWidget_Lang"), this);
	btnLanguageSelect->setGeometry(20, 140, 120, 30);
	btnLanguageSelect->setCheckable(true);
	btnLanguageSelect->setCursor(Qt::PointingHandCursor);
	connect(btnLanguageSelect, SIGNAL(clicked()), this, SLOT(popUpLanguage()));

	languageWidget = new popupWidget(btnLanguageSelect, this);
	languageWidget->initSize(142, 120);
	languageWidget->setMove(145, 0);//設定跳出的距離
	languageWidget->setBtnSize(120, 15);
	languageWidget->initFunctionName(tr("PopWidget_Lang"));
	QStringList languageString;
	languageString << "LANG0" << "LANG1";
	languageWidget->initFuntionbtn(2, languageString);
	connect(languageWidget, SIGNAL(returnSelectFunction(QStringList)), this, SLOT(languageSelected(QStringList)));
	languageWidget->initBtnSelect(languageIndex(systemLanguage));
	languageWidget->setHidden(true);
	takeScreenshot(appName);
}

QtControl::~QtControl()
{

}

void QtControl::mouseMoveEvent(QMouseEvent* event) {

	if (event->y() < 40 && event->x() < 1000)
		move(event->globalX() - mouseClick_X_Coordinate, event->globalY() - mouseClick_Y_Coordinate);
}

void QtControl::mousePressEvent(QMouseEvent *event) {
	hiddenCheck();
	mouseClick_X_Coordinate = event->x();
	mouseClick_Y_Coordinate = event->y();

}

void QtControl::mouseReleaseEvent(QMouseEvent * event)
{
	//qDebug() << "this->pos().x:" << this->pos().x();
	//qDebug() << "this->pos().y:" << this->pos().y();
	int posX = this->pos().x();
	int posY = this->pos().y();

	//eleCost->setMove(posX + 1000 - 210, posY + 400 - 40);
}

void QtControl::btnClick()
{

	QString state;
	_switch->switchState() ? state = "on" : state = "off";
	label->setText(state);
}

void QtControl::getPosClick()
{
	CustomFan->fansWidget->getItemPoint();

}

void QtControl::transResult(QMap<int, QPointF> data)
{
	qDebug() << "data:" << data;
	//lblPos->setText("aaa");

	QJsonObject json;

	QMapIterator<int, QPointF> i(data);
	while (i.hasNext()) {
		i.next();

		//json.insert(i.key(), i.value());
	}
}

void QtControl::setSize(QObject * obj)
{
	if (obj->isWidgetType()) static_cast<QWidget*>(obj)->setGeometry(rect());
}

void QtControl::takeScreenshot(const QString screenshotFileName)
{
	/*if (isActiveWindow())
	{
		auto grabbedScreenshot = QWidget::grab();
		grabbedScreenshot.save(screenshotFileName);
	}*/

	auto grabbedScreenshot = QWidget::grab();
	grabbedScreenshot.save(screenshotFileName);
}

void QtControl::coverShowSlot()
{

	if (coverOverlay->isHidden()) {
		coverOverlay->show();
		MainCoverFrame->show();
	}
	else {
		coverOverlay->hide();
		MainCoverFrame->hide();
	}

}

bool QtControl::event(QEvent * ev)
{
	if (ev->type() == QEvent::ChildAdded) {
		setSize(static_cast<QChildEvent*>(ev)->child());
	}
	return QWidget::event(ev);
}

void QtControl::resizeEvent(QResizeEvent *)
{
	//for (auto obj : children()) setSize(obj);
}


void QtControl::popUpTempUnit()
{
	if (tempUnitWidget->isHidden())
	{
		tempUnitWidget->setHidden(false);
		tempUnitWidget->startAmin();
	}

	else
	{
		tempUnitWidget->setHidden(true);
	}
}

void QtControl::popUpLanguage()
{

	if (languageWidget->isHidden())
	{
		languageWidget->setHidden(false);
		languageWidget->startAmin();
	}

	else
	{
		languageWidget->setHidden(true);
	}
}

QString QtControl::tempUnitIndex(int i)
{
	if (i == TempUnit::Celsius) {
		return "TEMP_Celsius";
	}
	else {
		return "TEMP_Fahrenheit";
	}
}

QString QtControl::languageIndex(int i)
{
	if (i == language::English) {
		return "LANG0";
	}
	else {
		return "LANG1";
	}
}

void QtControl::changeFont(int language) {

	if (language != 1) {

		QFont newFont("Verdana", 8, false);
		QApplication::setFont(newFont);
	}

	else {
		QFont newFont("Microsoft JhengHei", 9, QFont::Bold);
		QApplication::setFont(newFont);
	}

}

void QtControl::resetLanguage() {

	tempUnitWidget->initFunctionName(tr("PopWidget_TempUnit"));
	languageWidget->initFunctionName(tr("PopWidget_Lang"));
	languageWidget->resetLanguage();
	QString SpeedModeString = languageWidget->getSelectName();
	btnLanguageSelect->setText(tr(SpeedModeString.toLatin1()));
}

void QtControl::tempUnitSelected(QStringList data)
{
	int tempUnit = data[0].toInt();

	if (tempUnit == TempUnit::Celsius)
	{

	}
}

void QtControl::languageSelected(QStringList data) {

	int languageIndex = data[0].toInt();
	

	if (languageIndex == language::English)
	{
		translator->load(userRunPath + "Language/en.qm");
	}

	else {

		translator->load(userRunPath + "Language/tc.qm");
	}

	systemLanguage = languageIndex;
	changeFont(languageIndex);
	resetLanguage();

}


void QtControl::hiddenCheck()
{
	QList<popupWidget *> pop = this->findChildren<popupWidget *>();
	foreach(popupWidget *pop, pop)
		if (pop != NULL) {
			if (!pop->isHidden() && pop->objectName() != "aaaa") {
				pop->setHidden(true);
			}
		}
}
