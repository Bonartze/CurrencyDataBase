/********************************************************************************
** Form generated from reading UI file 'insertaccount.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTACCOUNT_H
#define UI_INSERTACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsertAccount
{
public:

    void setupUi(QWidget *InsertAccount)
    {
        if (InsertAccount->objectName().isEmpty())
            InsertAccount->setObjectName(QString::fromUtf8("InsertAccount"));
        InsertAccount->resize(400, 300);

        retranslateUi(InsertAccount);

        QMetaObject::connectSlotsByName(InsertAccount);
    } // setupUi

    void retranslateUi(QWidget *InsertAccount)
    {
        InsertAccount->setWindowTitle(QCoreApplication::translate("InsertAccount", "InsertAccount", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InsertAccount: public Ui_InsertAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTACCOUNT_H
