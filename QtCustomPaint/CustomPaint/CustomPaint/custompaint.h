#ifndef CUSTOMPAINT_H
#define CUSTOMPAINT_H

#include <QtWidgets/QMainWindow>
#include "ui_custompaint.h"
#include "baseInfoWidget_Pin.h"
#include <QTimer>
#include "baseInfoWidget_Dash.h"
class CustomPaint : public QMainWindow
{
	Q_OBJECT

public:
	CustomPaint(QWidget *parent = 0);
	~CustomPaint();
	
private slots:
void demoInfo();
private:
	Ui::CustomPaintClass ui;
	baseInfoWidget_Pin *pinV12;
	baseInfoWidget_Dash *effDash;
	void setupDemoInfoTimer();
	QTimer* demoInfoTimer;
	QString effDashWidgetString =
		"<span style='font-size:12pt;"

		"color:rgb(106,106,102);"
		"'> %1</span>"
		"<span style='font-size:8pt;"
		"font-weight:600;"
		" color:rgb(106,106,102);'"
		"> %</span>"
		;
signals:
};

#endif // CUSTOMPAINT_H
