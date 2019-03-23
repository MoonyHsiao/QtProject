/********************************************************************************
** Form generated from reading UI file 'chatroomserver.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOMSERVER_H
#define UI_CHATROOMSERVER_H

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

class Ui_ChatRoomServerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChatRoomServerClass)
    {
        if (ChatRoomServerClass->objectName().isEmpty())
            ChatRoomServerClass->setObjectName(QStringLiteral("ChatRoomServerClass"));
        ChatRoomServerClass->resize(600, 400);
        menuBar = new QMenuBar(ChatRoomServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChatRoomServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChatRoomServerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChatRoomServerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChatRoomServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChatRoomServerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChatRoomServerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChatRoomServerClass->setStatusBar(statusBar);

        retranslateUi(ChatRoomServerClass);

        QMetaObject::connectSlotsByName(ChatRoomServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChatRoomServerClass)
    {
        ChatRoomServerClass->setWindowTitle(QApplication::translate("ChatRoomServerClass", "ChatRoomServer", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatRoomServerClass: public Ui_ChatRoomServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOMSERVER_H
