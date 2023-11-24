#include "managetables.hpp"
#include "ui_ManageTables.h"

ManageTables::ManageTables(QWidget *parent) :
        QWidget(parent), ui(new Ui::ManageTables) {
    ui->setupUi(this);
}

ManageTables::~ManageTables() {
    delete ui;
}
