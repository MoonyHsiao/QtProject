#pragma once
#ifndef BASEINFOWIDGET_DASH_H
#define BASEINFOWIDGET_DASH_H



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

class baseInfoWidget_Dash : public QWidget
{
	Q_OBJECT
public:
	baseInfoWidget_Dash(QWidget *parent = 0);
	~baseInfoWidget_Dash();
	void setGeo(int, int);
	
	QLabel* widgetTitle;
	QLabel* widgetValue;
	QLabel* lblImage;
	
	void setWidgetTitle(QString text);
	void setWidgetData(float data);
	void setWidgetData(QString data);
	void setWidgetUnit(QString unit);
	void setlblImage(QString imageLocat);
	void movelblImageYaxis(int y);
	dashBoardWidget *dashBoard;
	int lblImageXaxis = 0;
	void setWarningText(QString data);
protected:
	void paintEvent(QPaintEvent *);

	public slots:


private:
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	int pointerNumber = 0;
	double benchMark = 12;
	double percDeviation = 0.72;
	QLabel* lblWarning;
	QString widgetUnit = "W";
#pragma region StyleSheet
	QString lblStyleSheet =
		"QLabel"
		"{"
		//"background: rgb(0, 0, 255);"
		//"gridline-color: rgb(255, 57, 163);"
		//"selection-color: rgb(180, 114, 255);"
		"selection-background-color: rgb(255, 187, 209);"
		//"background-color: rgb(193, 255, 57);"
		"border: 0px solid rgb(0, 0, 0);"
		"border-radius: 10px;"
		"color: rgb(102, 51, 0);"
		"padding : 0;"
		"margin : 0;"
		"}"
		"QLabel#lowhigh"
		"{"
		"color: rgb(106, 106, 102);"
		"}"
		;

	QString WidgetStyleSheet =
		"QWidget#shadowFrame"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: 5px;" 
		"}";

#pragma endregion StyleSheet
};

#endif // DASHBOARDWIDGET_H
