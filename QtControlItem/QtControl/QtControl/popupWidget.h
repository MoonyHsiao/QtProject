#pragma once
#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H



#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QTimer>
#include <QAbstractAnimation>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QButtonGroup>
class popupWidget : public QWidget
{
	Q_OBJECT
public:
	explicit popupWidget(QPushButton* button, QWidget *parent = 0);
	~popupWidget();
	void initFunctionName(QString Name);
	void initSize(int w, int h);
	void initFuntionbtn(int btnNum, QStringList btnName);
	void startAmin();
	QPropertyAnimation *anim;
	QLabel *lblFunctionTitle;
	void setMove(int x, int y);
	void setBtnSize(int width, int height);
	QButtonGroup *controllerGroup;
	void initBtnSelect(QString Name);
	void resetLanguage();
	bool nonHidden = false;
	void setNonHidden(bool state);
	void setItemDisable(QStringList btnName);
	void setItemEnable();
	QString getSelectName();
protected:
	void paintEvent(QPaintEvent *);
	
	void showEvent(QShowEvent* event);
public slots:
	void functionSelected();
	
signals:
	void returnSelectFunction(QStringList);

private:
	QPushButton* b;
	QStringList btn_qobject_cast;
	int thisWidth = 0;
	int thisHeight = 0;
	int functionCount = 0;
	int moveWidth = 0;
	int moveHeight = 0;
	QSize btnSize;
	QPoint movePoint;
#pragma region StyleSheet
	QString WidgetStyleSheet =
		"QWidget"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: 5px;"  //設置邊框具備3個像素的圓角
		//"font-weight: bold;"  // 字體設置為加粗
		"}";

	QString labelStyleSheet =
		"QLabel"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 2px solid rgb(240, 240, 216);"
		//"border-radius: 10px;"  
		//"font-weight: bold;"
		"}";

	QString btnStyleSheet =
		"QPushButton"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(114, 140, 199);"
		"border-radius: 6px;"
		//"image:url(Image/Arrow.png)10 20 30 40 stretch stretch;"
		//"font-weight: bold;"
		"}"

		"QPushButton:hover{"
		"background: rgb(114, 140, 199);"
		//"border-image:url(Image/Arrow.png);"
		"}"
		
		"QPushButton:Checked"
		"{"
		"background: rgb(114, 140, 199);"
		//"border-image:url(Image/Arrow.png);"
		"}"
		"QPushButton:disabled"
		"{"
		"background: rgb(102, 102, 102);"
		
		"}"
		;

#pragma endregion StyleSheet
};

#endif // PIEWIDGET_H
