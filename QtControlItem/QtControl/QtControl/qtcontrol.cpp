#include "qtcontrol.h"
extern QString userRunPath = "";
QtControl::QtControl(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QString appName = "../QtControl.png";
	userRunPath = QApplication::applicationDirPath() + "/"; //取得使用者跑這隻程式的位置
	


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
	btnGetBallPos->setGeometry(QRect(440, 20, 60, 30));
	btnGetBallPos->setCursor(Qt::PointingHandCursor);
	connect(btnGetBallPos, SIGNAL(clicked()), this, SLOT(getPosClick()));

	connect(CustomFan->fansWidget, SIGNAL(emitPos(QMap<int, QPointF>)), this, SLOT(transResult(QMap<int, QPointF>)));

	lblPos = new QLabel(this);
	lblPos->setGeometry(440, 60, 200, 20);

	

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
	/*bool check =_switch->switchState();

	if (check) {
	label->setText("on");
	}

	else{
	label->setText("off");
	}*/
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


