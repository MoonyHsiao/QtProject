#pragma once
#ifndef BASEWIDGETV2_H
#define BASEWIDGETV2_H

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

class baseWidgetV2 : public QWidget
{
	Q_OBJECT
public:
	baseWidgetV2(QWidget *parent = 0);
	~baseWidgetV2();
	void setGeo(int, int);
	
	void setWidgetTitle(QString text);
	void setWidgetValue(QString text);
	void setWidgetValueGeometry(int x,int y, int w,int h);
protected:
	void paintEvent(QPaintEvent *);

	public slots:


private:
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	void initStyleSheet();
	QString lblStyleSheet;
	QString WidgetStyleSheet;
	QLabel* lblWidgetTitle;
	QLabel* lblWidgetValue;
};

#endif // DASHBOARDWIDGET_H
