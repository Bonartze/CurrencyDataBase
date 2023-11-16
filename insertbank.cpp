#include "insertbank.hpp"
#include "ui_InsertBank.h"


InsertBank::InsertBank(QWidget *parent) : QMainWindow(parent), ui(new Ui::InsertBank) {
    ui->setupUi(this);

    bank_chart = new QPushButton("Display bank usage statistics", this);
    delete_table = new QPushButton("Clear the table", this);
    insert_in_bank = new QPushButton("Insert data", this);
    delete_one = new QPushButton("Delete note from the table", this);

    bank_chart->setFixedSize(200, 30);
    delete_table->setFixedSize(200, 30);
    insert_in_bank->setFixedSize(200, 30);
    delete_one->setFixedSize(200, 30);

    bank_chart->move(10, 100);
    delete_table->move(10, 150);
    insert_in_bank->move(10, 200);
    delete_one->move(10, 250);

    bank_chart->show();
    delete_table->show();
    insert_in_bank->show();
    delete_one->show();

    connect(insert_in_bank, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(bank_chart, SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));
    connect(delete_table, SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(delete_one, SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));

    insert_line_bank.resize(2);
    for (int i = 0; i < 2; i++) {
        insert_line_bank[i] = new QLineEdit(this);
        insert_line_bank[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

InsertBank::~InsertBank() {
    delete ui;
}

void InsertBank::onButtonClicked() {
    int id = insert_line_bank[0]->text().toInt();
    std::string name = insert_line_bank[1]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"Bank\" VALUES ($1, $2);", id, name);
    w.commit();
    for (int i = 0; i < 2; i++)
        insert_line_bank[i]->clear();
}

void InsertBank::onButtonCLickedChart() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT name as name, COUNT(id) as transaction_count\n"
                            "FROM public.\"Bank\" GROUP BY name;");
    series = new QPieSeries();

    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["name"].as<std::string>());
        int transaction_count = row["transaction_count"].as<int>();

        slice = new QPieSlice(bank_name, transaction_count);
        series->append(slice);
    }
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Banks usage");
    chartview = new QChartView(chart);
    chartview->show();
}

void InsertBank::onButtonClickedDeleted() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("DELETE FROM public.\"Bank\";");
    w.commit();
}

void InsertBank::onButtonClickedDeletedOne() {
    pqxx::work w(ConnectionTool::GetConnect());
    int id = insert_line_bank[0]->text().toInt();
    w.exec_params("DELETE FROM public.\"Bank\" WHERE id = $1", id);
    w.commit();
    for (int i = 0; i < 2; i++)
        insert_line_bank[i]->clear();
}