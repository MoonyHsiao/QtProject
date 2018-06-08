#include "baseInfoWidget_Dash.h"
#include <QDebug>


extern QString userRunPath;



baseInfoWidget_Dash::baseInfoWidget_Dash(QWidget *parent) :
	QWidget(parent)
{

	setStyleSheet(WidgetStyleSheet);
	setObjectName(QStringLiteral("shadowFrame"));

	QPixmap pm(userRunPath + "Image/dashBoard_White.PNG");
	int dashBoardWidth = pm.width()/2;
	int dashBoardHeight = pm.height()/2;
	int thisWidth = this->width();
	this->setAutoFillBackground(true);
	


	QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
	bodyShadow->setBlurRadius(9.0);
	bodyShadow->setColor(QColor(0, 0, 0, 100));
	bodyShadow->setOffset(2.0);
	setGraphicsEffect(bodyShadow);

	widgetTitle = new QLabel("label", this);
	widgetTitle->setGeometry((135 - 130) / 2, 4, 130, 15);
	widgetTitle->setStyleSheet(lblStyleSheet);
	widgetTitle->setAlignment(Qt::AlignCenter);
	QFont lblFont = widgetTitle->font();
	lblFont.setPointSize(9);
	lblFont.setBold(false);
	widgetTitle->setFont(lblFont);
	widgetTitle->setTextFormat(Qt::RichText);

	
	dashBoard = new dashBoardWidget(this);
	dashBoard->setGeo((135 - 110) / 2, 25);
	dashBoard->resize(135, 135);
	
	widgetValue = new QLabel("label", this);
	widgetValue->setGeometry((135 - 100) / 2, 110, 100, 25);
	widgetValue->setStyleSheet(lblStyleSheet);
	widgetValue->setAlignment(Qt::AlignCenter);
	widgetValue->setFont(lblFont);
	widgetValue->setTextFormat(Qt::RichText);
    

	lblImageXaxis = (135 - 33) / 2;
	lblImage = new QLabel(this);
	lblImage->setGeometry(lblImageXaxis, 60, 33, 33);
	lblWarning = new QLabel(this);
	lblWarning->setGeometry(26, 88, 120, 20);
	lblWarning->setObjectName("lowhigh");
	lblWarning->setStyleSheet(lblStyleSheet);
}

baseInfoWidget_Dash::~baseInfoWidget_Dash() {
}

void baseInfoWidget_Dash::setGeo(int _x, int _y) {
	this->setGeometry(_x, _y, pmFrameWidth, pmFrameHeight);
	this->update();
}

void baseInfoWidget_Dash::setWidgetTitle(QString text) {
	widgetTitle->setText(text);
}

void baseInfoWidget_Dash::setWidgetData(float data) {
	QString voltString = "%1 %2";
	widgetValue->setText(voltString.arg(QString::number(data, 'f', 0), widgetUnit));
}

void baseInfoWidget_Dash::setWidgetData(QString data)
{
	widgetValue->setText(data);
}

void baseInfoWidget_Dash::setWidgetUnit(QString unit) {
	widgetUnit = unit;
}

void baseInfoWidget_Dash::setlblImage(QString imageLocat) {
	
	QPixmap image(imageLocat);
	int w = lblImage->width();
	int h = lblImage->height();
	lblImage->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
}

void baseInfoWidget_Dash::movelblImageYaxis(int y) {
	lblImage->move(lblImageXaxis, y);
}

void baseInfoWidget_Dash::setWarningText(QString data)
{
	lblWarning->setText(data);
}

void baseInfoWidget_Dash::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

