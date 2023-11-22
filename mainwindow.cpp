

#include "mainwindow.hpp"
#include "ui_MainWindow.h"
#include "ConnectionTool.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    insert_buttons.resize(6);
    windows_for_insert.resize(5);
    windows_for_insert[0] = new InsertBank();
    windows_for_insert[1] = new InsertAccount();
    windows_for_insert[2] = new InsertCurrency();
    windows_for_insert[3] = new StockMarket();
    windows_for_insert[4] = new Transaction();
    auntification = new Auntification();
    stackedWidget = new QStackedWidget();

    insert_buttons[0] = new QPushButton("Bank's statistics", this);
    insert_buttons[1] = new QPushButton("Account's statistics", this);
    insert_buttons[2] = new QPushButton("Currency's statistics", this);
    insert_buttons[3] = new QPushButton("Stock market's statistics", this);
    insert_buttons[4] = new QPushButton("Transaction's statistics", this);
    insert_buttons[5] = new QPushButton("Authorization", this);

    for (int i = 0; i < 5; i++) {
        insert_buttons[i]->setFixedSize(200, 120);
        insert_buttons[i]->setFont(QFont("Arial", 10, QFont::Bold));
        //    insert_buttons[i]->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none; color: black;");
        insert_buttons[i]->setStyleSheet("background-color: blue;");
    }
    insert_buttons[5]->setFixedSize(280, 170);
    insert_buttons[5]->setFont(QFont("Arial", 14, QFont::Bold));
    insert_buttons[5]->setStyleSheet("background-color: red;");
    for (auto &window: windows_for_insert) {
        stackedWidget->addWidget(window);
    }
    stackedWidget->addWidget(auntification);

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);

    menuLayout = new QVBoxLayout();
    contentLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout(this);

    for (int i = 0; i < 6; i++)
        menuLayout->addWidget(insert_buttons[i]);

    contentLayout->addWidget(stackedWidget);
    contentLayout->addWidget(label);

    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(contentLayout);

    mainLayout->setAlignment(Qt::AlignTop);

    connect(insert_buttons[0], &QPushButton::clicked, this, &MainWindow::onButtonClickedBankManage);
    connect(insert_buttons[1], &QPushButton::clicked, this, &MainWindow::onButtonClickedAccountManage);
    connect(insert_buttons[2], &QPushButton::clicked, this, &MainWindow::onButtonClickedCurrencyManage);
    connect(insert_buttons[3], &QPushButton::clicked, this, &MainWindow::onButtonClickedStockMarketManage);
    connect(insert_buttons[4], &QPushButton::clicked, this, &MainWindow::onButtonClickedTransactionManage);
    connect(insert_buttons[5], &QPushButton::clicked, this, &MainWindow::onButtonClickedAuntificationManage);

}


MainWindow::~MainWindow() {
    delete ui;
    delete vl;
    delete layout;
    delete label;
    for (auto &a: windows_for_insert) {
        delete a;
        a = nullptr;
    }
    auntification->hide();
    delete auntification;
    for (auto &b: insert_buttons) {
        delete b;
        b = nullptr;
    }
    ui = nullptr;
    vl = nullptr;
    layout = nullptr;
    label = nullptr;

}

void MainWindow::onButtonClickedBankManage() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::onButtonClickedAccountManage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::onButtonClickedCurrencyManage() {
    stackedWidget->setCurrentIndex(2);
}


void MainWindow::onButtonClickedStockMarketManage() {
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::onButtonClickedTransactionManage() {
    stackedWidget->setCurrentIndex(4);
}

void MainWindow::onButtonClickedAuntificationManage() {
    stackedWidget->setCurrentIndex(5);
}


