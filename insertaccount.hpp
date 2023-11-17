
#ifndef UNTITLED87_INSERTACCOUNT_HPP
#define UNTITLED87_INSERTACCOUNT_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertAccount; }
QT_END_NAMESPACE

class InsertAccount : public QWidget {
Q_OBJECT
public:
    explicit InsertAccount(QWidget *parent = nullptr);

    ~InsertAccount() override;

private slots:

    void onButtonClicked();

    void onButtonClickedDeleted();

    void onButtonClickedDeletedOne();

    void onButtonClickedBalanceChangeEachYear();

    void onButtonClickedStockMarketUsage();

private:
    std::vector<QLineEdit *> insert_line;
    Ui::InsertAccount *ui;
    QPushButton *bank_usage;
    QPushButton *stock_market_usage;
    QPushButton *insert_into_account;
    QPushButton *delete_table;
    QPushButton *delete_one;
    std::vector<QPieSeries *> series;
    std::vector<QPieSlice *> slice;
    std::vector<QChart *> chart;
    std::vector<QChartView *> chartview;
};

#endif
