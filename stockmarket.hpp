
#ifndef UNTITLED87_STOCKMARKET_HPP
#define UNTITLED87_STOCKMARKET_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QStringList>
#include <QCategoryAxis>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QVBoxLayout>
#include <QLabel>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class StockMarket; }
QT_END_NAMESPACE

class StockMarket : public QMainWindow {
Q_OBJECT

public:
    explicit StockMarket(QWidget *parent = nullptr);

    ~StockMarket() override;

private slots:

    void onButtonClickedDeleted();

    void onButtonClickedDeletedOne();

    void onButtonClicked();

    void onButtonClickedIncomeCurrency();

private:
    std::vector<QLineEdit *> insert_stock_market_line;
    Ui::StockMarket *ui;

    std::vector<QPushButton *> buttons;
    std::vector<QLabel *> labels;

    QtCharts::QBarSet *barSet;
    QtCharts::QChart *chart;
    QtCharts::QBarCategoryAxis *axisX;
    QtCharts::QChartView *chartView;
    QtCharts::QValueAxis *axisY;


    QHBoxLayout *layout_;
    QVBoxLayout *vl_;
    QLabel *label_;
    QWidget *centralWidget;
};


#endif
