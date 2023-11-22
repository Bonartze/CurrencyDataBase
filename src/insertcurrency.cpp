
#include "insertcurrency.hpp"
#include "ui_InsertCurrency.h"


InsertCurrency::InsertCurrency(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::InsertCurrency) {

    buttons.resize(4);
    insert_currency_line.resize(2);
    labels.resize(2);
    QFont font("Arial", 10, QFont::Bold);
    ui->setupUi(this);
    buttons[0] = new QPushButton("Insert data", this);
    buttons[3] = new QPushButton("Clear the table", this);
    buttons[2] = new QPushButton("Delete note from the table", this);
    buttons[1] = new QPushButton("Currency popularity statistics", this);

    for (int i = 0; i < 4; i++) {
        buttons[i]->setFixedSize(200, 120);
        buttons[i]->setFont(QFont("Arial", 10, QFont::Bold));
        buttons[i]->setStyleSheet("background-color: blue;");
    }

    labels[0] = new QLabel("Currency id: ", this);
    labels[1] = new QLabel("Name: ", this);
    for (int i = 0; i < 2; i++) {
        labels[i]->move(10, 10 + 50 * i);
        labels[i]->setFont(font);
        labels[i]->show();
    }

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));

    layout_ = new QHBoxLayout();
    for (int i = 0; i < 4; i++) {
        layout_->addWidget(buttons[i]);
    }

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("cc.png");
    img = img.scaled(400, 400);
    label_ = new QLabel(this);
    label_->setPixmap(img);
    label_->setAlignment(Qt::AlignCenter);
    vl_ = new QVBoxLayout();
    vl_->addWidget(label_);
    vl_->addLayout(layout_);
    centralWidget = new QWidget();
    centralWidget->setLayout(vl_);

    setCentralWidget(centralWidget);
    for (int i = 0; i < 2; i++) {
        insert_currency_line[i] = new QLineEdit(this);
        insert_currency_line[i]->move(100, 10 + 50 * i);
        insert_currency_line[i]->setFixedWidth(100);
    }
    insert_currency_line[0]->setPlaceholderText("43");
    insert_currency_line[1]->setPlaceholderText("WorldCoin");

}


InsertCurrency::~InsertCurrency() {
    delete ui;
}

void InsertCurrency::onButtonClicked() {
    try {
        std::string id = insert_currency_line[0]->text().toStdString();
        std::string name = insert_currency_line[1]->text().toStdString();
        pqxx::work w(ConnectionTool::GetConnect());
        w.exec_params("INSERT INTO public.\"Currency\" VALUES ($1, $2);", id, name);
        w.commit();
        for (int i = 0; i < 2; i++)
            insert_currency_line[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void InsertCurrency::onButtonClickedDeletedOne() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        int id = insert_currency_line[0]->text().toInt();
        w.exec_params("DELETE FROM public.\"Currency\" WHERE id = $1", id);
        w.commit();
        for (int i = 0; i < 2; i++)
            insert_currency_line[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void InsertCurrency::onButtonClickedDeleted() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("DELETE FROM public.\"Currency\";");
        w.commit();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void InsertCurrency::onButtonCLickedChart() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("SELECT name as name, COUNT(id) as transaction_count\n"
                                "FROM public.\"Currency\" GROUP BY name;");
        try {
            if (res_query.empty()) {
                throw new QException();
            }
        }
        catch (...) {
            QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
        }

        series = new QPieSeries();

        int totalTransactions = 0;

        // Calculate total transactions
        for (const auto &row: res_query) {
            totalTransactions += row["transaction_count"].as<int>();
        }

        // Add slices to the chart
        for (const auto &row: res_query) {
            QString currency_name = QString::fromStdString(row["name"].as<std::string>());
            int transaction_count = row["transaction_count"].as<int>();
            double percentage = static_cast<double>(transaction_count) / totalTransactions * 100.0;

            slice = new QPieSlice(currency_name, percentage);
            series->append(slice);
        }

        chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Currency popularity");

        chartview = new QChartView(chart);
        chartview->show();
        chartview->setWindowTitle("PieChart");
        for (const auto &slice: series->slices()) {
            slice->setLabel(QString("%1%\n%2").arg(QString::number(slice->percentage(), 'f', 2)).arg(slice->label()));
        }
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}



