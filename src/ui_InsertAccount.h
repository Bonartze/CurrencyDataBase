#ifndef UI_INSERTACCOUNT_H
#define UI_INSERTACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsertAccount {
public:

    void setupUi(QWidget *InsertAccount) {
        if (InsertAccount->objectName().isEmpty())
            InsertAccount->setObjectName(QString::fromUtf8("InsertAccount"));
        InsertAccount->resize(400, 300);

        retranslateUi(InsertAccount);

        QMetaObject::connectSlotsByName(InsertAccount);
    }

    void retranslateUi(QWidget *InsertAccount) {
        InsertAccount->setWindowTitle(QCoreApplication::translate("InsertAccount", "InsertAccount", nullptr));
    }

};

namespace Ui {
    class InsertAccount : public Ui_InsertAccount {
    };
}

QT_END_NAMESPACE

#endif
