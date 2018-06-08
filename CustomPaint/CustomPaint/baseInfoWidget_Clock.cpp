#include "baseInfoWidget_Clock.h"
#include <QDebug>


extern QString userRunPath;



baseInfoWidget_Clock::baseInfoWidget_Clock(QWidget *parent) :
	QWidget(parent)
{

	setStyleSheet(WidgetStyleSheet);
	setObjectName(QStringLiteral("shadowFrame"));

	QPixmap pm(userRunPath + "Image/dashBoard_White.PNG");
	int dashBoardWidth = pm.width();
	int dashBoardHeight = pm.height();
	int thisWidth = this->width();
	//this->resize(pmFrameWidth, pmFrameHeight);
	this->setAutoFillBackground(true);
	qDebug() << "pmFrameWidth: " << pmFrameWidth;
	qDebug() << "pmFrameHeight: " << pmFrameHeight;


	QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
	bodyShadow->setBlurRadius(9.0);
	bodyShadow->setColor(QColor(0, 0, 0, 100));
	bodyShadow->setOffset(2.0);
	setGraphicsEffect(bodyShadow);

	widgetTitle = new QLabel("label", this);
	widgetTitle->setGeometry((135 - 130) / 2, 2, 130, 20);
	widgetTitle->setStyleSheet(lblStyleSheet);
	widgetTitle->setAlignment(Qt::AlignCenter);
	QFont lblFont = widgetTitle->font();
	lblFont.setPointSize(10);
	lblFont.setBold(false);
	widgetTitle->setFont(lblFont);

}

baseInfoWidget_Clock::~baseInfoWidget_Clock() {


}

void baseInfoWidget_Clock::setGeo(int _x, int _y) {
	this->setGeometry(_x, _y, pmFrameWidth, pmFrameHeight);
	this->update();
}

void baseInfoWidget_Clock::setWidgetTitle(QString text) {
	widgetTitle->setText(text);
}

void baseInfoWidget_Clock::setSample(QStringList data)
{
	dataList = data;
	this->update();
}

void baseInfoWidget_Clock::setClock(QString time)
{

	drawString = time;
}

void baseInfoWidget_Clock::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	//QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	//QRectF rectangle_MidPie(33.0, 38.0, 70.0, 70.0);
	QRectF rectangle_MidPie(30.0, 35.0, 80.0, 80.0);
	QPen penBar;
	//penBar.setCapStyle(Qt::RoundCap);
	penBar.setWidth(10);
	QConicalGradient barGradient(135, 135, 45);

	barGradient.setColorAt(0.0, QColor(212, 212, 212));
	barGradient.setColorAt(1 / 6.0, QColor(186, 186, 186));
	barGradient.setColorAt(2 / 6.0, QColor(166, 166, 166));
	barGradient.setColorAt(3 / 6.0, QColor(136, 136, 136));
	barGradient.setColorAt(4 / 6.0, QColor(166, 166, 166));
	barGradient.setColorAt(5 / 6.0, QColor(186, 186, 186));
	barGradient.setColorAt(6 / 6.0, QColor(212, 212, 212));

	QBrush barBrush(barGradient);
	penBar.setBrush(barBrush);
	p.setPen(penBar);
	p.setBrush(barBrush);
	p.drawPie(rectangle_MidPie, 0 * 16, 360 * 16);

	QPen pen;



	//QRectF rectangle2(38.0, 43.0, 60.0, 60.0);
	QRectF rectangle2(35.0, 40.0, 70.0, 70.0);
	QPen pen2;
	QColor pieColor(240, 240, 216);
	pen2.setColor(pieColor);
	QBrush brush(pieColor);
	p.setBrush(brush);
	p.setPen(pen2);
	p.drawPie(rectangle2, 0 * 16, 360 * 16);

	QFont font = p.font();
	font.setPointSize(13);
	//font.setWeight(QFont::DemiBold);
	p.setFont(font);
	QPen penClock;
	QColor clockColor(102, 51, 0);
	penClock.setColor(clockColor);
	p.setPen(penClock);
	p.drawText(rectangle2, Qt::AlignCenter, drawString);

	//p->setRenderHint(QPainter::Antialiasing, true);
	//QRectF rectangle3(0, 20, 120.0, 30.0);
	//doc->drawContents(&p, rectangle3);
	QTransform trans;


	//trans.translate(width() / 2, height() / 2);
	//trans.translate(68, 72);
	trans.translate(70, 76);
	//trans.rotate(rotateValue);
	p.setRenderHint(QPainter::Antialiasing);
	QPen pen22;
	for (int j = 0; j < dataList.count(); ++j) {
		//if ((j % 5) != 0)
		trans.rotate(1.0);
		p.setTransform(trans);
		float value = dataList[j].toFloat();
		//qDebug() << "index[" << j << "]" << value;
		if (value > 0) {
			if (value <= 0.33) {
				pen22.setColor(QColor(117, 117, 117));

			}

			else if (value > 0.33 && value <= 0.75) {
				pen22.setColor(QColor(129, 188, 0));

			}

			else if (value > 0.75 && value <= 1) {
				pen22.setColor(QColor(255, 0, 0));

			}
			p.setPen(pen22);
			p.drawLine(34, 0, 48, 0);
		}
		else {
			//qDebug() << "no data";
		}
	}
}

