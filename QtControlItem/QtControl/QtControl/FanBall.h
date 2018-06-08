#pragma once
#ifndef FANBALL_H
#define FANBALL_H

#include <QGraphicsItem>
#include <QList>
#include "FanGraphWidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

class QGraphicsSceneMouseEvent;

class FanGraphWidget;

class FanBall : public QObject , public QGraphicsItem
{
	
public:
	FanBall(FanGraphWidget *graphWidget);
	enum { Type = UserType + 1 };
	int type() const override { return Type; }
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setBallString(QString data);
	void setBallNameColor(int r, int g, int b);
	void setBallColor_100(int r, int g, int b);
	void setBallColor_0(int r, int g, int b);
	
	
protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
	QPointF newPos;
	FanGraphWidget *graph;
	QString ballName = "";
	int ballNameColor_R = 255, ballNameColor_G = 255, ballNameColor_B = 255;
	int ballColor100_R = 0, ballColor100_G = 143, ballColor100_B = 0;
	int ballColor0_R = 82, ballColor0_G = 255, ballColor0_B = 82;
	bool m_dragValid;
};

#endif // NODE_H