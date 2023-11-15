/********************************************************************************
** Form generated from reading UI file 'stockmarket.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKMARKET_H
#define UI_STOCKMARKET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StockMarket
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StockMarket)
    {
        if (StockMarket->objectName().isEmpty())
            StockMarket->setObjectName(QString::fromUtf8("StockMarket"));
        StockMarket->resize(400, 300);
        centralwidget = new QWidget(StockMarket);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        StockMarket->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StockMarket);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 17));
        StockMarket->setMenuBar(menubar);
        statusbar = new QStatusBar(StockMarket);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StockMarket->setStatusBar(statusbar);

        retranslateUi(StockMarket);

        QMetaObject::connectSlotsByName(StockMarket);
    } // setupUi

    void retranslateUi(QMainWindow *StockMarket)
    {
        StockMarket->setWindowTitle(QCoreApplication::translate("StockMarket", "StockMarket", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StockMarket: public Ui_StockMarket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKMARKET_H
