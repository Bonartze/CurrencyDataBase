

#include "mainwindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    try {
        pqxx::connection c(
                "user=postgres password=123 host=127.0.0.1 port=5432 dbname=postgres target_session_attrs=read-write");
    } catch (...) {
        QMessageBox::critical(nullptr, "Error", "Can't connect to Data base", QMessageBox::Ok);
    }

    ui->setupUi(this);


    insert_buttons.resize(6);
    windows_for_insert.resize(5);
    windows_for_insert[0] = new InsertBank();
    windows_for_insert[1] = new InsertAccount();
    windows_for_insert[2] = new InsertCurrency();
    windows_for_insert[3] = new StockMarket();
    windows_for_insert[4] = new Transaction();

    insert_buttons[0] = new QPushButton("Manage table \"Bank\"", this);
    insert_buttons[1] = new QPushButton("Manage table \"Account\"", this);
    insert_buttons[2] = new QPushButton("Manage table \"Currency\"", this);
    insert_buttons[3] = new QPushButton("Manage table \"StockMarket\"", this);
    insert_buttons[4] = new QPushButton("Manage table \"Transaction\"", this);
    insert_buttons[5] = new QPushButton("Clear all the tables", this);

    for (int i = 0; i < 6; i++) {
        insert_buttons[i]->setFixedSize(280, 200);
        insert_buttons[i]->setFont(QFont("Arial", 14, QFont::Bold));
        insert_buttons[i]->setStyleSheet("background-color: blue;");
    }

    vl = new QVBoxLayout(this);
    QPixmap img("menu.jpg");
    img = img.scaledToWidth(1825);
    label = new QLabel(this);
    label->setPixmap(img);

    layout = new QHBoxLayout(this);
    layout->setSpacing(20);
    for (int i = 0; i < 6; i++)
        layout->addWidget(insert_buttons[i]);

    layout->setAlignment(Qt::AlignCenter);

    vl->addWidget(label, 0, Qt::AlignCenter);
    vl->addLayout(layout);


    connect(insert_buttons[0], SIGNAL(clicked()), this, SLOT(onButtonClicked0()));
    connect(insert_buttons[1], SIGNAL(clicked()), this, SLOT(onButtonClicked1()));
    connect(insert_buttons[2], SIGNAL(clicked()), this, SLOT(onButtonClicked2()));
    connect(insert_buttons[3], SIGNAL(clicked()), this, SLOT(onButtonClicked3()));
    connect(insert_buttons[4], SIGNAL(clicked()), this, SLOT(onButtonClicked4()));
    connect(insert_buttons[5], SIGNAL(clicked()), this, SLOT(onButtonClicked5()));
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

void MainWindow::onButtonClicked5() {
    auto reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to do this action?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        try {
            pqxx::work w(ConnectionTool::GetConnect());
            auto res_query = w.exec("DELETE FROM public.\"Transaction\";\n"
                                    "DELETE FROM public.\"Account\";\n"
                                    "DELETE FROM public.\"StockMarket\";\n"
                                    "DELETE FROM public.\"Bank\";\n"
                                    "DELETE FROM public.\"Currency\";\n");
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    }
}