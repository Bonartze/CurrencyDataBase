

#include "mainwindow.hpp"
#include "ui_MainWindow.h"
#include "ConnectionTool.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    insert_buttons.resize(7);
    this->setStyleSheet("background-color: #303030; color: white;");
    windows_for_insert.resize(6);

    manager = new QNetworkAccessManager();

    auntification = new Auntification();
    windows_for_insert[0] = new InsertBank();
    windows_for_insert[1] = new InsertAccount();
    windows_for_insert[2] = new InsertCurrency();
    windows_for_insert[3] = new StockMarket();
    windows_for_insert[4] = new Transaction();
    windows_for_insert[5] = new ManageTables(nullptr, auntification->getStackedWidget()); //


    insert_buttons[0] = new QPushButton("Bank's statistics", this);
    insert_buttons[1] = new QPushButton("Account's statistics", this);
    insert_buttons[2] = new QPushButton("Currency's statistics", this);
    insert_buttons[3] = new QPushButton("Stock market's statistics", this);
    insert_buttons[4] = new QPushButton("Transaction's statistics", this);
    insert_buttons[5] = new QPushButton("Manage tables", this);
    insert_buttons[6] = new QPushButton("Authorization", this);

    for (int i = 0; i < 7; i++) {
        insert_buttons[i]->setFixedSize(150, 120);
        insert_buttons[i]->setFont(QFont("Arial", 10, QFont::Bold));
        insert_buttons[i]->setStyleSheet("QPushButton {"
                                         "    background-color: #333333;"
                                         "    color: #ffffff;"
                                         "    border: 2px solid #ffffff;"
                                         "    border-radius: 10px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "    background-color: #555555;"
                                         "}"
                                         "QPushButton:pressed {"
                                         "    background-color: #777777;"
                                         "}");
    }


    for (auto &window: windows_for_insert)
        auntification->getStackedWidget()->addWidget(window); // 5, 6, 7, 8, 9, 10
    auntification->getStackedWidget()->addWidget(auntification); //11

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);

    menuLayout = new QVBoxLayout();
    contentLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout(this);

    for (int i = 0; i < 7; i++)
        menuLayout->addWidget(insert_buttons[i]);
    contentLayout->addWidget(auntification->getStackedWidget());
    contentLayout->addWidget(label);

    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(contentLayout);

    mainLayout->setAlignment(Qt::AlignTop);

    auntification->getStackedWidget()->setCurrentIndex(1005);

    connect(insert_buttons[0], &QPushButton::clicked, this, &MainWindow::onButtonClickedBankManage);
    connect(insert_buttons[1], &QPushButton::clicked, this, &MainWindow::onButtonClickedAccountManage);
    connect(insert_buttons[2], &QPushButton::clicked, this, &MainWindow::onButtonClickedCurrencyManage);
    connect(insert_buttons[3], &QPushButton::clicked, this, &MainWindow::onButtonClickedStockMarketManage);
    connect(insert_buttons[4], &QPushButton::clicked, this, &MainWindow::onButtonClickedTransactionManage);
    connect(insert_buttons[6], &QPushButton::clicked, this, &MainWindow::onButtonClickedAuntificationManage);
    connect(insert_buttons[5], &QPushButton::clicked, this, &MainWindow::onButtonClickedManageTables);

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
    auntification->getStackedWidget()->setCurrentIndex(1005);
}

void MainWindow::onButtonClickedAccountManage() {
    auntification->getStackedWidget()->setCurrentIndex(1006);
}

void MainWindow::onButtonClickedCurrencyManage() {
    auntification->getStackedWidget()->setCurrentIndex(1007);
}

void MainWindow::onButtonClickedStockMarketManage() {
    auntification->getStackedWidget()->setCurrentIndex(1008);
}

void MainWindow::onButtonClickedTransactionManage() {
    auntification->getStackedWidget()->setCurrentIndex(1009);
}

void MainWindow::onButtonClickedAuntificationManage() {
    auntification->getStackedWidget()->setCurrentIndex(1011);
}

void MainWindow::onButtonClickedManageTables() {
    std::ifstream f("../api");
    std::string apiUrl, chat_id;
    getline(f, apiUrl);
    getline(f, chat_id);
    QString apiU(apiUrl.c_str());
    QNetworkRequest request{(apiU)};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    const std::string characters = "0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    std::string rand_code;
    for (int i = 0; i < 4; ++i)
        rand_code += characters[dis(gen)];
    QUrlQuery params;
    params.addQueryItem("chat_id", chat_id.c_str());
    params.addQueryItem("text", rand_code.c_str());
    manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    bool ok;
    QString entered_code = QInputDialog::getText(this, tr(""), tr("Enter code from telegram\n"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
    if (ok && entered_code == rand_code.c_str()) {
        auntification->getStackedWidget()->setCurrentIndex(1010);
    }
}


