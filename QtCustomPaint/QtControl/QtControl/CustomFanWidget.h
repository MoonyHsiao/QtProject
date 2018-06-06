#pragma once
#ifndef CUSTOMFANWIDGET_H
#define CUSTOMFANWIDGET_H

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
#include <QRadioButton>
#include "FanGraphWidget.h"


class CustomFanWidget : public QWidget
{
	Q_OBJECT
public:
	CustomFanWidget(QWidget *parent = 0);
	~CustomFanWidget();
	void setGeo(int, int);
	FanGraphWidget *fansWidget;
protected:
	void paintEvent(QPaintEvent *);

	public slots:


private:
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	int pointerNumber = 0;
	
	QString WidgetStyleSheet =
		"QWidget#shadowFrame"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: 5px;"  //設置邊框具備3個像素的圓角
								//"font-weight: bold;"  // 字體設置為加粗
								//"border-image:url(+userRunLocat+DPSIMAGE/Share/Background.PNG)};"
		"}";


};

#endif // DASHBOARDWIDGET_H
