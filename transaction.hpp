#ifndef UNTITLED87_TRANSACTION_HPP
#define UNTITLED87_TRANSACTION_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Transaction; }
QT_END_NAMESPACE

class Transaction : public QWidget {
Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);

    ~Transaction() override;

private slots:

    void onButtonClickedDeleted();

    void onButtonClickedDeletedOne();


    void onButtonClicked();

    void onButtonClickedTransactionStatistics();


private:
    QtCharts::QBarSet *barSet;
    QtCharts::QBarSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QBarCategoryAxis *axisX;
    QtCharts::QChartView *chartView;
    QtCharts::QValueAxis *axisY;
    std::vector<QLineEdit *> insert_transaction_line;
    QPushButton *transaction_statistics;
    QPushButton *insert_into_transaction;
    QPushButton *delete_table;
    QPushButton *delete_one;
    Ui::Transaction *ui;
};


#endif
