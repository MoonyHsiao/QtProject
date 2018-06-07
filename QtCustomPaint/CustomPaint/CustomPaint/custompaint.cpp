#include "custompaint.h"
#include <QDebug>
extern QString userRunPath = "";
QString appName = "../CustomPaint.png";
CustomPaint::CustomPaint(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	userRunPath = QApplication::applicationDirPath() + "/";
	

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
	effDash->dashBoard->setTrafficLightModel(true);
	effDash->setWidgetTitle(tr("DashBoard")); //set DashBoard title
	effDash->setWidgetUnit("%"); //setUnit
	effDash->setlblImage(userRunPath + "/Image/Efficiency.png"); //set Image
	effDash->movelblImageYaxis(60);
	effDash->dashBoard->setBarColor_100(58, 112, 28); //setColor 100%
	effDash->dashBoard->setBarColor_10(124, 182, 2); //setColor 10%
	effDash->dashBoard->setBarColor_0(129, 188, 0); //setColor 0%
	effDash->dashBoard->setUpperBound(100);

	setupDemoInfoTimer();

	clock = new baseInfoWidget_Clock(this);
	clock->setGeo(297, pinGeoY);
	clock->resize(135, 135);
	clock->setWidgetTitle(tr("clock"));

	reSetClock();

	setupClockTimer();
	//QTimer::singleShot(1000, this, SLOT(takeScreenshot()));

}

CustomPaint::~CustomPaint()
{

}

void CustomPaint::demoInfo()
{
	int boolRandon = rand() % 2;
	float VVOut12 = 0;
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
	connect(demoInfoTimer, SIGNAL(timeout()), this, SLOT(demoInfo()), Qt::DirectConnection);
	demoInfoTimer->start();
}

void CustomPaint::setupClockTimer()
{
	clockTimer = new QTimer(this);
	clockTimer->setInterval(100);
	connect(clockTimer, SIGNAL(timeout()), this, SLOT(simulationClock()), Qt::DirectConnection);
	clockTimer->start();
}

void CustomPaint::reSetClock()
{
	clockDataList.clear();
	for (size_t i = 0; i < 360; i++)
	{
		clockDataList.append("0");
	}
}

void CustomPaint::simulationClock()
{
	QDateTime time = QDateTime::currentDateTime();
	QString strTimeBuffer;
	strTimeBuffer = time.toString("hh:mm");
	clock->setClock(strTimeBuffer);

	clockTime += 4;
	clockTime %= 1440;

	//float simulationData = (float)(rand() % 100) / 100;
	float simulationData = (float)(rand() % 70+30) / 100;
	//float simulationData = (float)(rand() % 40 + 60) / 100;

	clockDataList[clockDataIndex] = QString::number(simulationData);

	if (clockDataIndex % 360 == 0) {
		reSetClock();
	}

	clock->setSample(clockDataList);
	clockDataIndex += 1;
	clockDataIndex %= 360;

}


void CustomPaint::takeScreenshot()
{
	/*if (isActiveWindow())
	{
	auto grabbedScreenshot = QWidget::grab();
	grabbedScreenshot.save(screenshotFileName);
	}*/

	auto grabbedScreenshot = QWidget::grab();
	grabbedScreenshot.save(appName);
}

