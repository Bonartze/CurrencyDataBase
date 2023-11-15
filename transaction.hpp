//
// Created by ivan on 15.11.23.
//

#ifndef UNTITLED87_TRANSACTION_HPP
#define UNTITLED87_TRANSACTION_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Transaction; }
QT_END_NAMESPACE

class Transaction : public QWidget {
Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);

    ~Transaction() override;

private:
    Ui::Transaction *ui;
};


#endif //UNTITLED87_TRANSACTION_HPP
