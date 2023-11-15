
#ifndef UNTITLED87_STOCKMARKET_HPP
#define UNTITLED87_STOCKMARKET_HPP

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class StockMarket; }
QT_END_NAMESPACE

class StockMarket : public QMainWindow {
Q_OBJECT

public:
    explicit StockMarket(QWidget *parent = nullptr);

    ~StockMarket() override;

private:
    Ui::StockMarket *ui;
};


#endif //UNTITLED87_STOCKMARKET_HPP
