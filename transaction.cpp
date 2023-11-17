

#include <QValueAxis>
#include "transaction.hpp"
#include "ui_Transaction.h"


Transaction::Transaction(QWidget *parent) :
        QWidget(parent), ui(new Ui::Transaction) {
    ui->setupUi(this);
    insert_into_transaction = new QPushButton("Insert data", this);
    transaction_statistics = new QPushButton("Get transaction statistics", this);
    delete_table = new QPushButton("Clear the table", this);
    delete_one = new QPushButton("Delete note from the table", this);


    insert_into_transaction->setFixedSize(200, 30);
    transaction_statistics->setFixedSize(200, 30);
    delete_table->setFixedSize(200, 30);
    delete_one->setFixedSize(200, 30);


    insert_into_transaction->move(10, 100);
    transaction_statistics->move(10, 150);
    delete_one->move(10, 200);
    delete_table->move(10, 250);

    insert_into_transaction->show();
    transaction_statistics->show();
    delete_one->show();
    delete_table->show();


    connect(insert_into_transaction, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(transaction_statistics, SIGNAL(clicked()), this, SLOT(onButtonClickedTransactionStatistics()));

    insert_transaction_line.resize(4);
    for (int i = 0; i < 4; i++) {
        insert_transaction_line[i] = new QLineEdit(this);
        insert_transaction_line[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

Transaction::~Transaction() {
    delete ui;
}

void Transaction::onButtonClicked() {
    std::string id = insert_transaction_line[0]->text().toStdString();
    std::string account_id_from = insert_transaction_line[1]->text().toStdString();
    std::string amount = insert_transaction_line[2]->text().toStdString();
    std::string date = insert_transaction_line[3]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"Transaction\" VALUES ($1, $2, $3, $4);", id, account_id_from, amount, date);
    w.commit();
    for (int i = 0; i < 4; i++)
        insert_transaction_line[i]->clear();

}

void Transaction::onButtonClickedTransactionStatistics() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto query_res = w.exec("SELECT "
                            "\"Transaction\".date, "
                            "SUM(\"Transaction\".amount) AS Got "
                            "FROM "
                            "public.\"Transaction\" "
                            "JOIN "
                            "public.\"Account\" ON public.\"Account\".id = public.\"Transaction\".account_id_from "
                            "GROUP BY "
                            "\"Transaction\".date, \"Transaction\".account_id_from "
                            "ORDER BY "
                            "\"Transaction\".date ASC;");
    QStringList categories;
    barSet = new QtCharts::QBarSet("Transacted Money");

    for (const auto &row: query_res) {
        QString year = QString::fromStdString(row[0].c_str());
        categories << year;

        double amount = row[1].as<double>();
        barSet->append(amount);
    }

    series = new QtCharts::QBarSeries();
    series->append(barSet);

    chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Transaction Statistics");

    axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Years");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Transacted Money");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}

void Transaction::onButtonClickedDeleted() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("DELETE FROM public.\"Transaction\";");
    w.commit();
}

void Transaction::onButtonClickedDeletedOne() {
    pqxx::work w(ConnectionTool::GetConnect());
    int id = insert_transaction_line[0]->text().toInt();
    w.exec_params("DELETE FROM public.\"Transaction\" WHERE id = $1", id);
    w.commit();
    for (int i = 0; i < 4; i++)
        insert_transaction_line[i]->clear();
}

