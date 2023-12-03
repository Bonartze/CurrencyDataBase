#ifndef UNTITLED87_TRANSACTION_HPP
#define UNTITLED87_TRANSACTION_HPP

#include <QPushButton>
#include <QValueAxis>
#include <QMessageBox>
#include <QException>
#include <QFont>
#include <QMainWindow>
#include <QLineEdit>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QLabel>

#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Transaction; }
QT_END_NAMESPACE

class Transaction : public QMainWindow {
Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);

    ~Transaction() override;

private slots:

    void onButtonClickedTransactionStatistics();


private:
    QtCharts::QBarSet *barSet;
    QtCharts::QBarSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QBarCategoryAxis *axisX;
    QtCharts::QChartView *chartView;
    QtCharts::QValueAxis *axisY;

    QPushButton *buttons;

    QLabel *label_;
    QHBoxLayout *layout_;
    QVBoxLayout *vl_;
    QWidget *centralWidget;

    Ui::Transaction *ui;

};


#endif
