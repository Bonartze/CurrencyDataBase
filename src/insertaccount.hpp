
#ifndef UNTITLED87_INSERTACCOUNT_HPP
#define UNTITLED87_INSERTACCOUNT_HPP

#include <QMessageBox>
#include <QWidget>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QMainWindow>
#include <exception>

#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertAccount; }
QT_END_NAMESPACE

class InsertAccount : public QMainWindow {
Q_OBJECT
public:
    explicit InsertAccount(QWidget *parent = nullptr);

    ~InsertAccount() override;

private slots:

    void onButtonClickedBalanceChangeEachYear();

    void onButtonClickedStockMarketUsage();

private:
    Ui::InsertAccount *ui;

    std::vector<QPushButton *> buttons;

    std::vector<QPieSeries *> series;
    std::vector<QPieSlice *> slice;
    std::vector<QChart *> chart;
    std::vector<QChartView *> chartview;

    QLabel *label_;

    QHBoxLayout *layout_;
    QVBoxLayout *vl_;
    QWidget *centralWidget;
};

#endif
