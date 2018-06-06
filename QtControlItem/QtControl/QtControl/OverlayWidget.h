#pragma once
#include <QtWidgets>

class OverlayWidget : public QWidget
{
	void newParent();
public:
	explicit OverlayWidget(QWidget * parent = {}) : QWidget{ parent } {
		setAttribute(Qt::WA_NoSystemBackground);
		setAttribute(Qt::WA_TransparentForMouseEvents);
		newParent();
	}

protected:
	//! Catches resize and child events from the parent widget
	bool eventFilter(QObject * obj, QEvent * ev) override;
	//! Tracks parent widget changes
	bool event(QEvent* ev) override;
};


class LoadingOverlay : public OverlayWidget
{
public:
	LoadingOverlay(QWidget * parent = {}) : OverlayWidget{ parent } {
		setAttribute(Qt::WA_TranslucentBackground);
	}
	
	
	void setWarningText(QString data);
	QString warningText;
protected:
	void paintEvent(QPaintEvent *) override;
};
