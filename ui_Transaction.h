#ifndef UI_TRANSACTION_H
#define UI_TRANSACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Transaction {
public:

    void setupUi(QWidget *Transaction) {
        if (Transaction->objectName().isEmpty())
            Transaction->setObjectName(QString::fromUtf8("Transaction"));
        Transaction->resize(400, 300);

        retranslateUi(Transaction);

        QMetaObject::connectSlotsByName(Transaction);
    }

    void retranslateUi(QWidget *Transaction) {
        Transaction->setWindowTitle(QCoreApplication::translate("Transaction", "Transaction", nullptr));
    }

};

namespace Ui {
    class Transaction : public Ui_Transaction {
    };
}

QT_END_NAMESPACE

#endif
