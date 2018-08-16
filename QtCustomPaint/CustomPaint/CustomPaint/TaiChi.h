#pragma once
#ifndef TAICHI_H
#define TAICHI_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QLabel>
#include <QStyleOption>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class TaiChi : public QWidget
{
	Q_OBJECT
public:
	explicit TaiChi(int blockNum, float sizeScale, float SquareSize, QWidget *parent = 0);
	~TaiChi();

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *event);
	public slots:
	void pushDefault();
	void setRGB(int r, int g, int b);
signals:
	void lightState(QString);
private:
	int outSidePieSize, penWidth = 1, blockNum = 12, blockSpacing = 30;
	float angle, sizeScale;
	int  insidePieSpacing, SquareSize;
	float getAngle(float, float);
	void setAllBlockCheck(bool state);
	int rValue[13] = { 255,255,255,255,255,255,255,255,255,255,255,255,255 }, gValue[13] = { 255,255,255,255,255,255,255,255,255,255,255,255,255 }, bValue[13] = { 255,255,255,255,255,255,255,255,255,255,255,255,255 };
	bool blockClicked[12];
	void sentLightState();

};

#endif // DASHBOARDWIDGET_H
