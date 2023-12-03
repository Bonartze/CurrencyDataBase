/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:

    void setupUi(QWidget *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName(QString::fromUtf8("MyDialog"));
        MyDialog->resize(400, 300);

        retranslateUi(MyDialog);

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QWidget *MyDialog)
    {
        MyDialog->setWindowTitle(QCoreApplication::translate("MyDialog", "MyDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
