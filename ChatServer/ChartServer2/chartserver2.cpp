#include "chartserver2.h"
#include <QGroupBox>
#include <QVBoxLayout>

ChartServer2::ChartServer2(QWidget *parent, Qt::WindowFlags f)
	: QToolBox(parent, f)
{
	//ui.setupUi(this);
	setWindowTitle(tr("MSN 2019"));                  
	setWindowIcon(QPixmap("Image/message.png"));         

	toolBtn1 = new QToolButton;
	toolBtn1->setText(tr("RockMan"));
	toolBtn1->setIcon(QPixmap("Image/rockman.png"));
	//toolBtn1->setIconSize(QPixmap("Image/rockman.png").size());
	toolBtn1->setIconSize(QSize(80,80));
	toolBtn1->setAutoRaise(true);
	toolBtn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	connect(toolBtn1, SIGNAL(clicked()), this, SLOT(showChatWidget1()));

	toolBtn2 = new QToolButton;
	toolBtn2->setText(tr("Goku"));
	toolBtn2->setIcon(QPixmap("Image/goku.png"));
	toolBtn2->setIconSize(QPixmap("Image/goku.png").size());
	toolBtn2->setIconSize(QSize(80, 80));
	toolBtn2->setAutoRaise(true);
	toolBtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	connect(toolBtn2, SIGNAL(clicked()), this, SLOT(showChatWidget2()));

	toolBtn3 = new QToolButton;
	toolBtn3->setText(tr("Shin"));
	toolBtn3->setIcon(QPixmap("Image/shin.png"));
	toolBtn3->setIconSize(QPixmap("Image/shin.png").size());
	toolBtn3->setIconSize(QSize(80, 80));
	toolBtn3->setAutoRaise(true);
	toolBtn3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	connect(toolBtn3, SIGNAL(clicked()), this, SLOT(showChatWidget3()));

	toolBtn4 = new QToolButton;
	toolBtn4->setText(tr("Zero"));
	toolBtn4->setIcon(QPixmap("Image/zero.png"));
	toolBtn4->setIconSize(QPixmap("Image/zero.png").size());
	toolBtn4->setIconSize(QSize(80, 80));
	toolBtn4->setAutoRaise(true);
	toolBtn4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	connect(toolBtn4, SIGNAL(clicked()), this, SLOT(showChatWidget4()));

	
	QGroupBox *groupBox = new QGroupBox;
	QVBoxLayout *layout = new QVBoxLayout(groupBox);
	layout->setMargin(20);
	layout->setAlignment(Qt::AlignLeft);
	layout->addWidget(toolBtn1);
	layout->addWidget(toolBtn2);
	layout->addWidget(toolBtn3);
	layout->addWidget(toolBtn4);
	layout->addStretch();//插入一个占位符

	this->addItem((QWidget*)groupBox, tr("聊天室成員"));
}

ChartServer2::~ChartServer2()
{

}

void ChartServer2::showChatWidget1()
{
	chatWidget1 = new chatWidget(0, toolBtn1->text());
	chatWidget1->setWindowTitle(toolBtn1->text());
	chatWidget1->setWindowIcon(toolBtn1->icon());
	chatWidget1->show();
}

void ChartServer2::showChatWidget2()
{
	chatWidget2 = new chatWidget(0, toolBtn2->text());
	chatWidget2->setWindowTitle(toolBtn2->text());
	chatWidget2->setWindowIcon(toolBtn2->icon());
	chatWidget2->show();
}

void ChartServer2::showChatWidget3()
{
	chatWidget3 = new chatWidget(0, toolBtn3->text());
	chatWidget3->setWindowTitle(toolBtn3->text());
	chatWidget3->setWindowIcon(toolBtn3->icon());
	chatWidget3->show();
}

void ChartServer2::showChatWidget4()
{
	chatWidget4 = new chatWidget(0, toolBtn4->text());
	chatWidget4->setWindowTitle(toolBtn4->text());
	chatWidget4->setWindowIcon(toolBtn4->icon());
	chatWidget4->show();
}


