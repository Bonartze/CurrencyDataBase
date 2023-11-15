
#include "insertcurrency.hpp"
#include "ui_InsertCurrency.h"


InsertCurrency::InsertCurrency(QWidget *parent) :
        QWidget(parent), ui(new Ui::InsertCurrency) {
    ui->setupUi(this);
}

InsertCurrency::~InsertCurrency() {
    delete ui;
}
