#include "baseInfoWidget_Pin.h"
#include <QDebug>


extern QString userRunPath;



baseInfoWidget_Pin::baseInfoWidget_Pin(QWidget *parent) :
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



	pinDashBoard = new pinDashBoardWidget(this);
	pinDashBoard->setGeo((135 - dashBoardWidth) / 2, 30);

	
	widgetTitle = new QLabel("label", this);
	widgetTitle->setGeometry((135 - 20) / 2, 2, 60, 20);
	widgetTitle->setStyleSheet(lblStyleSheet);
	
	QFont lblFont = widgetTitle->font();
	lblFont.setPointSize(10);
	lblFont.setBold(false);
	widgetTitle->setFont(lblFont);


	QLabel* lblLowHigh = new QLabel("Low                 High", this);
	lblLowHigh->setGeometry(13, 88, 120, 20);
	lblLowHigh->setObjectName("lowhigh");
	lblLowHigh->setStyleSheet(lblStyleSheet);
	

}

baseInfoWidget_Pin::~baseInfoWidget_Pin() {


}

void baseInfoWidget_Pin::setGeo(int _x, int _y) {
	this->setGeometry(_x, _y, pmFrameWidth, pmFrameHeight);
	this->update();
}

void baseInfoWidget_Pin::setWidgetTitle(QString text) {
	widgetTitle->setText(text);
}

void baseInfoWidget_Pin::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void baseInfoWidget_Pin::initStyleSheet()
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

