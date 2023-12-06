#ifndef CURRENCYDATABASE_MYDIALOG_HPP
#define CURRENCYDATABASE_MYDIALOG_HPP

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QListWidget>
#include <QtCharts>
#include <QHeaderView>
#include <QTableWidget>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MyDialog; }
QT_END_NAMESPACE

class MyDialog : public QDialog {
Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr, bool is_sell = true, int id = 0, QListWidget *currency_list = nullptr,
                      std::unordered_map<std::string, double> currency_amount_ = {},
                      QLabel *current_balance_ = nullptr);

    ~MyDialog() override;

private slots:

    void onButtonClickedHistoryTransactions();

    void onButtonClickedOk();

private:
    std::unordered_map<std::string, double> currency_amount;
    Ui::MyDialog *ui;
    QComboBox *currency_to_buy;
    QListWidget *currency_list;
    QHBoxLayout *occupation;
    QPushButton *ok;
    QPushButton *transaction_journal;
    QLabel *current_balance;
    bool is_sell_;
    int account_id;
};


#endif
