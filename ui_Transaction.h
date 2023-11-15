/********************************************************************************
** Form generated from reading UI file 'transaction.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTION_H
#define UI_TRANSACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Transaction
{
public:

    void setupUi(QWidget *Transaction)
    {
        if (Transaction->objectName().isEmpty())
            Transaction->setObjectName(QString::fromUtf8("Transaction"));
        Transaction->resize(400, 300);

        retranslateUi(Transaction);

        QMetaObject::connectSlotsByName(Transaction);
    } // setupUi

    void retranslateUi(QWidget *Transaction)
    {
        Transaction->setWindowTitle(QCoreApplication::translate("Transaction", "Transaction", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Transaction: public Ui_Transaction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTION_H
