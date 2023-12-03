
#ifndef UNTITLED87_INSERTCURRENCY_HPP
#define UNTITLED87_INSERTCURRENCY_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QMainWindow>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertCurrency; }
QT_END_NAMESPACE

class InsertCurrency : public QMainWindow {
Q_OBJECT

public:
    explicit InsertCurrency(QWidget *parent = nullptr);

    ~InsertCurrency() override;

private slots:

    void onButtonCLickedChart();


private:
    QPieSeries *series;
    QPieSlice *slice;
    QChart *chart;
    QChartView *chartview;

    Ui::InsertCurrency *ui;

    QPushButton * buttons;

    QHBoxLayout *layout_;
    QVBoxLayout *vl_;
    QLabel *label_;
    QWidget *centralWidget;

};


#endif
