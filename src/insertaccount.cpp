
#include "insertaccount.hpp"
#include "ui_InsertAccount.h"

InsertAccount::InsertAccount(QWidget *parent) : QMainWindow(parent), ui(new Ui::InsertAccount) {
    ui->setupUi(this);
    buttons.resize(2);
    series.resize(2);
    slice.resize(2);
    chart.resize(2);
    chartview.resize(2);

    buttons[0] = new QPushButton("Bank usage statistics", this);
    buttons[1] = new QPushButton("Stock market usage", this);

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClickedBalanceChangeEachYear()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClickedStockMarketUsage()));

    for (int i = 0; i < 2; i++) {
        buttons[i]->setFixedSize(600, 120);
        buttons[i]->setFont(QFont("Arial", 12, QFont::Bold));
        buttons[i]->setStyleSheet("QPushButton {"
                                  "    background-color: #333333;"
                                  "    color: #ffffff;"
                                  "    border: 2px solid #ffffff;"
                                  "    border-radius: 10px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "    background-color: #555555;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "    background-color: #777777;"
                                  "}");
    }

    layout_ = new QHBoxLayout();
    label_ = new QLabel(this);
    vl_ = new QVBoxLayout();
    centralWidget = new QWidget();
    QPixmap img("account.jpg");

    for (int i = 0; i < 2; i++) {
        layout_->addWidget(buttons[i]);
    }
    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    img = img.scaled(500, 500);
    label_->setPixmap(img);
    label_->setAlignment(Qt::AlignCenter);
    vl_->addWidget(label_);
    vl_->addLayout(layout_);
    centralWidget->setLayout(vl_);
    setCentralWidget(centralWidget);
}

InsertAccount::~InsertAccount() {
    delete ui;
}


void InsertAccount::onButtonClickedBalanceChangeEachYear() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT DISTINCT b.name AS bank_name,\n"
                            "(COUNT(a.id) * 100.0 / NULLIF((SELECT COUNT(*) FROM public.\"Account\"), 0)) AS percentage_of_usage\n"
                            "FROM public.\"Bank\" b\n"
                            "LEFT JOIN public.\"Account\" a ON b.id = a.bank_id\n"
                            "GROUP BY b.id, b.name;");
    try {
        if (res_query.empty())
            throw QException();
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
        return;
    }

    series[0] = new QPieSeries();
    chart[0] = new QChart();
    chartview[0] = new QChartView(chart[0]);

    chart[0]->setTheme(QChart::ChartThemeDark);

    int totalUsage = 0;

    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["bank_name"].as<std::string>());
        double percentage_of_usage = row["percentage_of_usage"].as<double>();
        totalUsage += percentage_of_usage;

        QPieSlice *slice = new QPieSlice(
                QString("%1: %2%").arg(bank_name).arg(QString::number(percentage_of_usage, 'f', 1)),
                percentage_of_usage);
        series[0]->append(slice);
    }

    chart[0]->addSeries(series[0]);
    chart[0]->setTitle("Banks usage percentage");

    chartview[0]->setWindowTitle("BankUsagePie");
    chartview[0]->setFixedSize(600, 600);

    QPalette chartViewPalette = chartview[0]->palette();
    chartViewPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    chartViewPalette.setColor(QPalette::WindowText, Qt::white);
    chartview[0]->setPalette(chartViewPalette);

    chartview[0]->show();
}


void InsertAccount::onButtonClickedStockMarketUsage() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT s.id AS stock_market_id,\n"
                            "(COUNT(a.id) * 100.0 / NULLIF((SELECT COUNT(*) FROM public.\"Account\"), 0)) AS percentage_of_usage\n"
                            "FROM public.\"StockMarket\" s\n"
                            "LEFT JOIN public.\"Account\" a ON s.id = a.stock_id\n"
                            "GROUP BY s.id;");
    try {
        if (res_query.empty())
            throw QException();
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
        return;
    }

    series[1] = new QPieSeries();
    chart[1] = new QChart();
    chartview[1] = new QChartView(chart[1]);

    chart[1]->setTheme(QChart::ChartThemeDark);

    int totalUsage = 0;

    for (const auto &row: res_query) {
        totalUsage += row["percentage_of_usage"].as<double>();
    }
    for (const auto &row: res_query) {
        QString stock_market_id = QString::fromStdString(row["stock_market_id"].as<std::string>());
        double percentage_of_usage = row["percentage_of_usage"].as<double>();

        slice[1] = new QPieSlice(stock_market_id, percentage_of_usage);
        slice[1]->setLabel(QString("%1: %2%").arg(stock_market_id).arg(QString::number(percentage_of_usage, 'f', 2)));
        series[1]->append(slice[1]);
    }

    chart[1]->addSeries(series[1]);
    chart[1]->setTitle("Stock markets usage percentage");

    chartview[1]->setWindowTitle("StockPieUsage");
    chartview[1]->setFixedSize(600, 600);

    QPalette chartViewPalette = chartview[1]->palette();
    chartViewPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    chartViewPalette.setColor(QPalette::WindowText, Qt::white);
    chartview[1]->setPalette(chartViewPalette);

    chartview[1]->show();
}


