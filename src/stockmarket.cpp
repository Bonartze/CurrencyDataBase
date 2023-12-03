

#include "stockmarket.hpp"
#include "ui_StockMarket.h"


StockMarket::StockMarket(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StockMarket) {
    ui->setupUi(this);
    button = new QPushButton("Get statistics of currency's sales", this);
    button->setFixedSize(800, 120);
    button->setFont(QFont("Arial", 12, QFont::Bold));
    button->setStyleSheet("QPushButton {"
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
    connect(button, SIGNAL(clicked()), this, SLOT(onButtonClickedIncomeCurrency()));
    layout_ = new QHBoxLayout();
    layout_->addWidget(button);
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
}

StockMarket::~StockMarket() {
    delete ui;
}


void StockMarket::onButtonClickedIncomeCurrency() {
    using namespace QtCharts;

    try {
        pqxx::work w(ConnectionTool::GetConnect());
        auto res_query = w.exec(
                "SELECT sm.date AS year, COALESCE(SUM(sm.amount), 0) AS total_stock_amount "
                "FROM public.\"StockMarket\" sm "
                "LEFT OUTER JOIN public.\"Account\" a ON sm.id = a.stock_id "
                "GROUP BY year;");

        QPieSeries *series = new QPieSeries();
        QChart *chart = new QChart();
        QChartView *chartView = new QChartView(chart);

        chart->setTheme(QChart::ChartThemeDark);

        QVector<QColor> sliceColors = {QColor(30, 130, 76), QColor(214, 48, 49), QColor(244, 208, 63),
                                       QColor(66, 133, 244), QColor(232, 126, 4), QColor(153, 102, 255),
                                       QColor(255, 193, 7), QColor(0, 123, 255), QColor(255, 61, 127)};

        int colorIndex = 0;

        for (const auto &row: res_query) {
            int year = row["year"].as<int>();
            qreal totalAmount = row["total_stock_amount"].as<qreal>();

            QPieSlice *slice = new QPieSlice(QString::number(year), totalAmount);
            slice->setBrush(sliceColors[colorIndex % sliceColors.size()]);
            slice->setLabel(QString("%1: %2").arg(QString::number(year), QString::number(totalAmount, 'f', 1)));
            series->append(slice);

            colorIndex++;
        }

        chart->addSeries(series);

        chart->setTitle("Common income of stock markets");
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignTop);

        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setWindowTitle("StockMarketDataPieChart");

        QPalette chartViewPalette = chartView->palette();
        chartViewPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        chartViewPalette.setColor(QPalette::WindowText, Qt::white);
        chartView->setPalette(chartViewPalette);

        chartView->setFixedSize(600, 600);

        chartView->show();
    }
    catch (std::exception &ex) {
        QMessageBox::critical(nullptr, "Error", "Empty query result", QMessageBox::Ok);
        return;
    }
}

