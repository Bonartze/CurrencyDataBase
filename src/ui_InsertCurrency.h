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
    }

    void retranslateUi(QWidget *InsertCurrency)
    {
        InsertCurrency->setWindowTitle(QCoreApplication::translate("InsertCurrency", "InsertCurrency", nullptr));
    }

};

namespace Ui {
    class InsertCurrency: public Ui_InsertCurrency {};
}

QT_END_NAMESPACE

#endif
