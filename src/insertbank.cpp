#include "insertbank.hpp"
#include "ui_InsertBank.h"


InsertBank::InsertBank(QWidget *parent) : QMainWindow(parent), ui(new Ui::InsertBank) {
    ui->setupUi(this);
    buttons.resize(2);
    buttons[0] = new QPushButton("Display bank usage statistics", this);
    buttons[1] = new QPushButton("Display Bank-Login");
    QPixmap img("bank.jpg");
    layout_ = new QHBoxLayout();
    label_ = new QLabel(this);
    vl_ = new QVBoxLayout();
    centralWidget = new QWidget();

    for (int i = 0; i < 2; i++) {
        buttons[i]->setFont(QFont("Arial", 12, QFont::Bold));
        buttons[i]->setFixedSize(600, 120);
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

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    img = img.scaled(500, 500);
    label_->setPixmap(img);
    label_->setAlignment(Qt::AlignCenter);
    vl_->addWidget(label_);
    vl_->addLayout(layout_);
    centralWidget->setLayout(vl_);
    for (int i = 0; i < 2; i++)
        layout_->addWidget(buttons[i]);

    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClickedChartLoginBank()));
    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));
    setCentralWidget(centralWidget);
}

InsertBank::~InsertBank() {
    delete ui;
}

void InsertBank::onButtonClickedChartLoginBank() {

    pqxx::work w(ConnectionTool::GetConnect());
    auto result = w.exec(
            "SELECT acc.login as login, b.name as bank FROM public.\"Account\" AS acc "
            "RIGHT JOIN public.\"Bank\" AS b"
            " ON acc.bank_id = b.id;");
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(2);

    QStringList headers;
    headers << "Login" << "Bank Name";
    tableWidget->setHorizontalHeaderLabels(headers);

    int row = 0;

    for (auto el: result) {
        QString login = el["login"].as<std::string>().c_str();
        QString bankName = el["bank"].as<std::string>().c_str();

        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(login));
        tableWidget->setItem(row, 1, new QTableWidgetItem(bankName));
        ++row;
    }

    tableWidget->setFixedSize(250, 500);
    QPalette pal = tableWidget->palette();
    pal.setColor(QPalette::Window, QColor(53, 53, 53));
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Base, QColor(25, 25, 25));
    pal.setColor(QPalette::AlternateBase, QColor(35, 35, 35));
    tableWidget->setPalette(pal);
    tableWidget->show();

}


void InsertBank::onButtonCLickedChart() {
    pqxx::work w(ConnectionTool::GetConnect());
    auto res_query = w.exec("SELECT name as name, COUNT(id) as transaction_count\n"
                            "FROM public.\"Bank\" GROUP BY name;");
    try {
        if (res_query.empty())
            throw QException();
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
    }

    series = new QPieSeries();
    chart = new QChart();
    chartview = new QChartView(chart);

    int totalTransactions = 0;

    for (const auto &row: res_query) {
        totalTransactions += row["transaction_count"].as<int>();
    }

    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["name"].as<std::string>());
        int transaction_count = row["transaction_count"].as<int>();
        double percentage = static_cast<double>(transaction_count) / totalTransactions * 100.0;

        slice = new QPieSlice(bank_name, percentage);
        slice->setLabel(QString("%1: %2%").arg(bank_name).arg(QString::number(percentage, 'f', 2)));
        series->append(slice);
    }

    chart->addSeries(series);
    chart->setTitle("Banks usage");

    chart->setTheme(QChart::ChartThemeDark);

    chartview->setRenderHint(QPainter::Antialiasing);

    QPalette pal = chartview->palette();
    pal.setColor(QPalette::Window, QColor(53, 53, 53));
    pal.setColor(QPalette::WindowText, Qt::white);
    chartview->setPalette(pal);

    chartview->setWindowTitle("BankPieUsage");
    chartview->setFixedSize(600, 600);
    chartview->show();
}
