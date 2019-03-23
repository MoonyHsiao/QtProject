/********************************************************************************
** Form generated from reading UI file 'chatroomclient.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOMCLIENT_H
#define UI_CHATROOMCLIENT_H

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

class Ui_ChatRoomClientClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChatRoomClientClass)
    {
        if (ChatRoomClientClass->objectName().isEmpty())
            ChatRoomClientClass->setObjectName(QStringLiteral("ChatRoomClientClass"));
        ChatRoomClientClass->resize(600, 400);
        menuBar = new QMenuBar(ChatRoomClientClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChatRoomClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChatRoomClientClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChatRoomClientClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChatRoomClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChatRoomClientClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChatRoomClientClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChatRoomClientClass->setStatusBar(statusBar);

        retranslateUi(ChatRoomClientClass);

        QMetaObject::connectSlotsByName(ChatRoomClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChatRoomClientClass)
    {
        ChatRoomClientClass->setWindowTitle(QApplication::translate("ChatRoomClientClass", "ChatRoomClient", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatRoomClientClass: public Ui_ChatRoomClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOMCLIENT_H
