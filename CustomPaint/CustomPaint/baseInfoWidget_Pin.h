#pragma once
#ifndef BASEINFOWIDGET_PIN_H
#define BASEINFOWIDGET_PIN_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QLabel>
#include <QTime>
#include <QStyleOption>
#include <QAbstractAnimation>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "pinDashBoardWidget.h"
#include <QRadioButton>

class baseInfoWidget_Pin : public QWidget
{
	Q_OBJECT
public:
	baseInfoWidget_Pin(QWidget *parent = 0);
	~baseInfoWidget_Pin();
	void setGeo(int, int);
	
	QLabel* widgetTitle;
	pinDashBoardWidget *pinDashBoard;

	void setWidgetTitle(QString text);
protected:
	void paintEvent(QPaintEvent *);

	public slots:


private:
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	int pointerNumber = 0;
	double benchMark = 12;
	double percDeviation = 0.72;
	void initStyleSheet();
	QString lblStyleSheet;
	QString WidgetStyleSheet;
};

#endif // DASHBOARDWIDGET_H
