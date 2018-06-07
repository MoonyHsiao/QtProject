#ifndef CUSTOMPAINT_H
#define CUSTOMPAINT_H

#include <QtWidgets/QMainWindow>
#include "ui_custompaint.h"
#include "baseInfoWidget_Pin.h"
#include <QTimer>
#include "baseInfoWidget_Dash.h"
#include "baseInfoWidget_Clock.h"
class CustomPaint : public QMainWindow
{
	Q_OBJECT

public:
	CustomPaint(QWidget *parent = 0);
	~CustomPaint();
	
private slots:
void simulationClock();
void demoInfo();
void takeScreenshot();
private:
	Ui::CustomPaintClass ui;
	baseInfoWidget_Pin *pinV12;
	baseInfoWidget_Dash *effDash;
	
	QTimer* demoInfoTimer;
	QTimer* clockTimer;
	QString effDashWidgetString =
		"<span style='font-size:12pt;"
		"color:rgb(106,106,102);"
		"'> %1</span>"
		"<span style='font-size:8pt;"
		"font-weight:600;"
		" color:rgb(106,106,102);'"
		"> %</span>"
		;
	QString clockString = "%1h%2m";
	baseInfoWidget_Clock *clock;
	QStringList clockDataList;
	void setupClockTimer();
	void reSetClock();
	void setupDemoInfoTimer();
	int clockDataIndex = 0;
	int clockTime = 0;
	
signals:
};

#endif // CUSTOMPAINT_H
