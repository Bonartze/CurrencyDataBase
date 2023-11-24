//
// Created by ivan on 24.11.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ManageTables.h" resolved

#include "managetables.hpp"
#include "ui_ManageTables.h"


ManageTables::ManageTables(QWidget *parent) :
        QWidget(parent), ui(new Ui::ManageTables) {
    ui->setupUi(this);
}

ManageTables::~ManageTables() {
    delete ui;
}
