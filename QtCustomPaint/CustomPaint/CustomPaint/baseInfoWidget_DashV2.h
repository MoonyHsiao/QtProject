#pragma once
#ifndef BASEINFOWIDGET_DASHV2_H
#define BASEINFOWIDGET_DASHV2_H
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
#include "dashBoardWidget.h"
#include <QRadioButton>
#include "baseWidgetV2.h"


class baseInfoWidget_DashV2 : public baseWidgetV2
{
	Q_OBJECT
public:
	baseInfoWidget_DashV2(QWidget *parent = 0);
	~baseInfoWidget_DashV2();
	dashBoardWidget *dashBoard;
	void setWidgetUnit(QString unit);
	void setlblImage(QString imageLocat);
	QLabel* lblImage;
	int lblImageXaxis = 0;
	void movelblImageYaxis(int y);
	void setWidgetData(float data);
	void setWidgetData(QString data);
protected:
	
	public slots:


private:
	QString widgetUnit = "W";
};

#endif // DASHBOARDWIDGET_H
