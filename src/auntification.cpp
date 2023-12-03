#include "auntification.hpp"
#include "ui_Auntification.h"


Auntification::Auntification(QWidget *parent) :
        QWidget(parent), ui(new Ui::Auntification) {

    layout = new QVBoxLayout(this);
    registration_ = new registration();
    auntForm = new QFormLayout();
    sb = new QStatusBar();
    sb->setStyleSheet("color: red");
    ui->setupUi(this);
    sign_up = new QPushButton("Sign up");
    log_in = new QPushButton("Log in");
    lo = new QHBoxLayout(this);
    stackedWidget = new QStackedWidget();

    accounts.resize(1000);
    lines.resize(2);
    labels.resize(3);

    log_in->setFixedSize(60, 20);
    sign_up->setFixedSize(60, 20);

    for (size_t i = 0; i < 2; i++) {
        lines[i] = new QLineEdit();
        lines[i]->setFixedWidth(180);
        labels[i] = new QLabel();
    }
    for (size_t i = 0; i < 1000; i++) {
        accounts[i] = new Account(nullptr, i);
        stackedWidget->addWidget(accounts[i]);
    }

    labels[2] = new QLabel();
    lines[0]->setPlaceholderText("Your unique id");
    lines[1]->setPlaceholderText("*******");
    lines[1]->setEchoMode(QLineEdit::Password);
    labels[0]->setText("Login: ");
    labels[1]->setText("Password: ");
    labels[2]->setText("Don't have an account yet?   ");
    labels[2]->setStyleSheet("color: blue;");
    layout->setAlignment(Qt::AlignTop);

    for (size_t i = 0; i < 2; i++)
        auntForm->addRow(labels[i], lines[i]);
    lo->addWidget(sign_up);
    lo->addWidget(log_in);
    auntForm->addRow(labels[2], lo);
    auntForm->addRow(sb);
    layout->addLayout(auntForm);

    connect(sign_up, SIGNAL(clicked()), this, SLOT(onButtonClickSignUp()));
    connect(log_in, SIGNAL(clicked()), this, SLOT(onButtonClickedLogIn()));
}

Auntification::~Auntification() {
    delete ui;
}

void Auntification::onButtonClickSignUp() {
    registration_->setFixedSize(500, 500);
    registration_->show();
}

void Auntification::onButtonClickedLogIn() {
    pqxx::work w(ConnectionTool::GetConnect());

    std::string login_line = lines[0]->text().toStdString();
    std::string password_line = lines[1]->text().toStdString();
    std::string real_password;

    auto query = w.exec_params("SELECT id, password FROM public.\"Account\" WHERE login = $1", login_line);
    int id;
    if (!query.empty())
        id = query[0]["id"].as<int>();
    if (!query.empty() && !query[0]["password"].is_null()) {
        real_password = query[0]["password"].as<std::string>();
    }
    if (login_line.empty())
        sb->showMessage("Sorry, you didn't enter a login", 3000);
    else if (real_password.empty())
        sb->showMessage("Sorry, but login doesn't exist, sign up, please", 3000);
    else if (real_password != password_line)
        sb->showMessage("Wrong password", 3000);
    else {
        stackedWidget->setCurrentIndex(12 + id);
    }
}

QStackedWidget *&Auntification::getStackedWidget() {
    return stackedWidget;
}