#pragma once
#ifndef BASEINFOWIDGET_CLOCK_H
#define BASEINFOWIDGET_CLOCK_H

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
#include <QTextDocument>
#include <QRadioButton>
class baseInfoWidget_Clock : public QWidget
{
	Q_OBJECT
public:
	baseInfoWidget_Clock(QWidget *parent = 0);
	~baseInfoWidget_Clock();
	void setGeo(int, int);
	QLabel* widgetTitle;
	void setWidgetTitle(QString text);
	QStringList dataList;
	void setSample(QStringList data);
	void setClock(QString time);
	
protected:
	void paintEvent(QPaintEvent *);

	public slots:


private:
	QTextDocument *doc;
	int pmFrameWidth = 0;
	int pmFrameHeight = 0;
	int pointerNumber = 0;
	double benchMark = 12;
	double percDeviation = 0.72;
	QString baseDrawString = "%1:%2";
	QString drawString;
	QString voltString =
		"<span style='font-size:20pt;"
		"font-weight:600;"
		"color:rgb(106,106,102);"
		"'>%1</span>"
		"<span style='font-size:20pt;"
		"font-weight:600;"
		" color:rgb(106,106,102);'"
		"> </span>"
		;

	QString AMPString =
		"<span style='font-size:20pt;"
		"font-weight:600;"
		"color:rgb(106,106,102);"
		"'>%1</span>"
		"<span style='font-size:12pt;"
		"font-weight:600;"
		" color:rgb(106,106,102);'"
		"> A</span>"
		;
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
		;

	QString btnStyleSheet =
		"QPushButton"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(114, 140, 199);"
		"border-radius: 15px;"  //設置邊框具備3個像素的圓角
								//"font-weight: bold;"// 字體設置為加粗
								//"border-image:url(+ userRunLocat + DPSIMAGE/Share/ComputerInfo /123.png);" 
								//"border:none;"
								//"color:rgb(0, 0, 0)};"
		"}"

		"QPushButton:Checked"
		"{"
		"color: rgb(0, 255, 0);"
		"background-color: rgb(255, 0, 0);"
		"border: none;"
		"}"

		"QPushButton:Checked"
		"{"
		"color:black;"
		"border-radius:12px;"
		"background:rgb(255, 0, 0)"
		//"border-image:url(DPSIMAGE/Share/ComputerInfo/AMP.png;"
		"}"

		"QPushButton:hover"
		"{"
		"background: rgb(114, 140, 199);"
		"}"

		"QPushButton:pressed{"
		//"background-color: rgb(255, 0, 0);"
		//"border: none;"
		//"border-image:url(DPSIMAGE/Share/ComputerInfo/AMP.png;"
		"}"

		/*
		"QPushButton:focus"
		"{"
		"border: 1px solid black;"
		"background-color: rgb(0, 0, 255);"
		"}"
		*/

		"QPushButton::menu-indicator:open"
		"{"
		//"image:url(:/meterDayCal/DPSIMAGE/Share/btnArrowRight.png);"
		//"subcontrol-position: right center;"
		//"subcontrol-origin: padding;"
		"}"

		"QPushButton::menu-indicator:closed"
		"{"
		//"image:url(:/meterDayCal/DPSIMAGE/Share/btnArrowRight.png);"
		//"subcontrol-position: right center;"
		//"subcontrol-origin: padding;"
		"}"
		;

	QString tabWidgetStyleSheet =
		"QTabWidget::pane"
		"{"
		"border: 3px solid rgb(0, 0, 0);"
		"border-radius: 3px;}"//外框

		"QTabBar::tab "
		"{"
		"background:rgb(47, 255, 106);"
		"color:rgb(240, 240, 216);"
		"padding:10px;"
		"}"

		"QTabBar:tab:!selected"
		"{"
		"margin: 2px;"
		"color: rgb(0,0,0);"
		"border: 3px solid rgb(0, 0, 0);"
		"}"

		"QTabBar::tab:selected,QTabBar::tab:hover"
		"{"
		//"background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
		//stop : 0 #fafafa, stop: 0.4 #f4f4f4,"
		//stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
		"color: rgb(0,0,0);"
		"background:rgb(240, 240, 216);"
		"}"

		"QWidget#pinFrame"
		"{"
		"background-color:rgb(240, 240, 216);"
		"}"

		//可以只針對裡面設 也可以直接寫在上一層的stylesheet 只要標記好setObjectName即可
		"QLabel#lbl"
		"{"
		//"background: rgb(0, 0, 255);"
		//"gridline-color: rgb(255, 57, 163);"
		"selection-color: rgb(180, 114, 255);"
		"selection-background-color: rgb(255, 187, 209);"
		"background-color: rgb(193, 255, 57);"
		"border: 0px solid rgb(0, 0, 0);"
		"border-radius: 10px;"
		"color: rgb(255, 0, 0);"
		"padding : 0;"
		"margin : 0;"
		"}"
		;

	QString SliBaseStyleSheet =
		"QSlider::groove:horizontal::disabled"
		"{"
		"background:qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 0, stop : 1 rgb(150,150,150), stop : 0 rgb(150,150,150));"
		"border-radius: 4px;"
		"height: 8px;"
		"margin: -4px 6px 0px 6px;"
		"left: 0px;"
		"right: 0px;"
		"}"

		"QSlider::handle:horizontal::disabled"
		"{"
		"border-radius:13px;"
		"background:qradialgradient(cx: 0.5, cy: 0.5,fx : 0.5, fy : 0.5,radius : 0.5,stop : 0.8 rgb(150,150,150), stop: 1 rgba(255,255,255,0.1));"
		"width: 27px;"
		"height: 27px;"
		"margin: -10px -5px -10px -5px;"
		"}"

		"QSlider::groove:horizontal"
		"{"
		"background:qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 0, stop : 1 rgb(%1 , %2, %3), stop : 0 rgb(0,0,0));"
		"border-radius: 4px;"
		"height: 8px;"
		"margin: -4px 6px 0px 6px;"
		"left: 0px;"
		"right: 0px;"
		"}"

		"QSlider::handle:horizontal"
		"{"
		"border-radius:13px;"
		"background:qradialgradient(cx: 0.5, cy: 0.5,fx : 0.5, fy : 0.5,radius : 0.5,stop : 0.8 rgb(%1, %2, %3), stop: 1 rgba(255,255,255,0.1));"
		"width: 27px;"
		"height: 27px;"
		"margin: -10px -5px -10px -5px;"
		"}"

		"QSlider::add-page:qlineargradient{"
		//"background: lightgrey;"
		//"borde-top-right-radius: 9px;"
		//"border-bottom-right-radius: 9px;"
		//"border-top-left-radius: 9px;"
		//"border-bottom-left-radius: 9px;"
		"}"

		"QSlider::sub-page:qlineargradient{"
		//"background: blue;"
		//"border-top-right-radius: 9px;"
		//"border-bottom-right-radius: 9px;"
		//"border-top-left-radius: 9px;"
		//"border-bottom-left-radius: 9px;"
		"}"
		;

	QString SliStyleSheet = SliBaseStyleSheet.arg("255", "0", "0");

	QString radioBtnStyleSheet =
		"QRadioButton"
		"{"
		//"width: 30px;"
		//"height: 30px;"
		"color: rgb(0, 0, 255);"
		"}"

		"QRadioButton:checked" //改字的顏色
		"{"
		"color: rgb(255, 0, 0);"
		"}"

		"QRadioButton:hover" //改字的顏色
		"{"
		//"color: rgb(0, 255, 0);"
		"}"

		"QRadioButton::indicator:checked"
		"{"
		//"width: 25px;"
		//"height: 25px;"
		//"border-image: url(Image/fan.png);"
		//"image: url(DPSIMAGE/Share/ComputerInfo/AMP.png);"
		"}"

		"QRadioButton#Volt::indicator:!checked"
		"{"
		"width: 32px;"
		"height: 25px;"
		"border-image: url(Image/Volt.png);"
		"}"

		"QRadioButton#AMP::indicator:!checked"
		"{"
		"width: 32px;"
		"height: 25px;"
		"border-image: url(Image/AMP.png);"
		"}"

		"QRadioButton::indicator:hover"
		"{"
		//"width: 20px;"
		//"height: 20px;"
		//"border-image: url(Image/fan.png);"
		"}"
		;

	QString cBbStyleSheet =
		"QComboBox"  //外框
		"{"
		//"background: rgb(255, 0, 255);"
		"border: 1px solid gray;"
		"border-radius: 3px;"
		"padding: 0.2em;"
		"color: gray;"
		//"selection-background-color: rgb(255, 0, 0);"
		//"selection-color: rgb(255, 0, 255);"
		"}"

		"QComboBox::hover"
		"{"
		"border-color:#5D8B9E;"
		"}"

		"QComboBox:focus{"
		"border: 1px solid black;"
		"color: black;"
		"}"

		"QComboBox::drop-down"
		"{"
		"min-width: 20px;"
		"max-width: 20px;"
		"margin: -1px;"
		"}"

		"QComboBox::down-arrow"
		"{"
		"image: url(Image/ArrowDown.png);"
		"}"

		"QComboBox::drop-down:focus"
		"{"
		//"border: 1px solid rgb(255,0,0);"
		"}"

		"QComboBox:on{"
		"padding-top: 3px;"
		"padding-left: 4px;"
		"}"

		"QComboBox QAbstractItemView{"
		"border: 2px solid #32435E;"
		//"selection-background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
		//"stop : 0 #506B79,"
		//"stop: 1.0 #0D95A6);"
		"selection-background-color: rgb(255, 0, 0);"
		//"background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
		//"stop : 0 #1B2534, stop: 0.4 #010101,"
		//"stop: 0.5 #000101, stop: 1.0 #1F2B3C);"
		"background: rgb(0, 255, 0);"
		"}"
		;


	QString QListWidgetStyleSheet =
		"QListWidget"
		"{"
		"background-color: rgb(255, 0, 0);"
		"border:solid;"
		//"background:transparent;"
		"}"

		"QListWidget::item:selected"
		"{"
		"background:yellow;"
		"color:red;"
		"}"

		"QListWidget::item:hover"
		"{"
		"background-color:rgb(0,142,250);"
		"}"

		"QListWidget::item"
		"{"
		"border-style: solid;"
		"height:50px;"
		"border-radius:5px;"
		"border-width:1px;"
		"border-color:rgb(128, 128, 128);"
		"background-color: rgb(51, 51, 51);"
		"color:rgba(51,51,51,0);"
		"}"

		"QScrollBar:vertical"
		"{"
		"border: solid;"
		"background:rgb(51,51,51);"
		"width:15px;"
		"margin: 0px 0px 0px 0px;"
		"}"

		"QScrollBar::handle:vertical"
		"{"
		"background:rgb(100,100,100);"
		"min-height: 15px;"
		"}"

		"QScrollBar::add-line:vertical"
		"{"
		"background:rgb(0,255,0);"
		"height: 0px;"
		"subcontrol-position: bottom;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::sub-line:vertical"
		"{"
		"background:rgb(0,0,255);"
		"height: 0px;"
		"subcontrol-position: top;"
		"subcontrol-origin: margin;"
		"}"
		;



	QString WidgetStyleSheet =
		"QWidget#shadowFrame"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: 5px;"  //設置邊框具備3個像素的圓角
								//"font-weight: bold;"  // 字體設置為加粗
								//"border-image:url(+userRunLocat+DPSIMAGE/Share/Background.PNG)};"
		"}";

	QString menuStyleSheet =
		"QMenu"
		"{"
		"background-color: white;"
		"padding: 1px;"  // 缩小菜单项四个方向的padding
		"font: 90 12pt \"MS PGothic\";"
		"}"

		//padding-top:15px;
		//padding-right:10px;
		//padding-bottom:30px;
		//padding-left:40px; 
		//padding: 1px;
		"QMenu::item"
		"{"
		//"spacing: 30px;"
		"padding: 20px 20px 20px 20px;"
		"backgroun-color: transparent;"
		"font: 90 14pt \"MS PGothic\";"
		"}"

		"QMenu::item:selected"
		"{"
		"background-color: rgb(0, 243, 253);"
		"color: black;"
		"}";

#pragma endregion StyleSheet
};

#endif // DASHBOARDWIDGET_H
