#pragma once
#ifndef RGBPALETTEWIDGET_H
#define RGBPALETTEWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QLabel>
#include <QStyleOption>

class RGBPaletteWidget : public QWidget
{

	Q_OBJECT
public:
	explicit RGBPaletteWidget(QString imageLocat, float SquareSize, QWidget *parent = 0);
	~RGBPaletteWidget();
	
	public slots:

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *event);
signals:
	void returnRGBValue(int r, int g, int b);
	
private:
	float SquareSize = 0, pixScale = 0;
	QString imageLocat;
	int x = 50, y = 50;
	
};

#endif // DASHBOARDWIDGET_H
