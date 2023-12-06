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
    transaction_journal = new QPushButton("Get transaction history", this);
    transaction_journal->setFixedWidth(200);
    ok = new QPushButton("OK", this);
    occupation = new QHBoxLayout(this);

    occupation->addWidget(currency_to_buy);
    ok->move(this->width() - ok->width(), 65);
    transaction_journal->move(this->width() - ok->width() - transaction_journal->width() - 10, 65);

    pqxx::work w(ConnectionTool::GetConnect());
    auto currencies = w.exec("SELECT DISTINCT name FROM public.\"Currency\"");
    for (auto row = currencies.begin(); row != currencies.end(); ++row)
        currency_to_buy->addItem(QString::fromStdString(row[0].as<std::string>()));

    setStyleSheet("background-color: #333; color: #fff;");

    connect(ok, &QPushButton::clicked, this, &MyDialog::onButtonClickedOk);
    connect(transaction_journal, &QPushButton::clicked, this, &MyDialog::onButtonClickedHistoryTransactions);
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
        if (balance)
            w.exec_params("UPDATE public.\"Account\" SET balance = 0, amount = $1\n"
                          "WHERE id = $2;", balance / query_result_currency_price, account_id);
        else {
            QMessageBox::critical(nullptr, "Error", "0 balance", QMessageBox::Ok);
            return;
        }
        w.exec_params("INSERT INTO public.\"Transaction\" (account_id_from, amount, date) VALUES ($1, $2, $3)",
                      account_id, balance / query_result_currency_price, "2023");
        balance = 0;
        current_balance->setText("Balance: " + QString::number(balance) + " $");
        currency_list->addItem(currency_name);
    } else {  //case 2: selling currency
        if (currency_to_buy->currentText() == currency_list->currentItem()->text()) {
            //getting amount to calculate
            double amount = w.exec_params("SELECT amount FROM public.\"Account\"\n"
                                          "WHERE id = $1", account_id)[0]["amount"].as<double>();
            //updating balance
            const double percentage = 1.1;
            w.exec_params("UPDATE public.\"Account\" SET balance = $1\n"
                          "WHERE id = $2", amount * query_result_currency_price * percentage, account_id);
            balance = amount * query_result_currency_price * percentage;
            w.exec_params("INSERT INTO public.\"Transaction\" (account_id_from, amount, date)  VALUES ($1, 0, $2)",
                          account_id, "2023");
            current_balance->setText("Balance: " + QString::number(balance) + " $");
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

void MyDialog::onButtonClickedHistoryTransactions() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT * FROM public.\"Transaction\"");

    QTableWidget *tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(res_query.size());
    tableWidget->setColumnCount(5);

    QStringList headers;
    headers << "ID" << "Account ID" << "Amount" << "Date" << "Status";
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFile file("../transaction_data");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << headers.join("\t") << "\n";
    int row = 0;
    for (auto rowIt = res_query.begin(); rowIt != res_query.end(); ++rowIt) {
        int id = rowIt["id"].as<int>();
        int account_id = rowIt["account_id_from"].as<int>();
        double amount = rowIt["amount"].as<double>();
        std::string date = rowIt["date"].as<std::string>();

        QString status = (amount == 0) ? "Sell" : "Purchase";

        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(id));
        QTableWidgetItem *accountIdItem = new QTableWidgetItem(QString::number(account_id));
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(amount));
        QTableWidgetItem *dateItem = new QTableWidgetItem(QString::fromStdString(date));
        QTableWidgetItem *statusItem = new QTableWidgetItem(status);

        tableWidget->setItem(row, 0, idItem);
        tableWidget->setItem(row, 1, accountIdItem);
        tableWidget->setItem(row, 2, amountItem);
        tableWidget->setItem(row, 3, dateItem);
        tableWidget->setItem(row, 4, statusItem);
        out << QString::number(id) << "\t"
            << QString::number(account_id) << "\t"
            << QString::number(amount) << "\t"
            << QString::fromStdString(date) << "\t"
            << status << "\n";

        ++row;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Transaction history");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(tableWidget);
    dialog.setLayout(layout);
    dialog.resize(700, 400);
    dialog.exec();
}