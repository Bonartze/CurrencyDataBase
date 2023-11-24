/********************************************************************************
** Form generated from reading UI file 'managetables.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGETABLES_H
#define UI_MANAGETABLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManageTables
{
public:

    void setupUi(QWidget *ManageTables)
    {
        if (ManageTables->objectName().isEmpty())
            ManageTables->setObjectName(QString::fromUtf8("ManageTables"));
        ManageTables->resize(400, 300);

        retranslateUi(ManageTables);

        QMetaObject::connectSlotsByName(ManageTables);
    } // setupUi

    void retranslateUi(QWidget *ManageTables)
    {
        ManageTables->setWindowTitle(QCoreApplication::translate("ManageTables", "ManageTables", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageTables: public Ui_ManageTables {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGETABLES_H
