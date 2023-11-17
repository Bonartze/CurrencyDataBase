
#include "insertaccount.hpp"
#include "ui_InsertAccount.h"


InsertAccount::InsertAccount(QWidget *parent) :
        QWidget(parent), ui(new Ui::InsertAccount) {
    ui->setupUi(this);
    slice.resize(2);
    chart.resize(2);
    series.resize(2);
    chartview.resize(2);

    insert_into_account = new QPushButton("Insert data", this);
    bank_usage = new QPushButton("Bank usage statistics", this);
    stock_market_usage = new QPushButton("Stock market usage", this);
    delete_one = new QPushButton("Delete note from the table", this);
    delete_table = new QPushButton("Clear the table", this);

    insert_into_account->setFixedSize(200, 30);
    bank_usage->setFixedSize(200, 30);
    stock_market_usage->setFixedSize(200, 30);
    delete_one->setFixedSize(200, 30);
    delete_table->setFixedSize(200, 30);

    insert_into_account->move(10, 100);
    stock_market_usage->move(10, 200);
    bank_usage->move(10, 150);
    delete_one->move(10, 250);
    delete_table->move(10, 300);

    insert_into_account->show();
    bank_usage->show();
    stock_market_usage->show();
    delete_one->show();
    delete_table->show();

    connect(insert_into_account, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(stock_market_usage, SIGNAL(clicked()), this, SLOT(onButtonClickedStockMarketUsage()));
    connect(bank_usage, SIGNAL(clicked()), this, SLOT(onButtonClickedBalanceChangeEachYear()));
    connect(delete_one, SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));
    connect(delete_table, SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));

    insert_line.resize(4);
    for (int i = 0; i < 4; i++) {
        insert_line[i] = new QLineEdit(this);
        insert_line[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

InsertAccount::~InsertAccount() {
    delete ui;
}

void InsertAccount::onButtonClicked() {
    std::string id = insert_line[0]->text().toStdString();
    std::string balance = insert_line[1]->text().toStdString();
    std::string bank_id = insert_line[2]->text().toStdString();
    std::string stock_id = insert_line[3]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"Account\" VALUES ($1, $2, $3, $4);", id, balance, bank_id, stock_id);
    w.commit();
    for (int i = 0; i < 4; i++)
        insert_line[i]->clear();
}

void InsertAccount::onButtonClickedBalanceChangeEachYear() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT b.name AS bank_name,\n"
                            "(COUNT(a.id) * 100.0 / NULLIF((SELECT COUNT(*) FROM public.\"Account\"), 0)) AS percentage_of_usage\n"
                            "FROM public.\"Bank\" b\n"
                            "LEFT JOIN public.\"Account\" a ON b.id = a.bank_id\n"
                            "GROUP BY b.id, b.name;");
    series[0] = new QPieSeries();
    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["bank_name"].as<std::string>());
        int transaction_count = row["percentage_of_usage"].as<double>();

        slice[0] = new QPieSlice(bank_name, transaction_count);
        series[0]->append(slice[0]);
    }
    chart[0] = new QChart();
    chart[0]->addSeries(series[0]);
    chart[0]->setTitle("Banks usage percentage");
    chartview[0] = new QChartView(chart[0]);
    chartview[0]->show();
}

void InsertAccount::onButtonClickedStockMarketUsage() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT s.id AS stock_market_id,\n"
                            "(COUNT(a.id) * 100.0 / NULLIF((SELECT COUNT(*) FROM public.\"Account\"), 0)) AS percentage_of_usage\n"
                            "FROM public.\"StockMarket\" s\n"
                            "LEFT JOIN public.\"Account\" a ON s.id = a.stock_id\n"
                            "GROUP BY s.id;");
    series[1] = new QPieSeries();
    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["stock_market_id"].as<std::string>());
        int transaction_count = row["percentage_of_usage"].as<double>();

        slice[1] = new QPieSlice(bank_name, transaction_count);
        series[1]->append(slice[1]);
    }
    chart[1] = new QChart();
    chart[1]->addSeries(series[1]);
    chart[1]->setTitle("Stock markets usage percentage");
    chartview[1] = new QChartView(chart[1]);
    chartview[1]->show();
}

void InsertAccount::onButtonClickedDeleted() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("DELETE FROM public.\"Account\";");
    w.commit();
}

void InsertAccount::onButtonClickedDeletedOne() {
    pqxx::work w(ConnectionTool::GetConnect());
    int id = insert_line[0]->text().toInt();
    w.exec_params("DELETE FROM public.\"Account\" WHERE id = $1", id);
    w.commit();
    for (int i = 0; i < 4; i++)
        insert_line[i]->clear();
}