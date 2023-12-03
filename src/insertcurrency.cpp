
#include "insertcurrency.hpp"
#include "ui_InsertCurrency.h"


InsertCurrency::InsertCurrency(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::InsertCurrency) {

    ui->setupUi(this);
    buttons = new QPushButton("Currency popularity statistics", this);
    buttons->setFixedSize(800, 120);
    buttons->setFont(QFont("Arial", 12, QFont::Bold));
    buttons->setStyleSheet("QPushButton {"
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


    connect(buttons, SIGNAL(clicked()), this, SLOT(onButtonCLickedChart()));

    layout_ = new QHBoxLayout();
    layout_->addWidget(buttons);
    layout_->setAlignment(Qt::AlignCenter);
    layout_->setSpacing(20);
    QPixmap img("cc.jpg");
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
}


InsertCurrency::~InsertCurrency() {
    delete ui;
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

        for (const auto &row: res_query) {
            totalTransactions += row["transaction_count"].as<int>();
        }

        for (const auto &row: res_query) {
            QString currency_name = QString::fromStdString(row["name"].as<std::string>());
            int transaction_count = row["transaction_count"].as<int>();
            double percentage = (static_cast<double>(transaction_count) / totalTransactions) ;
            slice = new QPieSlice(currency_name, percentage);
            series->append(slice);
        }

        chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Currency popularity");

        chartview = new QChartView(chart);
        chartview->setWindowTitle("CurrencyPieUsage");

        chart->setTheme(QChart::ChartThemeDark);

        chartview = new QChartView(chart);
        chartview->setWindowTitle("CurrencyPieUsage");

        QPalette pal = chartview->palette();
        pal.setColor(QPalette::Window, QColor(53, 53, 53));
        pal.setColor(QPalette::WindowText, Qt::white);
        chartview->setPalette(pal);

        for (const auto &slice: series->slices()) {
            slice->setLabel(QString("%1%\n%2").arg(QString::number(slice->percentage()*100, 'f', 1)).arg(slice->label()));
        }
        chartview->setFixedSize(600, 600);

        chartview->setRenderHint(QPainter::Antialiasing);

        chartview->show();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}



