#include <QPropertyAnimation>
#include "account.hpp"
#include "ui_Account.h"

QString s = "QPushButton{"
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
            "}";

Account::Account(QWidget *parent, int id) :
        QWidget(parent), ui(new Ui::Account), account_id(id - 12) {
    using namespace QtCharts;
    pqxx::work w(ConnectionTool::GetConnect());
    buy = new QPushButton();
    sell = new QPushButton();
    top_up = new QPushButton();
    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *layout1 = new QVBoxLayout();
    QVBoxLayout *layout2 = new QVBoxLayout();
    QHBoxLayout *layout3 = new QHBoxLayout();
    currency_list = new QListWidget(this);
    crypto_choice = new QComboBox();
    ui->setupUi(this);

    top_up->setFixedHeight(150);
    top_up->setStyleSheet(s);
    buy->setFixedHeight(150);
    buy->setStyleSheet(s);
    sell->setFixedHeight(150);
    sell->setStyleSheet(s);

    top_up->setText("Top up (+100$)");
    buy->setText("Buy");
    sell->setText("Sell");

    currency_list->resize(500, 300);
    create_graph = new QPushButton("Creat graph of price");
    create_graph->setStyleSheet(s);
    create_graph->setFixedHeight(50);

    auto a = w.exec_params("SELECT balance FROM public.\"Account\"\n"
                           "WHERE id = $1", account_id);

    if (!a[0]["balance"].is_null()) {
        balance = a[0]["balance"].as<double>();
    }
    current_balance = new QLabel("Balance: " + QString::number(balance) + " $");

    layout2->addWidget(current_balance);
    layout3->addWidget(buy);
    layout3->addWidget(sell);
    layout3->addWidget(top_up);
    layout1->addWidget(crypto_choice);
    layout1->addWidget(create_graph);
    layout2->addLayout(layout3);
    layout->addLayout(layout2);
    layout->addLayout(layout1);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(10);

    currency_list->resize(300, 300);
    currency_list->move(100, 200);

    auto currencies = w.exec("SELECT DISTINCT name FROM public.\"Currency\"");
    for (auto row = currencies.begin(); row != currencies.end(); ++row)
        crypto_choice->addItem(QString::fromStdString(row[0].as<std::string>()));

    connect(create_graph, &QPushButton::clicked, this, &Account::print_graph);
    connect(buy, &QPushButton::clicked, this, &Account::onButtonClickedBuy);
    connect(sell, &QPushButton::clicked, this, &Account::onButtonClickedSell);
    connect(top_up, &QPushButton::clicked, this, &Account::onButtonClickedTopUp);
}


Account::~Account() {
    delete ui;
}


void Account::onButtonClickedTopUp() {
    pqxx::work w(ConnectionTool::GetConnect());
    balance += 100;
    w.exec_params("UPDATE public.\"Account\" SET balance = $1 WHERE id = $2", balance, account_id);
    w.commit();
    current_balance->setText("Balance: " + QString::number(balance) + " $");
}

void Account::onButtonClickedBuy() {
    MyDialog *myDialog = new MyDialog(nullptr, false, account_id, currency_list, currency_amount, current_balance);
    myDialog->setFixedHeight(100);
    myDialog->show();
}

void Account::onButtonClickedSell() {
    MyDialog *myDialog = new MyDialog(nullptr, true, account_id, currency_list, currency_amount, current_balance);
    myDialog->setFixedHeight(100);
    myDialog->show();
}

void Account::print_graph() {
    using namespace QtCharts;

    pqxx::work w(ConnectionTool::GetConnect());
    auto query_res = w.exec("SELECT name, date, price FROM public.\"Currency\";");
    std::string name = crypto_choice->currentText().toStdString();

    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();
    QDateTimeAxis *axisX = new QDateTimeAxis;
    QValueAxis *axisY = new QValueAxis;
    QChartView *chartView = new QChartView(chart);

    chart->setTheme(QChart::ChartThemeDark);

    QColor seriesColor = QColor(0, 255, 0);

    for (auto a = query_res.begin(); a != query_res.end(); ++a) {
        if (name == a["name"].as<std::string>()) {
            double price = a["price"].as<double>();
            std::string date_str = a["date"].as<std::string>();

            QDateTime date = QDateTime::fromString(QString::fromStdString(date_str), "yyyy-MM-dd");

            series->append(date.toMSecsSinceEpoch(), price);
        }
    }

    axisX->setFormat("yyyy-MM-dd");
    axisX->setTitleText("Date");

    axisY->setLabelFormat("%.1f");
    axisY->setTitleText("Price");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->addSeries(series);

    QPen pen(seriesColor);
    pen.setWidth(1);
    series->setPen(pen);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(this);
    chartView->move(850, 170);
    chartView->resize(850, 850);
    chartView->show();
}






