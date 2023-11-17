

#include "stockmarket.hpp"
#include "ui_StockMarket.h"


StockMarket::StockMarket(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StockMarket) {
    ui->setupUi(this);
    insert_into_stock_market = new QPushButton("Insert data", this);
    income_currency = new QPushButton("Get statistics of currency's sales", this);
    delete_table = new QPushButton("Clear the table", this);
    delete_one = new QPushButton("Delete note from the table", this);

    insert_into_stock_market->setFixedSize(200, 30);
    income_currency->setFixedSize(200, 30);
    delete_table->setFixedSize(200, 30);
    delete_one->setFixedSize(200, 30);


    insert_into_stock_market->move(10, 100);
    income_currency->move(10, 150);
    delete_table->move(10, 200);
    delete_one->move(10, 250);

    insert_into_stock_market->show();
    income_currency->show();
    delete_table->show();
    delete_one->show();

    connect(insert_into_stock_market, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(income_currency, SIGNAL(clicked()), this, SLOT(onButtonClickedIncomeCurrency()));
    connect(delete_table, SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(delete_one, SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));


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

void StockMarket::onButtonClickedIncomeCurrency() {
    using namespace QtCharts;
    QBarSeries *series = new QBarSeries();
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT public.\"Currency\".name, SUM(public.\"StockMarket\".rate) \n"
                            "FROM public.\"Currency\"\n"
                            "JOIN public.\"StockMarket\" ON public.\"StockMarket\".currecny_id_to = public.\"Currency\".id\n"
                            "GROUP BY public.\"Currency\".name\n"
                            "ORDER BY SUM(public.\"StockMarket\".rate) DESC;");
    QStringList categories;
    barSet = new QtCharts::QBarSet("Transacted Money");

    for (const auto &row: res_query) {
        QString year = QString::fromStdString(row[0].c_str());
        categories << year;

        double amount = row[1].as<double>();
        barSet->append(amount);
    }

    series = new QtCharts::QBarSeries();
    series->append(barSet);

    chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Converted currency");

    axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Name of currency");
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

void StockMarket::onButtonClickedDeleted() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("DELETE FROM public.\"StockMarket\";");
    w.commit();
}

void StockMarket::onButtonClickedDeletedOne() {
    pqxx::work w(ConnectionTool::GetConnect());
    int id = insert_stock_market_line[0]->text().toInt();
    w.exec_params("DELETE FROM public.\"StockMarket\" WHERE id = $1", id);
    w.commit();
    for (int i = 0; i < 5; i++)
        insert_stock_market_line[i]->clear();
}