#include "insertbank.hpp"
#include "ui_InsertBank.h"


InsertBank::InsertBank(QWidget *parent) : QMainWindow(parent), ui(new Ui::InsertBank) {
    ui->setupUi(this);
    labels.resize(2);
    buttons.resize(4);
    QFont font("Arial", 10, QFont::Bold);
    labels[0] = new QLabel("Bank id: ", this);
    labels[1] = new QLabel("Name: ", this);
    for (int i = 0; i < 2; i++) {
        labels[i]->move(10, 10 + 50 * i);
        labels[i]->setFont(font);
        labels[i]->show();
    }

    buttons[1] = new QPushButton("Display bank usage statistics", this);
    buttons[3] = new QPushButton("Clear the table", this);
    buttons[0] = new QPushButton("Insert data", this);
    buttons[2] = new QPushButton("Delete note from the table", this);


    for (int i = 0; i < 4; i++) {
        buttons[i]->setFixedSize(300, 200);
        buttons[i]->setStyleSheet("background-color: blue;");
        buttons[i]->setFont(QFont("Arial", 14, QFont::Bold));
    }

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));

    insert_line_bank.resize(2);


    layout_ = new QHBoxLayout();
    for (int i = 0; i < 4; i++)
        layout_->addWidget(buttons[i]);

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("bank.jpg");
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
    for (int i = 0; i < 2; i++) {
        insert_line_bank[i] = new QLineEdit(this);
        insert_line_bank[i]->move(100, 10 + 50 * i);
        insert_line_bank[i]->setFixedWidth(200);
    }
    insert_line_bank[0]->setPlaceholderText("12");
    insert_line_bank[1]->setPlaceholderText("SDM");

}

InsertBank::~InsertBank() {
    delete ui;
}

void InsertBank::onButtonClicked() {
    try {
        std::string id = insert_line_bank[0]->text().toStdString();
        std::string name = insert_line_bank[1]->text().toStdString();
        pqxx::work w(ConnectionTool::GetConnect());
        w.exec_params("INSERT INTO public.\"Bank\" VALUES ($1, $2);", id, name);
        w.commit();
        for (int i = 0; i < 2; i++)
            insert_line_bank[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
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

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Banks usage");

    chartview = new QChartView(chart);
    chartview->setWindowTitle("PieChart");
    chartview->show();
}


void InsertBank::onButtonClickedDeleted() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("DELETE FROM public.\"Bank\";");
        w.commit();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void InsertBank::onButtonClickedDeletedOne() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        int id = insert_line_bank[0]->text().toInt();
        w.exec_params("DELETE FROM public.\"Bank\" WHERE id = $1", id);
        w.commit();
        for (int i = 0; i < 2; i++)
            insert_line_bank[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}