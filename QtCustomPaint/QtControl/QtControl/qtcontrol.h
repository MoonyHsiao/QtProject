#ifndef QTCONTROL_H
#define QTCONTROL_H

#include <QtWidgets/QMainWindow>
#include "ui_qtcontrol.h"
#include <QMouseEvent>
#include "QSwitchButton.h"
#include "OverlayWidget.h"
#include "CustomFanWidget.h"
class QtControl : public QMainWindow
{
	Q_OBJECT

public:
	QtControl(QWidget *parent = 0);
	~QtControl();

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
	QSwitchButton *_switch;
	LoadingOverlay *coverOverlay;
	CustomFanWidget *CustomFan;
	void takeScreenshot(const QString screenshotFileName);

};

#endif // QTCONTROL_H
