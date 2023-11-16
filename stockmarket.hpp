
#ifndef UNTITLED87_STOCKMARKET_HPP
#define UNTITLED87_STOCKMARKET_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
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

    void onButtonClicked();

private:
    std::vector<QLineEdit *> insert_stock_market_line;
    Ui::StockMarket *ui;
    QPushButton *insert_into_stock_market;
};


#endif //UNTITLED87_STOCKMARKET_HPP
