//
// Created by ivan on 15.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Transaction.h" resolved

#include "transaction.hpp"
#include "ui_Transaction.h"


Transaction::Transaction(QWidget *parent) :
        QWidget(parent), ui(new Ui::Transaction) {
    ui->setupUi(this);
}

Transaction::~Transaction() {
    delete ui;
}
