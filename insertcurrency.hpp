
#ifndef UNTITLED87_INSERTCURRENCY_HPP
#define UNTITLED87_INSERTCURRENCY_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertCurrency; }
QT_END_NAMESPACE

class InsertCurrency : public QWidget {
Q_OBJECT

public:
    explicit InsertCurrency(QWidget *parent = nullptr);

    ~InsertCurrency() override;

private slots:

    void onButtonClicked();

    void onButtonClickedDeleted();

    void onButtonClickedDeletedOne();

    void onButtonCLickedChart();


private:
    QPieSeries *series;
    QPieSlice *slice;
    QChart *chart;
    QChartView *chartview;
    std::vector<QLineEdit *> insert_currency_line;
    Ui::InsertCurrency *ui;
    QPushButton *insert_into_currency;
    QPushButton *delete_table;
    QPushButton *delete_one;
    QPushButton *currency_chart;

};


#endif //UNTITLED87_INSERTCURRENCY_HPP
