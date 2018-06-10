#pragma once
#ifndef PINWIDGET_H
#define PINWIDGET_H
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
#include "baseWidgetV2.h"

class baseInfoWidget_PinV2 : public baseWidgetV2
{
	Q_OBJECT
public:
	baseInfoWidget_PinV2(QWidget *parent = 0);
	~baseInfoWidget_PinV2();
	pinDashBoardWidget *pinDashBoard;

protected:
	
	public slots:


private:

};

#endif // DASHBOARDWIDGET_H
