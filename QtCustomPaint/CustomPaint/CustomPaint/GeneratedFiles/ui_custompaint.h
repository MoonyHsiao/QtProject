/********************************************************************************
** Form generated from reading UI file 'custompaint.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMPAINT_H
#define UI_CUSTOMPAINT_H

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

class Ui_CustomPaintClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CustomPaintClass)
    {
        if (CustomPaintClass->objectName().isEmpty())
            CustomPaintClass->setObjectName(QStringLiteral("CustomPaintClass"));
        CustomPaintClass->resize(1000, 550);
        menuBar = new QMenuBar(CustomPaintClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CustomPaintClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CustomPaintClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CustomPaintClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CustomPaintClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CustomPaintClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CustomPaintClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CustomPaintClass->setStatusBar(statusBar);

        retranslateUi(CustomPaintClass);

        QMetaObject::connectSlotsByName(CustomPaintClass);
    } // setupUi

    void retranslateUi(QMainWindow *CustomPaintClass)
    {
        CustomPaintClass->setWindowTitle(QApplication::translate("CustomPaintClass", "CustomPaint", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CustomPaintClass: public Ui_CustomPaintClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMPAINT_H
