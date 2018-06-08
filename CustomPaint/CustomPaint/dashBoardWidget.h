#pragma once

#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QLabel>

class dashBoardWidget : public QWidget
{
	Q_OBJECT
public:
	dashBoardWidget(QWidget *parent = 0);
	~dashBoardWidget();
	void setGeo(int, int);
	void setSamples(float);
	void setBarBackGroundColor(int, int, int);
	void setBarColor_100(int, int, int);
	void setBarColor_10(int, int, int);
	void setBarColor_0(int, int, int);
	void setUpperBound(float);
	
	void setTrafficLightModel(bool state);
protected:
	void paintEvent(QPaintEvent *);

public slots:

	
private:
	double progress = 0;
	int _maxValue = 100;
	int parentFrameWidth = 0;
	int parentFrameHeight = 0;
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	int pointerNumber = 0;
	int startedAngle = 0;
	int plotLen = 0;
	int barBackground_R = 255, barBackground_G = 255, barBackground_B = 255;
	float barColor_R_100 = 0, barColor_G_100 = 255, barColor_B_100 = 0;
	float barColor_R_10 = 0, barColor_G_10 = 255, barColor_B_10 = 0;
	float barColor_R_0 = 0, barColor_G_0 = 255, barColor_B_0 = 0;
	float UpperBound = 100;
	bool trafficLightModel = false;
	int greenLightXaxis = 0;
	int greenLightYaxis = 75;
	int amberLightXaxis = 55;
	int amberLightYaxis = 0;
	int redLightXaxis = 105;
	int redLightYaxis = 75;
	int trafficLightWidth = 2;
};

#endif // DASHBOARDWIDGET_H
