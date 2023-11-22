/********************************************************************************
** Form generated from reading UI file 'auntification.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUNTIFICATION_H
#define UI_AUNTIFICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Auntification
{
public:

    void setupUi(QWidget *Auntification)
    {
        if (Auntification->objectName().isEmpty())
            Auntification->setObjectName(QString::fromUtf8("Auntification"));
        Auntification->resize(400, 300);

        retranslateUi(Auntification);

        QMetaObject::connectSlotsByName(Auntification);
    } // setupUi

    void retranslateUi(QWidget *Auntification)
    {
        Auntification->setWindowTitle(QCoreApplication::translate("Auntification", "Auntification", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Auntification: public Ui_Auntification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUNTIFICATION_H
