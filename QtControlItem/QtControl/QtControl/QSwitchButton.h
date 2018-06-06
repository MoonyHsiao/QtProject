#pragma once
#include <QtWidgets>



class QSwitchButton : public QAbstractButton {
	Q_OBJECT
		Q_PROPERTY(int offset READ offset WRITE setOffset)
		Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
	QSwitchButton(QWidget* parent = nullptr);
	void setBrush(const QBrush &brsh);
	
	bool switchState();
protected:
	void paintEvent(QPaintEvent*) override;
	void mouseReleaseEvent(QMouseEvent*) override;
	void enterEvent(QEvent*) override;

private:
	bool _switch;
	qreal _opacity;
	int _x, _y, _height, _margin;
	QBrush _thumb, _track, _brush;
	QPropertyAnimation *_anim = nullptr;
	QSize sizeHint() const override;
	QBrush brush() const {
		return _brush;
	}
	
	int offset() const {
		return _x;
	}
	void setOffset(int o);
};