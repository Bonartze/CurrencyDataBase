

#include "transaction.hpp"
#include "ui_Transaction.h"

Transaction::Transaction(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Transaction) {
    ui->setupUi(this);

    buttons = new QPushButton("Get transaction statistics", this);

    connect(buttons, SIGNAL(clicked()), this, SLOT(onButtonClickedTransactionStatistics()));

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

    layout_ = new QHBoxLayout();
    layout_->addWidget(buttons);
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
}

Transaction::~Transaction() {
    delete ui;
}


void Transaction::onButtonClickedTransactionStatistics() {
    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto query_res = w.exec("SELECT "
                                "\"Transaction\".date, "
                                "SUM(\"Transaction\".amount) AS Got "
                                "FROM public.\"Transaction\" "
                                "JOIN public.\"Account\" ON public.\"Account\".id = public.\"Transaction\".account_id_from "
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

        chart->setTheme(QtCharts::QChart::ChartThemeDark);

        chart->addSeries(series);
        chart->setTitle("Transaction Statistics");

        axisX = new QtCharts::QBarCategoryAxis();
        axisX->append(categories);
        axisX->setTitleText("Years");

        axisX->setLabelsColor(QColor(255, 255, 255));
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        axisY = new QtCharts::QValueAxis();
        axisY->setTitleText("Transacted Money");

        axisY->setLabelsColor(QColor(255, 255, 255));
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chartView = new QtCharts::QChartView(chart);

        QPalette chartViewPalette = chartView->palette();
        chartViewPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        chartViewPalette.setColor(QPalette::WindowText, Qt::white);
        chartView->setPalette(chartViewPalette);

        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setWindowTitle("DiagramTransaction");
        chartView->setFixedSize(600, 600);
        chartView->show();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
    }
}


