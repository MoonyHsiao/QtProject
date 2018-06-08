#ifndef QTCONTROL_H
#define QTCONTROL_H

#include <QtWidgets/QMainWindow>
#include "ui_qtcontrol.h"
#include <QMouseEvent>
#include "QSwitchButton.h"
#include "OverlayWidget.h"
#include "CustomFanWidget.h"
#include "popupWidget.h"
#include <QTranslator>
class QtControl : public QMainWindow
{
	Q_OBJECT

public:
	QtControl(QWidget *parent = 0);
	~QtControl();
	enum TempUnit
	{
		Celsius,
		Fahrenheit
	};

	enum language {
		English,
		Trad_Chinese
	};
	public slots:

	void coverShowSlot();

protected:
	//! Resizes children to fill the extent of this widget
	bool event(QEvent * ev) override;
	//! Keeps the children appropriately sized
	void resizeEvent(QResizeEvent *) override;
	private slots:
	void btnClick();
	void getPosClick();
	void transResult(QMap<int, QPointF>);
	void popUpTempUnit();
	void popUpLanguage();
	void resetLanguage();
	void tempUnitSelected(QStringList data);
	void languageSelected(QStringList data);
private:
	Ui::QtControlClass ui;
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	int  mouseClick_X_Coordinate;
	int  mouseClick_Y_Coordinate;

	void setSize(QObject * obj);
	QLabel* label;
	QLabel* lblPos;
	QTimer* coverChangeTimer;
	QWidget* MainCoverFrame;
	QPushButton *btnGetBallPos;
	QPushButton *btnPopUpTempUnitSelect;
	QPushButton *btnLanguageSelect;
	QSwitchButton *_switch;
	LoadingOverlay *coverOverlay;
	CustomFanWidget *CustomFan;
	popupWidget *tempUnitWidget;
	popupWidget *languageWidget;
	void takeScreenshot(const QString screenshotFileName);
	int globalTempUnit = 0;
	QString tempUnitIndex(int i);
	QString languageIndex(int i);
	QTranslator* translator;
	void changeFont(int language);
	void hiddenCheck();
	int systemLanguage = 0; //語言 0:英文 1:繁中
};

#endif // QTCONTROL_H
