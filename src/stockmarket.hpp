
#ifndef UNTITLED87_STOCKMARKET_HPP
#define UNTITLED87_STOCKMARKET_HPP

#include <QMainWindow>
#include <QException>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QtCharts/QChartView>
#include <QPieSeries>
#include <QDateTime>
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

    void onButtonClickedIncomeCurrency();

private:
    Ui::StockMarket *ui;

    QPushButton *button;

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
