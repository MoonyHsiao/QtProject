
#include "FanGraphWidget.h"

#include "FanBall.h"
#include <QDebug>

FanBall::FanBall(FanGraphWidget *graphWidget)
	: graph(graphWidget)
{
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

QRectF FanBall::boundingRect() const
{
	qreal adjust = 2;
	return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath FanBall::shape() const
{
	QPainterPath path;
	path.addEllipse(-10, -10, 20, 20);
	return path;
}

void FanBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(180, 180, 180));
	//painter->drawEllipse(-7, -7, 20, 20);
	painter->drawEllipse(-10, -10, 23, 23);

	QColor ballColor_100(ballColor100_R, ballColor100_G, ballColor100_B);
	QColor ballColor_0(ballColor0_R, ballColor0_G, ballColor0_B);
	QRadialGradient gradient(-3, -3, 10);
	if (option->state & QStyle::State_Sunken) {
		gradient.setCenter(3, 3);
		gradient.setFocalPoint(3, 3);
		gradient.setColorAt(1, ballColor_0.light(120));
		gradient.setColorAt(0, ballColor_100.light(120));
	}
	else {
		gradient.setColorAt(0, ballColor_0);
		gradient.setColorAt(1, ballColor_100);
	}
	painter->setBrush(gradient);
	//painter->drawEllipse(-10, -10, 20, 20);
	painter->drawEllipse(-13, -13, 23, 23);

	QColor ballNameColor(ballNameColor_R, ballNameColor_G, ballNameColor_B);
	painter->setPen(QPen(ballNameColor, 0));
	//painter->setPen(Qt::NoPen);
	//qDebug() << "ballName:" << ballName;
	painter->drawText(-4, 2, ballName);

}

void FanBall::setBallString(QString data)
{
	ballName = data;
}

void FanBall::setBallNameColor(int r, int g, int b)
{
	ballNameColor_R = r;
	ballNameColor_G = g;
	ballNameColor_B = b;
	this->update();
}

void FanBall::setBallColor_100(int r, int g, int b)
{
	ballColor100_R = r;
	ballColor100_G = g;
	ballColor100_B = b;
	this->update();
}

void FanBall::setBallColor_0(int r, int g, int b)
{
	ballColor0_R = r;
	ballColor0_G = g;
	ballColor0_B = b;
	this->update();
}


QVariant FanBall::itemChange(GraphicsItemChange change, const QVariant &value)
{
	
	QPointF itemPoint = value.toPointF();
	
	if (itemPoint.x() >= -110 && itemPoint.x() <= 90 && itemPoint.y() >= -100 && itemPoint.y() <= 100) {
		//qDebug() << "in range: " << itemPoint;
		
		switch (change) {
		case ItemPositionHasChanged:

			break;
		default:
			break;
		};

		return QGraphicsItem::itemChange(change, value);
	}
	else {
		return 0;
	}
}

void FanBall::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

	//qDebug() << "update?";
	//update();
	//QGraphicsItem::mousePressEvent(event);

	if (shape().contains(event->pos()))
	{
		QGraphicsItem::mousePressEvent(event);
		m_dragValid = true;
		update();
	}
	else
		event->ignore();

}

void FanBall::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{


	if (m_dragValid) {
		update();
		QGraphicsItem::mouseReleaseEvent(event);
	}
	else
		event->ignore();

	m_dragValid = false;
}

void FanBall::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_dragValid)
		QGraphicsItem::mouseMoveEvent(event);
	else
		event->ignore();
}