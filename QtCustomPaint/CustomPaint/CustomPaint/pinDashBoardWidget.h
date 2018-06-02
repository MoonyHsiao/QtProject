#pragma once

#ifndef PINDASHBOARDWIDGET_H
#define PINDASHBOARDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QLabel>
#include <QTime>
class pinDashBoardWidget : public QWidget
{
	Q_OBJECT
public:
	pinDashBoardWidget(QWidget *parent = 0);
	~pinDashBoardWidget();
	void setGeo(int, int);
	void setSamples(double);
	void setBenchMark(double value);
	void setPercDeviation(double value);
	QLabel* valueLabel;
	QLabel* valueUnitLabel;
	
protected:
	void paintEvent(QPaintEvent *);

public slots:
	
	
private:
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	int pointerNumber = 0;
	double benchMark = 12;
	double percDeviation = 0.72;
};

#endif // DASHBOARDWIDGET_H
