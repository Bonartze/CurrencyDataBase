
#include "insertcurrency.hpp"
#include "ui_InsertCurrency.h"


InsertCurrency::InsertCurrency(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::InsertCurrency) {

    buttons.resize(4);
    insert_currency_line.resize(2);
    labels.resize(2);

    ui->setupUi(this);
    buttons[0] = new QPushButton("Insert data", this);
    buttons[1] = new QPushButton("Clear the table", this);
    buttons[2] = new QPushButton("Delete note from the table", this);
    buttons[3] = new QPushButton("Display currency popularity statistics", this);

    for (int i = 0; i < 4; i++) {
        buttons[i]->setFixedSize(300, 200);
        buttons[i]->setStyleSheet("background-color: blue;");
    }

    labels[0] = new QLabel("Currency id: ", this);
    labels[1] = new QLabel("Name: ", this);
    for (int i = 0; i < 2; i++) {
        labels[i]->move(10, 10 + 50 * i);
        labels[i]->show();
    }

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));

    layout_ = new QHBoxLayout();
    for (int i = 0; i < 4; i++) {
        layout_->addWidget(buttons[i]);
    }

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("account.jpg");
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
        insert_currency_line[i]->setFixedWidth(200);
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
