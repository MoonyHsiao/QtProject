#include "FanGraphWidget.h"

#include <math.h>
#include <QDebug>
#include <QKeyEvent>
extern QString userRunPath;


FanGraphWidget::FanGraphWidget(QWidget *parent)
	: QGraphicsView(parent)
{
	QGraphicsScene *scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	//scene->setSceneRect(-200, -200, 400, 400);
	scene->setSceneRect(-140, -140, 280, 280);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	//scale(qreal(0.8), qreal(0.8));
	setMinimumSize(280, 280);


	Lv1 = new FanBall(this);
	Lv1->setBallString("1");
	Lv1->setObjectName("1");
	Lv1->setBallColor_100(0, 143, 0);
	Lv1->setBallColor_0(82, 255, 82);
	Lv2 = new FanBall(this);
	Lv2->setBallColor_100(0, 173, 173);
	Lv2->setBallColor_0(168, 255, 255);
	Lv2->setBallString("2");
	Lv2->setObjectName("2");
	Lv3 = new FanBall(this);
	Lv3->setBallColor_100(204, 0, 0);
	Lv3->setBallColor_0(255, 117, 117);
	Lv3->setBallString("3");
	Lv3->setObjectName("3");
	scene->addItem(Lv1);
	scene->addItem(Lv2);
	scene->addItem(Lv3);

	Lv1->setPos(-50, -50);
	Lv2->setPos(0, -50);
	Lv3->setPos(50, -50);

}

void FanGraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);

	// Shadow
	QRectF sceneRect = this->sceneRect();

	// Fill
	QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());

	gradient.setColorAt(0, QColor(240, 240, 216));
	gradient.setColorAt(1, QColor(240, 240, 216));
	painter->fillRect(rect.intersected(sceneRect), gradient);
	painter->setBrush(Qt::NoBrush);
	//painter->drawRect(sceneRect);

	// Text

	painter->setRenderHint(QPainter::Antialiasing);
	QPen penGreenLight;
	penGreenLight.setCapStyle(Qt::RoundCap);
	penGreenLight.setColor(QColor(106, 106, 104));
	penGreenLight.setWidth(2);
	painter->setPen(penGreenLight);
	painter->drawLine(-110, -100, -110, 100);
	//painter->drawLine(-114, 80, -111, 80);
	//painter->drawLine(-114, 60, -111, 60);
	int ypoint = 80;
	for (size_t i = 0; i < 10; i++)
	{

		painter->drawLine(-114, ypoint, -111, ypoint);
		//qDebug() << "test:" <<  ypoint;
		QRectF rectangle2(-140, ypoint - 5, 20.0, 10.0);
		painter->drawText(rectangle2, Qt::AlignRight, QString::number(i * 10 + 10));
		ypoint -= 20;
	}
	painter->drawLine(-110, 100, 70, 100);

	int xpoint = -90;
	for (size_t i = 0; i < 4; i++)
	{

		painter->drawLine(xpoint, 104, xpoint, 101);
		//qDebug() << "test:" <<  ypoint;
		QRectF rectangle3(xpoint - 10, 110, 20.0, 10.0);
		painter->drawText(rectangle3, Qt::AlignCenter, QString::number(i * 10 + 30));
		xpoint += 45;
	}

	//image
	/*QRectF tempTarget(95.0, 70.0, 19.0, 46.0);
	QRectF tempSource(0.0, 0.0, 38.0, 93.0);
	QImage tempImage(userRunPath + "Image/temp.png");
	painter->drawImage(tempTarget, tempImage, tempSource);
	QRectF fanTarget(-140.0, -140.0, 34.0, 34.0);
	QRectF fanSource(0.0, 0.0, 65.0, 65.0);
	QImage fanImage(userRunPath + "Image/fan.png");
	painter->drawImage(fanTarget, fanImage, fanSource);*/


}

void FanGraphWidget::getItemPoint()
{
	QList<QGraphicsItem *> items = this->items();
	
	QMap<int, QPointF>  landmarks;
	foreach(QGraphicsItem *item, items) {
		if (item != NULL) {
			if (item->type() == FanBall::Type) {  // 自定义 Item
				FanBall *customItem = qgraphicsitem_cast<FanBall*>(item);
				QString balName = customItem->objectName();
				//qDebug() << "LV Name" << balName;
				//qDebug() << "LV"<< balName<<"." << customItem->pos();
				landmarks.insert(balName.toInt(),customItem->pos());
				
			}
		}
	}

	emit emitPos(landmarks);
}
