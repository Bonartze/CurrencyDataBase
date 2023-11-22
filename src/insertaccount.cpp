
#include "insertaccount.hpp"
#include "ui_InsertAccount.h"

InsertAccount::InsertAccount(QWidget *parent) : QMainWindow(parent), ui(new Ui::InsertAccount) {
    ui->setupUi(this);
    insert_line.resize(4);
    buttons.resize(5);
    labels.resize(4);
    series.resize(2);
    slice.resize(2);
    chart.resize(2);
    chartview.resize(2);

    QFont font("Arial", 10, QFont::Bold);

    labels[0] = new QLabel("Account id: ", this);
    labels[1] = new QLabel("Balance: ", this);
    labels[2] = new QLabel("Bank id: ", this);
    labels[3] = new QLabel("Market id: ", this);

    for (int i = 0; i < 4; i++) {
        labels[i]->move(10, 10 + 50 * i);
        labels[i]->setFont(font);
        labels[i]->show();
    }

    buttons[0] = new QPushButton("Insert data", this);
    buttons[1] = new QPushButton("Bank usage statistics", this);
    buttons[2] = new QPushButton("Stock market usage", this);
    buttons[3] = new QPushButton("Delete note from the table", this);
    buttons[4] = new QPushButton("Clear the table", this);


    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClickedStockMarketUsage()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClickedBalanceChangeEachYear()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));
    connect(buttons[4], SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));

    for (int i = 0; i < 5; i++) {
        buttons[i]->setFixedSize(200, 120);
        buttons[i]->setFont(QFont("Arial", 10, QFont::Bold));
        buttons[i]->setStyleSheet("background-color: blue;");
    }

    layout_ = new QHBoxLayout();
    for (int i = 0; i < 5; i++)
        layout_->addWidget(buttons[i]);

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("account.jpg");
    img = img.scaled(500, 500);
    label_ = new QLabel(this);
    label_->setPixmap(img);
    label_->setAlignment(Qt::AlignCenter);
    vl_ = new QVBoxLayout();
    vl_->addWidget(label_);
    vl_->addLayout(layout_);
    centralWidget = new QWidget();
    centralWidget->setLayout(vl_);

    setCentralWidget(centralWidget);
    for (int i = 0; i < 4; i++) {
        insert_line[i] = new QLineEdit(this);
        insert_line[i]->move(100, 10 + 50 * i);
        insert_line[i]->setFixedWidth(100);
    }
    insert_line[0]->setPlaceholderText("123");
    insert_line[1]->setPlaceholderText("1234.5");
    insert_line[2]->setPlaceholderText("4");
    insert_line[3]->setPlaceholderText("2");

}

InsertAccount::~InsertAccount() {
    delete ui;
}

void InsertAccount::onButtonClicked() {
    std::string id, balance, bank_id, stock_id;

    id = insert_line[0]->text().toStdString();
    balance = insert_line[1]->text().toStdString();
    bank_id = insert_line[2]->text().toStdString();
    stock_id = insert_line[3]->text().toStdString();

    try {
        pqxx::work w(ConnectionTool::GetConnect());
        w.exec_params("INSERT INTO public.\"Account\" VALUES ($1, $2, $3, $4);", id, balance, bank_id, stock_id);
        w.commit();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
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
    try {
        if (res_query.empty())
            throw QException();
    }
    catch (...) {
        QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
    }

    series[0] = new QPieSeries();

    int totalUsage = 0;

    for (const auto &row: res_query) {
        totalUsage += row["percentage_of_usage"].as<double>();
    }

    for (const auto &row: res_query) {
        QString bank_name = QString::fromStdString(row["bank_name"].as<std::string>());
        double percentage_of_usage = row["percentage_of_usage"].as<double>();

        slice[0] = new QPieSlice(bank_name, percentage_of_usage);
        slice[0]->setLabel(QString("%1: %2%").arg(bank_name).arg(QString::number(percentage_of_usage, 'f', 2)));
        series[0]->append(slice[0]);
    }

    chart[0] = new QChart();
    chart[0]->addSeries(series[0]);
    chart[0]->setTitle("Banks usage percentage");

    chartview[0] = new QChartView(chart[0]);
    chartview[0]->setWindowTitle("PieChart");
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
    }

    series[1] = new QPieSeries();

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

    chart[1] = new QChart();
    chart[1]->addSeries(series[1]);
    chart[1]->setTitle("Stock markets usage percentage");

    chartview[1] = new QChartView(chart[1]);
    chartview[0]->setWindowTitle("PieChart");
    chartview[1]->show();
}


void InsertAccount::onButtonClickedDeleted() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("DELETE FROM public.\"Account\";");
        w.commit();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void InsertAccount::onButtonClickedDeletedOne() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        int id = insert_line[0]->text().toInt();
        w.exec_params("DELETE FROM public.\"Account\" WHERE id = $1", id);
        w.commit();
        for (int i = 0; i < 4; i++)
            insert_line[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}