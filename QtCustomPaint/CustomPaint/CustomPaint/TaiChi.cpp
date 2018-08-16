#include "TaiChi.h"
#include <QDebug>


extern QString userRunPath;
#define PI 3.14159265

TaiChi::TaiChi(int blockNum, float sizeScale, float SquareSize, QWidget *parent) :
	QWidget(parent), blockNum(blockNum), sizeScale(sizeScale), SquareSize(SquareSize)
{

	QString WidgetStyleSheet =
		"QWidget#shadowFrame"
		"{"
		"background: rgb(240, 240, 216);"
		"border: 1px solid rgb(204, 204, 204);"
		"border-radius: %1;"
		"}";
	setStyleSheet(WidgetStyleSheet.arg(SquareSize / 2));
	setObjectName(QStringLiteral("shadowFrame"));


	this->setAutoFillBackground(true);
	this->resize(SquareSize, SquareSize);

	QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect;
	bodyShadow->setBlurRadius(9.0);
	bodyShadow->setColor(QColor(0, 0, 0, 100));
	bodyShadow->setOffset(2.0);
	setGraphicsEffect(bodyShadow);


	blockSpacing = 360 / blockNum;
	outSidePieSize = SquareSize - 2 * penWidth;
	//sizeScale = 0.7;
	insidePieSpacing = outSidePieSize * (1 - sizeScale) / 2 + penWidth;

	pushDefault();

	setAllBlockCheck(false);


}

TaiChi::~TaiChi() {


}

void TaiChi::pushDefault()
{
	rValue[0] = 0;
	gValue[0] = 127;
	bValue[0] = 255;

	rValue[1] = 0;
	gValue[1] = 255;
	bValue[1] = 255;


	rValue[2] = 0;
	gValue[2] = 255;
	bValue[2] = 127;


	rValue[3] = 0;
	gValue[3] = 255;
	bValue[3] = 0;


	rValue[4] = 127;
	gValue[4] = 255;
	bValue[4] = 0;


	rValue[5] = 255;
	gValue[5] = 255;
	bValue[5] = 0;


	rValue[6] = 255;
	gValue[6] = 127;
	bValue[6] = 0;


	rValue[7] = 255;
	gValue[7] = 0;
	bValue[7] = 0;


	rValue[8] = 255;
	gValue[8] = 0;
	bValue[8] = 127;


	rValue[9] = 255;
	gValue[9] = 0;
	bValue[9] = 255;


	rValue[10] = 127;
	gValue[10] = 0;
	bValue[10] = 255;


	rValue[11] = 0;
	gValue[11] = 0;
	bValue[11] = 255;


	rValue[12] = 255;
	gValue[12] = 0;
	bValue[12] = 0;

}

void TaiChi::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	p.setRenderHint(QPainter::Antialiasing);

	QRectF rectangle_OutSidePie(penWidth, penWidth, outSidePieSize, outSidePieSize);

	//QRectF rectangle_OutSidePie(1, 1, SquareSize-2, SquareSize-2);
	//QRectF rectangle_OutSidePie(penWidth, penWidth, SquareSize, SquareSize);
	QPen pen_OutSidePie;
	pen_OutSidePie.setCapStyle(Qt::RoundCap);
	pen_OutSidePie.setWidth(penWidth);


	//p.drawPie(45, 20, 50, 50, -90 * 16, usedValue * 16);
	//for (size_t i = 0; i < 12; i++) {
	for (size_t i = 0; i < blockNum; i++) {
		//blockNum
		QColor outSidePieColor(rValue[i], gValue[i], bValue[i]);
		QColor outSidePieColor2(255, 255, 255);

		if (blockClicked[i])
		{
			outSidePieColor2.setRgb(0, 0, 0);
		}
		pen_OutSidePie.setColor(outSidePieColor2);
		QBrush brush2(outSidePieColor);
		p.setBrush(brush2);
		p.setPen(pen_OutSidePie);
		//p.drawPie(rectangle_OutSidePie, (0 + i * 30) * 16, 29 * 16);
		p.drawPie(rectangle_OutSidePie, (0 + i * blockSpacing) * 16, (blockSpacing - 1) * 16);
	}

	//blockSpacing

	QRectF rectangle_InSidePie(insidePieSpacing, insidePieSpacing, outSidePieSize*sizeScale, outSidePieSize*sizeScale);
	QPen pen_InSidePie;
	QColor inSidePieColor(240, 240, 216);
	pen_InSidePie.setColor(inSidePieColor);
	QBrush brush(inSidePieColor);
	p.setBrush(brush);
	p.setPen(pen_InSidePie);
	p.drawPie(rectangle_InSidePie, 0 * 16, 360 * 16);

}

void TaiChi::mousePressEvent(QMouseEvent *event) {

	if (event->button() == Qt::LeftButton)
	{
		double xSquare = pow((event->x() - SquareSize / 2), 2);
		double ySquare = pow((event->y() - SquareSize / 2), 2);
		double boundary = sqrt(xSquare + ySquare) / (SquareSize / 2);
		if (boundary >= sizeScale && boundary <= 1.0) {
			QString locat = "you are in :%1 ";
			//qDebug() << "locat:" << locat.arg(boundary);
			float angle = getAngle(event->x(), event->y());
			int index = angle / blockSpacing;

			if (blockClicked[index]) blockClicked[index] = false;
			
			else blockClicked[index] = true;
			

			update();
			//qDebug() << "Angle: " << aaa;
		}
	}
}

void TaiChi::setRGB(int r, int g, int b)
{

	//for (size_t i = 0; i < 12; i++)
	for (size_t i = 0; i < blockNum; i++)
	{
		if (blockClicked[i]) 
		{
			rValue[i] = r;
			gValue[i] = g;
			bValue[i] = b;
			update();
		}
	}
	sentLightState();
}

float TaiChi::getAngle(float xPosition, float yPosition)
{
	double distance, result;
	distance = (yPosition - SquareSize / 2) / (xPosition - SquareSize / 2);;
	result = -(atan(distance) * 180 / PI);

	if (xPosition <= SquareSize / 2) result += 180;
	else if (xPosition >= SquareSize / 2 && yPosition >= SquareSize / 2) result += 360;

	return result;
}

void TaiChi::setAllBlockCheck(bool state)
{

	//for (size_t i = 0; i < 12; i++)
	for (size_t i = 0; i < blockNum; i++)
	{
		blockClicked[i] = state;
	}
}

void TaiChi::sentLightState()
{
	QJsonObject data_json_obj;

	QJsonArray rValue_Init;
	QJsonArray gValue_Init;
	QJsonArray bValue_Init;
	QJsonArray lightChecked;

	for (int i = 0; i < blockNum; i++) {

		rValue_Init.insert(i, rValue[i]);
		gValue_Init.insert(i, gValue[i]);
		bValue_Init.insert(i, bValue[i]);
		lightChecked.insert(i, blockClicked[i]);
	}


	data_json_obj.insert("rColor", rValue_Init);
	data_json_obj.insert("gColor", gValue_Init);
	data_json_obj.insert("bColor", bValue_Init);
	data_json_obj.insert("LED", lightChecked);
	
	QJsonObject command_json_obj;
	command_json_obj.insert("command", "0");
	command_json_obj.insert("Data", data_json_obj);
	QJsonDocument doc(command_json_obj);
	QString result(doc.toJson());
	//qDebug() << "string1: " << string1;
	emit lightState(result);
}

