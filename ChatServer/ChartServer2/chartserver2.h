#ifndef CHARTSERVER2_H
#define CHARTSERVER2_H
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_chartserver2.h"
#include <QToolBox>
#include <QToolButton>
#include "chatWidget.h"

class ChartServer2 : public QToolBox
{
	Q_OBJECT

public:
	ChartServer2(QWidget *parent = 0, Qt::WindowFlags f = 0);
	~ChartServer2();
	private slots:
	void showChatWidget1();
	void showChatWidget2();
	void showChatWidget3();
	void showChatWidget4();
	
	
private:
	Ui::ChartServer2Class ui;
	QToolButton *toolBtn1;
	QToolButton *toolBtn2;
	QToolButton *toolBtn3;
	QToolButton *toolBtn4;
	
	chatWidget *chatWidget1;
	chatWidget *chatWidget2;
	chatWidget *chatWidget3;
	chatWidget *chatWidget4;
	
};

#endif // CHARTSERVER2_H
