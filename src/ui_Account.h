/********************************************************************************
** Form generated from reading UI file 'account.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Account
{
public:

    void setupUi(QWidget *Account)
    {
        if (Account->objectName().isEmpty())
            Account->setObjectName(QString::fromUtf8("Account"));
        Account->resize(400, 300);

        retranslateUi(Account);

        QMetaObject::connectSlotsByName(Account);
    } // setupUi

    void retranslateUi(QWidget *Account)
    {
        Account->setWindowTitle(QCoreApplication::translate("Account", "Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Account: public Ui_Account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNT_H
