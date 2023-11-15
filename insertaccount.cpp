//
// Created by ivan on 15.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_InsertAccount.h" resolved

#include "insertaccount.hpp"
#include "ui_InsertAccount.h"


InsertAccount::InsertAccount(QWidget *parent) :
        QWidget(parent), ui(new Ui::InsertAccount) {
    ui->setupUi(this);
}

InsertAccount::~InsertAccount() {
    delete ui;
}
