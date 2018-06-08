#include "CustomFanWidget.h"
#include <QDebug>

extern QString userRunPath;
CustomFanWidget::CustomFanWidget(QWidget *parent) :
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

	fansWidget = new FanGraphWidget(this);
}

CustomFanWidget::~CustomFanWidget() {
}

void CustomFanWidget::setGeo(int _x, int _y) {
	this->setGeometry(_x, _y, pmFrameWidth, pmFrameHeight);
	this->update();
}

void CustomFanWidget::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

