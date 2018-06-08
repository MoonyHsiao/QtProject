#pragma 
#ifndef FANGRAPHWIDGET_H
#define FANGRAPHWIDGET_H

#include <QGraphicsView>
#include <QStyleOption>
#include "FanBall.h"

class FanBall;

class FanGraphWidget : public QGraphicsView
{
	Q_OBJECT

public:
	FanGraphWidget(QWidget *parent = 0);
	void getItemPoint();
	
	public slots:
	
signals:
	void emitPos(QMap<int, QPointF>);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	
private:
	FanBall *Lv1;
	FanBall *Lv2;
	FanBall *Lv3;
	
};

#endif // GRAPHWIDGET_H