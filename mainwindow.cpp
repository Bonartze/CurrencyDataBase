

#include "mainwindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    try {
        pqxx::connection c(
                "user=postgres password=123 host=127.0.0.1 port=5432 dbname=postgres target_session_attrs=read-write");
    } catch (...) {

    }

    ui->setupUi(this);
    insert_buttons.resize(5);
    windows_for_insert.resize(5);
    windows_for_insert[0] = new InsertBank();
    windows_for_insert[1] = new InsertAccount();
    windows_for_insert[2] = new InsertCurrency;
    windows_for_insert[3] = new StockMarket();
    windows_for_insert[4] = new Transaction();

    insert_buttons[0] = new QPushButton("Manage table \"Bank\"", this);
    insert_buttons[1] = new QPushButton("Manage table \"Account\"", this);
    insert_buttons[2] = new QPushButton("Manage table \"Currency\"", this);
    insert_buttons[3] = new QPushButton("Manage table \"StockMarket\"", this);
    insert_buttons[4] = new QPushButton("Manage table \"Transaction\"", this);

    insert_buttons[0]->setGeometry(10, 10, 400, 30);
    insert_buttons[1]->setGeometry(10, 50, 400, 30);
    insert_buttons[2]->setGeometry(10, 90, 400, 30);
    insert_buttons[3]->setGeometry(10, 130, 400, 30);
    insert_buttons[4]->setGeometry(10, 170, 400, 30);

    connect(insert_buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked0()));
    connect(insert_buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClicked1()));
    connect(insert_buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClicked2()));
    connect(insert_buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClicked3()));
    connect(insert_buttons[4], SIGNAL(clicked()), this, SLOT(onButtonClicked4()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onButtonClicked0() {
    windows_for_insert[0]->show();
}

void MainWindow::onButtonClicked1() {
    windows_for_insert[1]->show();
}

void MainWindow::onButtonClicked2() {
    windows_for_insert[2]->show();
}

void MainWindow::onButtonClicked3() {
    windows_for_insert[3]->show();
}

void MainWindow::onButtonClicked4() {
    windows_for_insert[4]->show();
}