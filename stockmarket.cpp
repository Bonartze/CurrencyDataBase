

#include "stockmarket.hpp"
#include "ui_StockMarket.h"


StockMarket::StockMarket(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StockMarket) {
    ui->setupUi(this);
    insert_into_stock_market = new QPushButton("Insert data", this);
    insert_into_stock_market->setGeometry(20, 20, 20, 20);
    insert_into_stock_market->show();
    connect(insert_into_stock_market, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    insert_stock_market_line.resize(5);
    for (int i = 0; i < 5; i++) {
        insert_stock_market_line[i] = new QLineEdit(this);
        insert_stock_market_line[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

StockMarket::~StockMarket() {
    delete ui;
}

void StockMarket::onButtonClicked() {
    std::string id = insert_stock_market_line[0]->text().toStdString();
    std::string currency_id_from = insert_stock_market_line[1]->text().toStdString();
    std::string currency_id_to = insert_stock_market_line[2]->text().toStdString();
    std::string rate_ = insert_stock_market_line[3]->text().toStdString();
    std::string date = insert_stock_market_line[4]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"StockMarket\" VALUES ($1, $2, $3, $4, $5)", id, currency_id_from,
                  currency_id_to, rate_, date);
    w.commit();
    for (int i = 0; i < 5; i++)
        insert_stock_market_line[i]->clear();
}