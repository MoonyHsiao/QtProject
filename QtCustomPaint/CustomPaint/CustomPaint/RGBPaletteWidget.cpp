#include "RGBPaletteWidget.h"
#include <QDebug>
//extern QString userRunPath;

#define PI 3.14159265
RGBPaletteWidget::RGBPaletteWidget(QString imageLocat, float SquareSize, QWidget *parent) :
	QWidget(parent), SquareSize(SquareSize), imageLocat(imageLocat)
{
	this->resize(SquareSize, SquareSize);

	QString WidgetStyleSheet =
		"QWidget#shadowFrame"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: %1;"
		"}";
	setStyleSheet(WidgetStyleSheet.arg(SquareSize / 2));
	setObjectName(QStringLiteral("shadowFrame"));


	QImage img(imageLocat);
	pixScale = img.width() / SquareSize;

	/*qDebug() << " img.width():"<< img.width();
	qDebug() << " SquareSize:" << SquareSize;
	qDebug() << " pixScale:" << pixScale;*/

}

RGBPaletteWidget::~RGBPaletteWidget() {
}

void RGBPaletteWidget::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		x = event->x();
		y = event->y();
		//QImage img(userRunPath + "Image/RGB/palette.png");
		QImage img(imageLocat);
		//QColor clrCurrent(img.pixel(event->x()*pixScale, event->y()*pixScale));
		QColor clrCurrent(img.pixel(x * pixScale, y * pixScale));
		int currentR = clrCurrent.red();
		int currentG = clrCurrent.green();
		int currentB = clrCurrent.blue();
		emit returnRGBValue(currentR, currentG, currentB);
		update();
	}
}

void RGBPaletteWidget::paintEvent(QPaintEvent *) {

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QPixmap pixmap(imageLocat);
	p.drawPixmap(0, 0, SquareSize, SquareSize, pixmap.scaled(SquareSize, SquareSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	//painter.drawPixmap(0, 0, newPixmap.scaled(pixScale, pixScale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	p.setPen(Qt::black); //指定畫筆顏色
	p.drawEllipse(x, y, 10, 10);
}











