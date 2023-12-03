#ifndef CURRENCYDATABASE_ACCOUNT_HPP
#define CURRENCYDATABASE_ACCOUNT_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QtMath>
#include <iomanip>
#include <QDateTimeAxis>
#include <QDateTime>
#include <QTimer>
#include <QListWidget>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDialog>
#include "ConnectionTool.hpp"
#include "mydialog.hpp"

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class Account; }
QT_END_NAMESPACE

class Account : public QWidget {
Q_OBJECT
private slots:

    void print_graph();

public:

    explicit Account(QWidget *parent = nullptr, int id = 0);

    ~Account() override;

private slots:

    void onButtonClickedBuy();

    void onButtonClickedTopUp();

    void onButtonClickedSell();


private:
    Ui::Account *ui;
    QLabel *current_balance;
    QComboBox *crypto_choice;
    QPushButton *top_up;
    QPushButton *create_graph;
    QListWidget *currency_list;
    QPushButton *buy;
    QPushButton *sell;
    int account_id;
    double balance = 0.0;
    std::unordered_map<std::string, double> currency_amount; //currency and its amount user owns
};


#endif
