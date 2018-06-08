#include "pinDashBoardWidget.h"
#include <QDebug>


extern QString userRunPath;

pinDashBoardWidget::pinDashBoardWidget(QWidget *parent) :
	QWidget(parent)
{

	QPixmap pm(userRunPath + "Image/dashBoard_White.PNG");
	pmFrameWidth = pm.width()/2;
	pmFrameHeight = pm.height()/2;
	this->resize(pmFrameWidth, pmFrameHeight);
	this->setAutoFillBackground(true);
	
	QPalette pl;
	pl.setBrush(QPalette::Background, pm.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	this->setPalette(pl);
	
}

pinDashBoardWidget::~pinDashBoardWidget() {


}

void pinDashBoardWidget::paintEvent(QPaintEvent *) {

	QColor panColor(102, 51, 0);
	QPainter painter(this);
	painter.setPen(QPen(panColor, 3.5));
	painter.setRenderHint(QPainter::Antialiasing, true);

	painter.drawEllipse(46, 50, 5, 5);
	painter.translate(49, 52);

	QPointF handhour[4] = {
		QPoint(0, -3),
		QPoint(-3, 0),
		QPoint(0, -40),
		QPoint(3, 0)
	};

	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(panColor, Qt::SolidPattern));
	painter.save();
	painter.rotate(pointerNumber);
	painter.drawConvexPolygon(handhour, 4);
	painter.restore();
}

void pinDashBoardWidget::setGeo(int _x, int _y) {

	this->setGeometry(_x, _y, pmFrameWidth, pmFrameHeight);
	this->update();
}

void pinDashBoardWidget::setSamples(double _pointerNumber) {

	//pointerNumber = _pointerNumber;
	pointerNumber = (_pointerNumber - benchMark) / percDeviation *45;
	this->update();
}

void pinDashBoardWidget::setBenchMark(double value) {
	benchMark = value;
}

void pinDashBoardWidget::setPercDeviation(double value) {
	percDeviation = benchMark * value;
}
