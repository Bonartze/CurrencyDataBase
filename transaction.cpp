

#include "transaction.hpp"
#include "ui_Transaction.h"


Transaction::Transaction(QWidget *parent) :
        QWidget(parent), ui(new Ui::Transaction) {
    ui->setupUi(this);
    insert_into_transaction = new QPushButton("Insert data", this);
    insert_into_transaction->setGeometry(20, 20, 20, 20);
    insert_into_transaction->show();
    connect(insert_into_transaction, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    insert_transaction_line.resize(4);
    for (int i = 0; i < 5; i++) {
        insert_transaction_line[i] = new QLineEdit(this);
        insert_transaction_line[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

Transaction::~Transaction() {
    delete ui;
}

void Transaction::onButtonClicked() {
    std::string id = insert_transaction_line[0]->text().toStdString();
    std::string account_id_from = insert_transaction_line[1]->text().toStdString();
    std::string amount = insert_transaction_line[2]->text().toStdString();
    std::string date = insert_transaction_line[3]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"Transaction\" VALUES ($1, $2, $3, $4);", id, account_id_from, amount, date);
    w.commit();
    for (int i = 0; i < 4; i++)
        insert_transaction_line[i]->clear();
}


