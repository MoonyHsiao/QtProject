/********************************************************************************
** Form generated from reading UI file 'chartserver2.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTSERVER2_H
#define UI_CHARTSERVER2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartServer2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChartServer2Class)
    {
        if (ChartServer2Class->objectName().isEmpty())
            ChartServer2Class->setObjectName(QStringLiteral("ChartServer2Class"));
        ChartServer2Class->resize(600, 400);
        menuBar = new QMenuBar(ChartServer2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChartServer2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChartServer2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChartServer2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChartServer2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChartServer2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChartServer2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChartServer2Class->setStatusBar(statusBar);

        retranslateUi(ChartServer2Class);

        QMetaObject::connectSlotsByName(ChartServer2Class);
    } // setupUi

    void retranslateUi(QMainWindow *ChartServer2Class)
    {
        ChartServer2Class->setWindowTitle(QApplication::translate("ChartServer2Class", "ChartServer2", 0));
    } // retranslateUi

};

namespace Ui {
    class ChartServer2Class: public Ui_ChartServer2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTSERVER2_H
