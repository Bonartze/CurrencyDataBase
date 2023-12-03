#ifndef UNTITLED87_MAINWINDOW_HPP
#define UNTITLED87_MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QObject>
#include <fstream>
#include <QMainWindow>
#include <vector>
#include <pqxx/pqxx>
#include <exception>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include "insertbank.hpp"
#include "insertaccount.hpp"
#include "insertcurrency.hpp"
#include "auntification.hpp"
#include "transaction.hpp"
#include "stockmarket.hpp"
#include "managetables.hpp"


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

    void onButtonClickedManageTables();

private:
    QVBoxLayout *menuLayout;
    QVBoxLayout *contentLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *vl;
    QHBoxLayout *layout;
    QLabel *label;
    Ui::MainWindow *ui;
    std::vector<QWidget *> windows_for_insert;
    Auntification *auntification;
    std::vector<QPushButton *> insert_buttons;
    QNetworkAccessManager *manager;
};

#endif
