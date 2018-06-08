#include "popupWidget.h"
#include <QDebug>

/*QWidget Supports only the background, background - clip and background - originproperties.
If you subclass from QWidget, you need to provide a paintEvent for your customQWidget as below : */

extern QString userRunPath;



popupWidget::popupWidget(QPushButton* button, QWidget *parent) :
	QWidget(parent), b(button)
{

	setStyleSheet(WidgetStyleSheet);
	//lblFunctionTitle = new QLabel(tr("Function Name"), this);
	lblFunctionTitle = new QLabel(tr("MAIN_STR_FAN_SILENT"), this);
	lblFunctionTitle->setStyleSheet(labelStyleSheet);
	lblFunctionTitle->setAlignment(Qt::AlignCenter);
	QFont lblFunctionTitleFont = lblFunctionTitle->font();
	lblFunctionTitleFont.setPointSize(9);
	//lblFunctionTitleFont.setFixedPitch(true);
	lblFunctionTitle->setFont(lblFunctionTitleFont);

	thisWidth = this->width();
	thisHeight = this->height();
	lblFunctionTitle->setGeometry((thisWidth - 130) / 2, 10, 130, 20);
	btnSize.setWidth(100);
	btnSize.setHeight(30);
	movePoint.setX(0);
	movePoint.setY(0);

	QGraphicsOpacityEffect *graohEff = new QGraphicsOpacityEffect(this);
	this->setGraphicsEffect(graohEff);
	anim = new QPropertyAnimation(graohEff, "opacity");
	anim->setDuration(1000);
	anim->setEasingCurve(QEasingCurve::InOutQuad);
	anim->setStartValue(0);
	anim->setEndValue(5);
}

popupWidget::~popupWidget()
{

}

void popupWidget::showEvent(QShowEvent * event) {
	
	int x = this->size().width();
	lblFunctionTitle->setGeometry((x - 120) / 2, 10, 120, 20);
	//lblFunctionTitle->setGeometry((thisWidth - 100) / 2, 10, 100, 20);
	QRect geo = b->geometry();
	//qDebug() << "geo.x() " << geo.width();
	//qDebug() << "geo.y() " << geo.height();
	//qDebug() << "geo.width()" << geo.x();
	//qDebug() << "geo.height()" << geo.y();
	this->move(geo.x() + geo.width() + movePoint.x(), geo.y() + geo.height() + movePoint.y());
	
}

void popupWidget::startAmin() {
	//test123
	anim->start();
}

void popupWidget::initFunctionName(QString Name) {

	lblFunctionTitle->setText(Name);
}

void popupWidget::initSize(int w, int h) {

	thisWidth = w;
	thisHeight = h;
	resize(w, h);

}

void popupWidget::initFuntionbtn(int btnNum, QStringList btnName) {

	functionCount = btnNum;
	controllerGroup = new QButtonGroup(this);
	for (size_t i = 0; i < btnNum; i++) {

		QPushButton *btn = new QPushButton(this);
		//qDebug() << "btnSize.width():" << btnSize.width();
		//qDebug() << "btnSize.height():" << btnSize.height();
		btn->setGeometry((thisWidth - btnSize.width()) / 2, i * (btnSize.height() + 10) + 40, btnSize.width(), btnSize.height());
		btn->setObjectName(btnName[i]);
		btn->setText(tr(btnName[i].toLatin1()));
		btn_qobject_cast << btnName[i];
		btn->setStyleSheet(btnStyleSheet);
		btn->setCheckable(true);
		btn->setChecked(false);
		connect(btn, SIGNAL(clicked()), this, SLOT(functionSelected()));
		controllerGroup->addButton(btn);
		controllerGroup->setId(btn, i);
	}
}

void popupWidget::setMove(int x, int y) {

	movePoint.setX(x);
	movePoint.setY(y);
}

void popupWidget::setBtnSize(int width, int height) {
	btnSize.setWidth(width);
	btnSize.setHeight(height);
}

void popupWidget::initBtnSelect(QString Name)
{
	QList<QPushButton *> btn = this->findChildren<QPushButton *>();
	foreach(QPushButton *btn, btn)
		if (btn->objectName() == Name) {
			qDebug() << btn->objectName();
			btn->setChecked(true);
			btn->click();
		}
}

void popupWidget::resetLanguage()
{
	QList<QPushButton *> btn = this->findChildren<QPushButton *>();
	foreach(QPushButton *btn, btn) {
		QString btnObjectName = btn->objectName();
		btn->setText(tr(btnObjectName.toLatin1()));
	}
}

void popupWidget::setNonHidden(bool state)
{
	nonHidden = state;
}

void popupWidget::setItemDisable(QStringList btnName)
{
	for (size_t i = 0; i < btnName.length(); i++)
	{
		QList<QPushButton *> btn = this->findChildren<QPushButton *>();
		foreach(QPushButton *btn, btn)
			if (btn->objectName() == btnName[i]) {

				qDebug() << btn->objectName();
				btn->setEnabled(false);

			}
	}

}

QString popupWidget::getSelectName()
{
	QList<QPushButton *> btn = this->findChildren<QPushButton *>();
	foreach(QPushButton *btn, btn) {
		if (btn->isChecked()) {
			return btn->objectName();
		}
	}
	return "NotExist";
}

void popupWidget::setItemEnable()
{
	QList<QPushButton *> btn = this->findChildren<QPushButton *>();
	foreach(QPushButton *btn, btn) {
		btn->setEnabled(true);
	}
}

void popupWidget::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void popupWidget::functionSelected() {

	QPushButton *btn = qobject_cast<QPushButton *>(sender());

	for (size_t i = 0; i < functionCount; i++)
	{
		if (btn->objectName() == btn_qobject_cast[i])
		{
			QStringList returnData;
			returnData << QString::number(i) << btn->objectName();
			emit returnSelectFunction(returnData);
			btn->setChecked(true);
			if (!nonHidden) {
				this->setHidden(true);
			}
		}
	}
}

