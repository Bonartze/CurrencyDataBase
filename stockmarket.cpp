

#include "stockmarket.hpp"
#include "ui_StockMarket.h"


StockMarket::StockMarket(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StockMarket) {
    ui->setupUi(this);
}

StockMarket::~StockMarket() {
    delete ui;
}
