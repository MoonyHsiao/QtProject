#include "baseInfoWidget_DashV2.h"
#include <QDebug>


extern QString userRunPath;

baseInfoWidget_DashV2::baseInfoWidget_DashV2(QWidget *parent) :
	baseWidgetV2(parent)
{

	dashBoard = new dashBoardWidget(this);
	dashBoard->setGeo((135 - 110) / 2, 25);
	dashBoard->resize(135, 135);


	lblImageXaxis = (135 - 33) / 2;
	lblImage = new QLabel(this);
	lblImage->setGeometry(lblImageXaxis, 60, 33, 33);
	
}

baseInfoWidget_DashV2::~baseInfoWidget_DashV2() {


}


void baseInfoWidget_DashV2::setWidgetUnit(QString unit) {
	widgetUnit = unit;
}


void baseInfoWidget_DashV2::setlblImage(QString imageLocat) {

	QPixmap image(imageLocat);
	int w = lblImage->width();
	int h = lblImage->height();
	lblImage->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
}

void baseInfoWidget_DashV2::movelblImageYaxis(int y) {
	lblImage->move(lblImageXaxis, y);
}

void baseInfoWidget_DashV2::setWidgetData(float data) {
	QString voltString = "%1 %2";
	
	setWidgetValue(voltString.arg(QString::number(data, 'f', 0), widgetUnit));
}

void baseInfoWidget_DashV2::setWidgetData(QString data)
{
	setWidgetValue(data);
}