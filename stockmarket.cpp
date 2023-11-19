

#include "stockmarket.hpp"
#include "ui_StockMarket.h"


StockMarket::StockMarket(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StockMarket) {
    ui->setupUi(this);
    buttons.resize(4);
    insert_stock_market_line.resize(5);
    labels.resize(5);
    QFont font("Arial", 10, QFont::Bold);
    buttons[0] = new QPushButton("Insert data", this);
    buttons[1] = new QPushButton("Get statistics of currency's sales", this);
    buttons[3] = new QPushButton("Clear the table", this);
    buttons[2] = new QPushButton("Delete note from the table", this);

    for (int i = 0; i < 4; i++) {
        buttons[i]->setFixedSize(300, 200);
        buttons[i]->move(100, 10 + 50 * i);
        buttons[i]->setFont(QFont("Arial", 14, QFont::Bold));
        buttons[i]->setStyleSheet("background-color: blue;");
    }

    connect(buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClickedIncomeCurrency()));
    connect(buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClickedDeleted()));
    connect(buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClickedDeletedOne()));
    layout_ = new QHBoxLayout();
    for (int i = 0; i < 4; i++)
        layout_->addWidget(buttons[i]);

    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("currency.jpg");
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

    insert_stock_market_line.resize(5);
    for (int i = 0; i < 5; i++) {
        insert_stock_market_line[i] = new QLineEdit(this);
        insert_stock_market_line[i]->move(150, 10 + 50 * i);
        insert_stock_market_line[i]->setFixedWidth(200);
    }

    insert_stock_market_line[0]->setPlaceholderText("43");
    insert_stock_market_line[1]->setPlaceholderText("12");
    insert_stock_market_line[2]->setPlaceholderText("13");
    insert_stock_market_line[3]->setPlaceholderText("43.4");
    insert_stock_market_line[4]->setPlaceholderText("1973");


    labels[0] = new QLabel("Stock id: ", this);
    labels[1] = new QLabel("Currency-i id: ", this);
    labels[2] = new QLabel("Currency-o id: ", this);
    labels[3] = new QLabel("Rate: ", this);
    labels[4] = new QLabel("Date (year): ", this);

    for (int i = 0; i < 5; i++) {
        labels[i]->move(5, 10 + 50 * i);
        labels[i]->setFont(font);
        labels[i]->show();
    }
}

StockMarket::~StockMarket() {
    delete ui;
}

void StockMarket::onButtonClicked() {
    try {
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
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void StockMarket::onButtonClickedIncomeCurrency() {
    try {
        using namespace QtCharts;
        QBarSeries *series = new QBarSeries();
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("SELECT public.\"Currency\".name, SUM(public.\"StockMarket\".rate) \n"
                                "FROM public.\"Currency\"\n"
                                "JOIN public.\"StockMarket\" ON public.\"StockMarket\".currecny_id_to = public.\"Currency\".id\n"
                                "GROUP BY public.\"Currency\".name\n"
                                "ORDER BY SUM(public.\"StockMarket\".rate) DESC;");
        try {
            if (res_query.empty())
                throw new QException();
        }
        catch (...) {
            QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
        }
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
        chartView->setWindowTitle("Diagram");
        chartView->show();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void StockMarket::onButtonClickedDeleted() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec("DELETE FROM public.\"StockMarket\";");
        w.commit();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}

void StockMarket::onButtonClickedDeletedOne() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        int id = insert_stock_market_line[0]->text().toInt();
        w.exec_params("DELETE FROM public.\"StockMarket\" WHERE id = $1", id);
        w.commit();
        for (int i = 0; i < 5; i++)
            insert_stock_market_line[i]->clear();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}