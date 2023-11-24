

#include "transaction.hpp"
#include "ui_Transaction.h"

Transaction::Transaction(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Transaction) {
    ui->setupUi(this);
    buttons.resize(4);
    insert_transaction_line.resize(4);
    labels.resize(4);

    labels[0] = new QLabel("Transaction id: ", this);
    labels[1] = new QLabel("Account id-i: ", this);
    labels[2] = new QLabel("Amount: ", this);
    labels[3] = new QLabel("Date (year): ", this);
    QFont font("Arial", 10, QFont::Bold);
    for (int i = 0; i < 4; i++) {
        labels[i]->move(2, 10 + 50 * i);
        labels[i]->setFont(font);
        labels[i]->show();
    }

    buttons[0] = new QPushButton("Insert data", this);
    buttons[1] = new QPushButton("Get transaction statistics", this);
    buttons[3] = new QPushButton("Clear the table", this);
    buttons[2] = new QPushButton("Delete note from the table", this);

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClickedTransactionStatistics()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));

    for (int i = 0; i < 4; i++) {
        buttons[i]->setFixedSize(200, 120);
        buttons[i]->setFont(QFont("Arial", 10, QFont::Bold));
        buttons[i]->setStyleSheet("background-color: blue;");

    }
    layout_ = new QHBoxLayout();
    for (int i = 0; i < 4; i++)
        layout_->addWidget(buttons[i]);

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("transaction.jpg");
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
        insert_transaction_line[i] = new QLineEdit(this);

        insert_transaction_line[i]->move(100, 10 + 50 * i);
        insert_transaction_line[i]->setFixedWidth(100);
    }
    insert_transaction_line[0]->setPlaceholderText("43");
    insert_transaction_line[1]->setPlaceholderText("12");
    insert_transaction_line[2]->setPlaceholderText("1242.3029");
    insert_transaction_line[3]->setPlaceholderText("1999");
    
}

Transaction::~Transaction() {
    delete ui;
}

void Transaction::onButtonClicked() {
    try {
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
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }

}

void Transaction::onButtonClickedTransactionStatistics() {
    try {
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
        try {
            if (query_res.empty())
                throw QException();
        }
        catch (...) {
            QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
            return;
        }

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
        chartView->setWindowTitle("Diagram");
        chartView->setFixedSize(600, 600);
        chartView->show();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void Transaction::onButtonClickedDeleted() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("DELETE FROM public.\"Transaction\";");
        w.commit();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void Transaction::onButtonClickedDeletedOne() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        int id = insert_transaction_line[0]->text().toInt();
        w.exec_params("DELETE FROM public.\"Transaction\" WHERE id = $1", id);
        w.commit();
        for (int i = 0; i < 4; i++)
            insert_transaction_line[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}