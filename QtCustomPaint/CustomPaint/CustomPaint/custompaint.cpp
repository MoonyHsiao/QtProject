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

#pragma region V1
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
#pragma endregion V1
	setupDemoInfoTimer();

	clock = new baseInfoWidget_Clock(this);
	clock->setGeo(297, pinGeoY);
	clock->resize(135, 135);
	clock->setWidgetTitle(tr("clock"));

	reSetClock();
	setupClockTimer();
	
	v2 = new baseInfoWidget_PinV2(this);
	v2->setGeo(5, pinGeoY+200);
	v2->resize(135, 135);
	v2->setWidgetTitle("PinDashV2");


	effDashV2 = new baseInfoWidget_DashV2(this);
	effDashV2->setGeo(151, pinGeoY+200);
	effDashV2->resize(135, 135);
	effDashV2->dashBoard->setTrafficLightModel(true);
	effDashV2->setWidgetTitle(tr("DashBoard")); //set DashBoard title
	effDashV2->setWidgetUnit("%"); //setUnit
	effDashV2->setlblImage(userRunPath + "/Image/Efficiency.png"); //set Image
	effDashV2->movelblImageYaxis(60);
	effDashV2->dashBoard->setBarColor_100(58, 112, 28); //setColor 100%
	effDashV2->dashBoard->setBarColor_10(124, 182, 2); //setColor 10%
	effDashV2->dashBoard->setBarColor_0(129, 188, 0); //setColor 0%
	effDashV2->dashBoard->setUpperBound(100);
	effDashV2->setWidgetValueGeometry((135 - 60)/2, 110, 60, 20);
	

	int Taichisize = 250;
	LED12 = new TaiChi(12, 0.8, Taichisize, this);
	LED12->setGeometry(500, 50, Taichisize, Taichisize);
	int Taichisize2 = 150;
	LED6 = new TaiChi(6, 0.9, Taichisize2, this);
	LED6->setGeometry(500, 300, Taichisize2, Taichisize2);

	
	RGBPaletteWidget *RGBPalette;
	QString image = userRunPath + "Image/palette.png";
	int RGBPaletteSize = 150;
	RGBPalette = new RGBPaletteWidget(image, RGBPaletteSize, this);
	RGBPalette->setGeometry(60, 350, RGBPaletteSize, RGBPaletteSize);
	connect(RGBPalette, SIGNAL(returnRGBValue(int, int, int)), LED12, SLOT(setRGB(int, int, int)));
	connect(LED6, SIGNAL(lightState(QString)), this, SLOT(getLightState(QString)));
	connect(RGBPalette, SIGNAL(returnRGBValue(int, int, int)), LED6, SLOT(setRGB(int, int, int)));

	QTimer::singleShot(3000, this, SLOT(takeScreenshot()));
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
	v2->pinDashBoard->setSamples(VVOut12);


	float EFF = rand() % 100;
	effDash->dashBoard->setSamples(EFF);
	effDash->setWidgetData(effDashWidgetString.arg(QString::number(EFF, 'f', 0)));

	effDashV2->dashBoard->setSamples(EFF);
	effDashV2->setWidgetData(effDashWidgetString.arg(QString::number(EFF, 'f', 0)));
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
	float simulationData = (float)(rand() % 70 + 30) / 100;
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

void CustomPaint::getLightState(QString data)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (jsonDocument.isObject()) {
			QVariantMap result = jsonDocument.toVariant().toMap();
			int commandType = result["command"].toInt();
			if (commandType == 0) {
				QVariantMap resultData;
				resultData = result["Data"].toMap();
				QStringList LED = resultData["LED"].toStringList();
				QStringList rColor = resultData["rColor"].toStringList();
				QStringList gColor = resultData["gColor"].toStringList();
				QStringList bColor = resultData["bColor"].toStringList();
			}
		}
	}
}