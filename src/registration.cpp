#include "registration.hpp"
#include "ui_registration.h"
#include <iostream>

registration::registration(QWidget *parent) :
        QWidget(parent), ui(new Ui::registration) {

    ui->setupUi(this);


    registrationTools = new QFormLayout(this);
    registration_labels.resize(2);
    registration_lines.resize(2);
    sign_up_ = new QPushButton("Sign up");
    sign_up_->setFixedSize(60, 20);
    for (size_t i = 0; i < 2; i++) {
        registration_labels[i] = new QLabel();
        registration_lines[i] = new QLineEdit();
        registration_lines[i]->setFixedWidth(180);
    }
    registration_labels[0]->setText("Make up a login: ");
    registration_labels[1]->setText("Make up a password: ");
    registration_lines[1]->setEchoMode(QLineEdit::Password);
    for (size_t i = 0; i < 2; i++)
        registrationTools->addRow(registration_labels[i], registration_lines[i]);
    registrationTools->addWidget(sign_up_);
    connect(sign_up_, SIGNAL(clicked()), this, SLOT(onButtonClickedSignUp()));
}

registration::~registration() {
    delete ui;
}

void registration::onButtonClickedSignUp() {
    pqxx::work w(ConnectionTool::GetConnect());
    std::string login_line = registration_lines[0]->text().toStdString();
    std::string password_line = registration_lines[1]->text().toStdString();
    std::string real_password;


    auto query = w.exec_params("SELECT password FROM public.\"Account\" WHERE login = $1", login_line);
    if (!query.empty() && !query[0]["password"].is_null()) {
        real_password = query[0]["password"].as<std::string>();
    }

    QStatusBar *statusBar = new QStatusBar(this);
    if (login_line.empty()) {
        statusBar->setStyleSheet("color: red");
        statusBar->showMessage("Sorry, you didn't enter a login", 5000);
        statusBar->move(220, 67);
        statusBar->setFixedWidth(2400);
        statusBar->show();
    } else if (password_line.empty()) {
        statusBar->setStyleSheet("color: red");
        statusBar->showMessage("Sorry, you didn't enter a password", 5000);
        statusBar->move(220, 67);
        statusBar->setFixedWidth(2400);
        statusBar->show();
    } else if (!real_password.empty()) {
        statusBar->setStyleSheet("color: red");
        statusBar->showMessage("Sorry, but this login is already used", 5000);
        statusBar->move(220, 67);
        statusBar->setFixedWidth(2400);
        statusBar->show();
        return;
    } else {
         w.exec_params("INSERT INTO public.\"Account\" (login, password) VALUES ($1, $2)", login_line,
                        password_line);
        w.commit();
        this->close();
    }
}
