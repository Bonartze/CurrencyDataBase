#ifndef UNTITLED87_MAINWINDOW_HPP
#define UNTITLED87_MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QObject>
#include <QMainWindow>
#include <vector>
#include <pqxx/pqxx>
#include <exception>
#include "insertbank.hpp"
#include "insertaccount.hpp"
#include "insertcurrency.hpp"
#include "auntification.hpp"
#include "transaction.hpp"
#include "stockmarket.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    virtual ~MainWindow() override;

private slots:

    void onButtonClickedBankManage();

    void onButtonClickedAccountManage();

    void onButtonClickedCurrencyManage();

    void onButtonClickedStockMarketManage();

    void onButtonClickedTransactionManage();

    void onButtonClickedAuntificationManage();

private:
    QVBoxLayout *menuLayout;
    QVBoxLayout *contentLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *vl;
    QHBoxLayout *layout;
    QLabel *label;
    Ui::MainWindow *ui;
    std::vector<QWidget *> windows_for_insert;
    QWidget *auntification;
    std::vector<QPushButton *> insert_buttons;
    QStackedWidget *stackedWidget;
};

#endif
