#include "dashBoardWidget.h"
#include <QDebug>


extern QString userRunPath;

dashBoardWidget::dashBoardWidget(QWidget *parent) :
	QWidget(parent)
{
	parentFrameWidth = parent->width();
	parentFrameHeight = parent->height();

	QPixmap pm(userRunPath + "Image/dashBoard_White.PNG");
	pmFrameWidth = pm.width()/2;
	pmFrameHeight = pm.height()/2;
	this->resize(pmFrameWidth, pmFrameHeight);
}

dashBoardWidget::~dashBoardWidget()
{

}


void dashBoardWidget::setGeo(int _x, int _y) {

	this->setGeometry(_x, _y, pmFrameWidth, pmFrameWidth);
	this->update();
}

void dashBoardWidget::setSamples(float _pointerNumber) {

	float pointerNumber = (UpperBound - _pointerNumber) / UpperBound * 240;
	startedAngle = -30 + pointerNumber;
	plotLen = 240 - pointerNumber;
	this->update();
}

void dashBoardWidget::setBarBackGroundColor(int r, int g, int b) {

	barBackground_R = r;
	barBackground_G = g;
	barBackground_B = b;
	this->update();
}

void dashBoardWidget::setBarColor_100(int r, int g, int b) {

	barColor_R_100 = r;
	barColor_G_100 = g;
	barColor_B_100 = b;
	this->update();
}

void dashBoardWidget::setBarColor_10(int r, int g , int b)
{
	barColor_R_10 = r;
	barColor_G_10 = g;
	barColor_B_10 = b;
	this->update();
}

void dashBoardWidget::setBarColor_0(int r, int g, int b)
{
	barColor_R_0 = r;
	barColor_G_0 = g;
	barColor_B_0 = b;
	this->update();
}

void dashBoardWidget::setUpperBound(float value) {

	UpperBound = value;
}

void dashBoardWidget::setTrafficLightModel(bool state){
	trafficLightModel = state;
}

void dashBoardWidget::paintEvent(QPaintEvent *) {

	QPainter p(this);

	if (trafficLightModel) {
		QPen penGreenLight;
		penGreenLight.setCapStyle(Qt::RoundCap);
		penGreenLight.setColor(QColor(0, 224, 4));
		penGreenLight.setWidth(trafficLightWidth);
		p.setPen(penGreenLight);
		p.drawLine(greenLightXaxis, greenLightYaxis, greenLightXaxis + 5, greenLightYaxis);

		QPen penAmberLight;
		penAmberLight.setCapStyle(Qt::RoundCap);
		penAmberLight.setColor(QColor(72, 211, 236));
		penAmberLight.setWidth(trafficLightWidth);
		p.setPen(penAmberLight);
		p.drawLine(amberLightXaxis, amberLightYaxis, amberLightXaxis, amberLightYaxis + 5);

		QPen penRedLight;
		penRedLight.setCapStyle(Qt::RoundCap);
		penRedLight.setColor(QColor(255, 0, 0));
		penRedLight.setWidth(trafficLightWidth);
		p.setPen(penRedLight);
		p.drawLine(redLightXaxis, redLightYaxis, redLightXaxis + 5, redLightYaxis);
	}

	const QRectF bounds(5, 8, 100, 100);
	p.setRenderHint(QPainter::Antialiasing);
	QPen penBarBackGround;
	penBarBackGround.setWidth(3);
	QColor barBackGroundColor(barBackground_R, barBackground_G, barBackground_B);
	penBarBackGround.setColor(barBackGroundColor);
	p.setPen(penBarBackGround);
	//p.drawArc(10, 10, 100, 100, -30 * 16, 240 * 16);
	p.drawArc(bounds, -30 * 16, 240 * 16);

	QPen penBar;
	penBar.setCapStyle(Qt::RoundCap);
	penBar.setWidth(7);
	QLinearGradient barGradient;
	//gradient.setStart(10, 110);
	barGradient.setStart(bounds.left(), bounds.left() + bounds.height());
	//gradient.setFinalStop(110, 110);
	barGradient.setFinalStop(bounds.left() + bounds.width(), bounds.top() + bounds.height());
	//barGradient.setColorAt(0, QColor(barColor_R / colorDiv, barColor_G / colorDiv, barColor_B / colorDiv));
	//barGradient.setColorAt(1, QColor(barColor_R, barColor_G, barColor_B));
	barGradient.setColorAt(0, QColor(barColor_R_0, barColor_G_0, barColor_B_0));
	barGradient.setColorAt(0.1, QColor(barColor_R_10, barColor_G_10, barColor_B_10));
	barGradient.setColorAt(1, QColor(barColor_R_100, barColor_G_100, barColor_B_100));
	QBrush barBrush(barGradient);
	penBar.setBrush(barBrush);
	p.setPen(penBar);
	p.drawArc(bounds, startedAngle * 16, plotLen * 16);



}