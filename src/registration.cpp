//
// Created by ivan on 23.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Registration.h" resolved

#include "registration.hpp"
#include "ui_Registration.h"


Registration::Registration(QWidget *parent) :
    QWidget(parent), ui(new Ui::Registration) {
    ui->setupUi(this);
}

Registration::~Registration() {
    delete ui;
}
