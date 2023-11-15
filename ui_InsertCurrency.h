/********************************************************************************
** Form generated from reading UI file 'insertcurrency.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTCURRENCY_H
#define UI_INSERTCURRENCY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsertCurrency
{
public:

    void setupUi(QWidget *InsertCurrency)
    {
        if (InsertCurrency->objectName().isEmpty())
            InsertCurrency->setObjectName(QString::fromUtf8("InsertCurrency"));
        InsertCurrency->resize(400, 300);

        retranslateUi(InsertCurrency);

        QMetaObject::connectSlotsByName(InsertCurrency);
    } // setupUi

    void retranslateUi(QWidget *InsertCurrency)
    {
        InsertCurrency->setWindowTitle(QCoreApplication::translate("InsertCurrency", "InsertCurrency", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InsertCurrency: public Ui_InsertCurrency {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTCURRENCY_H
