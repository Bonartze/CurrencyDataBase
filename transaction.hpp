#ifndef UNTITLED87_TRANSACTION_HPP
#define UNTITLED87_TRANSACTION_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Transaction; }
QT_END_NAMESPACE

class Transaction : public QWidget {
Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);

    ~Transaction() override;

private slots:

    void onButtonClicked();

private:
    std::vector<QLineEdit *> insert_transaction_line;
    QPushButton *insert_into_transaction;
    Ui::Transaction *ui;
};


#endif //UNTITLED87_TRANSACTION_HPP
