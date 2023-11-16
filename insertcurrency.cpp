
#include "insertcurrency.hpp"
#include "ui_InsertCurrency.h"


InsertCurrency::InsertCurrency(QWidget *parent) :
        QWidget(parent), ui(new Ui::InsertCurrency) {
    ui->setupUi(this);
    insert_into_currency = new QPushButton("Insert data", this);
    delete_table = new QPushButton("Clear the table", this);
    delete_one = new QPushButton("Delete note from the table", this);
    currency_chart = new QPushButton("Display currency popularity statistics", this);


    currency_chart->setFixedSize(200, 30);
    delete_table->setFixedSize(200, 30);
    insert_into_currency->setFixedSize(200, 30);
    delete_one->setFixedSize(200, 30);

    currency_chart->move(10, 100);
    delete_table->move(10, 150);
    insert_into_currency->move(10, 200);
    delete_one->move(10, 250);

    delete_one->show();
    delete_table->show();
    currency_chart->show();
    insert_into_currency->show();

    connect(insert_into_currency, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(currency_chart, SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));
    connect(delete_table, SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(delete_one, SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));


    insert_currency_line.resize(2);
    for (int i = 0; i < 2; i++) {
        insert_currency_line[i] = new QLineEdit(this);
        insert_currency_line[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

InsertCurrency::~InsertCurrency() {
    delete ui;
}

void InsertCurrency::onButtonClicked() {
    std::string id = insert_currency_line[0]->text().toStdString();
    std::string name = insert_currency_line[1]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"Currency\" VALUES ($1, $2);", id, name);
    w.commit();
    for (int i = 0; i < 2; i++)
        insert_currency_line[i]->clear();
}

void InsertCurrency::onButtonClickedDeletedOne() {
    pqxx::work w(ConnectionTool::GetConnect());
    int id = insert_currency_line[0]->text().toInt();
    w.exec_params("DELETE FROM public.\"Currency\" WHERE id = $1", id);
    w.commit();
    for (int i = 0; i < 2; i++)
        insert_currency_line[i]->clear();
}

void InsertCurrency::onButtonClickedDeleted() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("DELETE FROM public.\"Currency\";");
    w.commit();
}

void InsertCurrency::onButtonCLickedChart() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT name as name, COUNT(id) as transaction_count\n"
                            "FROM public.\"Currency\" GROUP BY name;");
    series = new QPieSeries();

    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["name"].as<std::string>());
        int transaction_count = row["transaction_count"].as<int>();

        slice = new QPieSlice(bank_name, transaction_count);
        series->append(slice);
    }
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Currency popularity");
    chartview = new QChartView(chart);
    chartview->show();
}
