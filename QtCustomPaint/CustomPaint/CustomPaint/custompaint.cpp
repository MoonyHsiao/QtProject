#include "custompaint.h"

extern QString userRunPath = "";
CustomPaint::CustomPaint(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	userRunPath = QApplication::applicationDirPath() + "/"; //���o�ϥΪ̶]�o���{������m

	int pinGeoY = (270 + 22);
	pinGeoY = 10;
	pinV12 = new baseInfoWidget_Pin(this);
	pinV12->setGeo(5, pinGeoY);
	pinV12->resize(135, 135);
	pinV12->setWidgetTitle("pinDash");
	pinV12->pinDashBoard->setBenchMark(12);
	pinV12->pinDashBoard->setPercDeviation(0.06);

	effDash = new baseInfoWidget_Dash(this);
	effDash->setGeo(151, pinGeoY);
	effDash->resize(135, 135);
	effDash->dashBoard->setTrafficLightModel(true); //�]�w����O�Ҧ�
	effDash->setWidgetTitle(tr("DashBoard")); //�]�wDashBoard���D
	effDash->setWidgetUnit("%"); //�]�w�ƭȳ��
	effDash->setlblImage(userRunPath + "/Image/Efficiency.png"); //�]�w�ϥ�
	effDash->movelblImageYaxis(60); //�]�w�ϥܪ�����
	effDash->dashBoard->setBarColor_100(58, 112, 28); //�]�w�C�� 100%
	effDash->dashBoard->setBarColor_10(124, 182, 2); //�]�w�C�� 10%
	effDash->dashBoard->setBarColor_0(129, 188, 0); //�]�w�C�� 0%
	effDash->dashBoard->setUpperBound(100); //�]�w�ƭȤW��

	setupDemoInfoTimer();
}

CustomPaint::~CustomPaint()
{

}

void CustomPaint::demoInfo()
{
	int boolRandon = rand() % 2;
	float VVOut12=0;
	if (boolRandon == 0) {
		VVOut12 = 12 + (rand() % 50)*0.01;
	}
	else {
		VVOut12 = 12 - (rand() % 50)*0.01;
	}

	
	pinV12->pinDashBoard->setSamples(VVOut12);
	


	float EFF = rand() % 100;
	effDash->dashBoard->setSamples(EFF);
	effDash->setWidgetData(effDashWidgetString.arg(QString::number(EFF, 'f', 0)));
}

void CustomPaint::setupDemoInfoTimer()
{
	demoInfoTimer = new QTimer(this);
	demoInfoTimer->setInterval(1000);
	//demoInfoTimer->setInterval(10);
	connect(demoInfoTimer, SIGNAL(timeout()), this, SLOT(demoInfo()), Qt::DirectConnection);
	demoInfoTimer->start();
}
