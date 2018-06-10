#include "baseWidgetV2.h"
#include <QDebug>

extern QString userRunPath;

baseWidgetV2::baseWidgetV2(QWidget *parent) :
	QWidget(parent)
{
	initStyleSheet();
	setStyleSheet(WidgetStyleSheet);
	setObjectName(QStringLiteral("shadowFrame"));

	QPixmap pm(userRunPath + "Image/dashBoard_White.PNG");
	int dashBoardWidth = pm.width() / 2;
	int dashBoardHeight = pm.height() / 2;
	int thisWidth = this->width();
	this->setAutoFillBackground(true);
	
	QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
	bodyShadow->setBlurRadius(9.0);
	bodyShadow->setColor(QColor(0, 0, 0, 100));
	bodyShadow->setOffset(2.0);
	setGraphicsEffect(bodyShadow);

	lblWidgetTitle = new QLabel("label", this);
	lblWidgetTitle->setGeometry((135 - 135) / 2, 2, 135, 20);
	lblWidgetTitle->setAlignment(Qt::AlignCenter);
	lblWidgetTitle->setStyleSheet(lblStyleSheet);
	
	QFont lblFont = lblWidgetTitle->font();
	lblFont.setPointSize(10);
	lblFont.setBold(false);
	lblWidgetTitle->setFont(lblFont);


	lblWidgetValue = new QLabel("Low                 High", this);
	lblWidgetValue->setGeometry(13, 88, 120, 20);
	lblWidgetValue->setObjectName("lowhigh");
	lblWidgetValue->setStyleSheet(lblStyleSheet);
	lblWidgetValue->setAlignment(Qt::AlignCenter);

}

baseWidgetV2::~baseWidgetV2() {


}

void baseWidgetV2::setGeo(int _x, int _y) {
	this->setGeometry(_x, _y, pmFrameWidth, pmFrameHeight);
	this->update();
}

void baseWidgetV2::setWidgetTitle(QString text) {
	lblWidgetTitle->setText(text);
}

void baseWidgetV2::setWidgetValue(QString text)
{
	lblWidgetValue->setText(text);
}

void baseWidgetV2::setWidgetValueGeometry(int x, int y, int w, int h)
{
	lblWidgetValue->setGeometry(x, y, w, h);
}

void baseWidgetV2::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void baseWidgetV2::initStyleSheet()
{
#pragma region StyleSheet
	
	lblStyleSheet =
		"QLabel"
		"{"
		//"background: rgb(0, 0, 255);"
		//"gridline-color: rgb(255, 57, 163);"
		//"selection-color: rgb(180, 114, 255);"
		"selection-background-color: rgb(255, 187, 209);"
		//"background-color: rgb(193, 255, 57);"
		"border: 0px solid rgb(0, 0, 0);"
		"border-radius: 10px;"
		"color: rgb(102, 51, 0);"
		"padding : 0;"
		"margin : 0;"
		"}"
		"QLabel#lowhigh"
		"{"
		"color: rgb(106, 106, 102);"
		"}"
		;

	WidgetStyleSheet =
		"QWidget#shadowFrame"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: 5px;"  //設置邊框具備3個像素的圓角
								//"font-weight: bold;"  // 字體設置為加粗
								//"border-image:url(+userRunLocat+DPSIMAGE/Share/Background.PNG)};"
		"}";



#pragma endregion StyleSheet
}

