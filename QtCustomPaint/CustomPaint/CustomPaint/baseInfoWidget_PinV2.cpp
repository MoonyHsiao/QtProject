#include "baseInfoWidget_PinV2.h"
#include <QDebug>


extern QString userRunPath;

baseInfoWidget_PinV2::baseInfoWidget_PinV2(QWidget *parent) :
	baseWidgetV2(parent)
{

	pinDashBoard = new pinDashBoardWidget(this);
	pinDashBoard->setGeo((135 - 97) / 2, 30);
}

baseInfoWidget_PinV2::~baseInfoWidget_PinV2() {


}





