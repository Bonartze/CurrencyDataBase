#include "mydialog.hpp"
#include "ui_MyDialog.h"


MyDialog::MyDialog(QWidget *parent, bool is_sell, int id, QListWidget *currency_list_,
                   std::unordered_map<std::string, double> currency_amount_, QLabel *current_balance_) :
        QDialog(parent), ui(new Ui::MyDialog), account_id(id), currency_list(currency_list_),
        currency_amount(currency_amount_), current_balance(current_balance_), is_sell_(is_sell) {
    setWindowTitle("Currency transaction");

    ui->setupUi(this);

    //  current_balance_ = current_balance;
    currency_to_buy = new QComboBox();
    ok = new QPushButton("OK", this);
    occupation = new QHBoxLayout(this);

    occupation->addWidget(currency_to_buy);
    ok->move(this->width() - ok->width(), 65);

    pqxx::work w(ConnectionTool::GetConnect());
    auto currencies = w.exec("SELECT DISTINCT name FROM public.\"Currency\"");
    for (auto row = currencies.begin(); row != currencies.end(); ++row)
        currency_to_buy->addItem(QString::fromStdString(row[0].as<std::string>()));

    setStyleSheet("background-color: #333; color: #fff;");

    connect(ok, &QPushButton::clicked, this, &MyDialog::onButtonClickedOk);
}


void MyDialog::onButtonClickedOk() {
    pqxx::work w(ConnectionTool::GetConnect());
    //get currency name for the following join
    QString currency_name = currency_to_buy->currentText();
    //get balance of current account
    auto query_result = w.exec_params("SELECT balance FROM public.\"Account\"\n"
                                      "WHERE id = $1", account_id);
    //get currency price by newest date
    double query_result_currency_price = std::max(w.exec_params("SELECT price FROM public.\"Currency\"\n"
                                                                "WHERE name = $1 ORDER BY date DESC LIMIT 1",
                                                                currency_name.toStdString())[0]["price"].as<double>(),
                                                  1.0);

    double balance = query_result[0]["balance"].is_null() ? 0 : query_result[0]["balance"].as<double>();
    if (!is_sell_) {   //case 1: buying currency
        //updating balance and amount of currency
        w.exec_params("UPDATE public.\"Account\" SET balance = 0, amount = $1\n"
                      "WHERE id = $2;", balance / query_result_currency_price, account_id);
        balance = 0;
        current_balance->setText("Balance: " + QString::number(balance) + " $");
        currency_list->addItem(currency_name);
    } else {  //case 2: selling currency
        if (currency_to_buy->currentText() == currency_list->currentItem()->text()) {
            //getting amount to calculate
            double amount = w.exec_params("SELECT amount FROM public.\"Account\"\n"
                                          "WHERE id = $1", account_id)[0]["amount"].as<double>();
            //updating balance
            w.exec_params("UPDATE public.\"Account\" SET balance = $1\n"
                          "WHERE id = $2", amount * query_result_currency_price, account_id);
            //now user doesn't have any currency so list must be cleared
            currency_list->clear();
        } else {
            QMessageBox::critical(nullptr, "Error", "Error occurred", QMessageBox::Ok);
            return;
        }
    }
    w.commit();
    this->close();
}

MyDialog::~MyDialog() {
    delete ui;
}
