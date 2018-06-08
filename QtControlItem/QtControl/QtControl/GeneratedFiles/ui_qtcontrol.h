/********************************************************************************
** Form generated from reading UI file 'qtcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCONTROL_H
#define UI_QTCONTROL_H

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

class Ui_QtControlClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtControlClass)
    {
        if (QtControlClass->objectName().isEmpty())
            QtControlClass->setObjectName(QStringLiteral("QtControlClass"));
        QtControlClass->resize(600, 400);
        menuBar = new QMenuBar(QtControlClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtControlClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtControlClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtControlClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtControlClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtControlClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtControlClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtControlClass->setStatusBar(statusBar);

        retranslateUi(QtControlClass);

        QMetaObject::connectSlotsByName(QtControlClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtControlClass)
    {
        QtControlClass->setWindowTitle(QApplication::translate("QtControlClass", "QtControl", 0));
    } // retranslateUi

};

namespace Ui {
    class QtControlClass: public Ui_QtControlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCONTROL_H
