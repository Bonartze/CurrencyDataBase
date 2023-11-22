#include "auntification.hpp"
#include "ui_Auntification.h"


Auntification::Auntification(QWidget *parent) :
        QWidget(parent), ui(new Ui::Auntification) {
    layout = new QVBoxLayout(this);
    ui->setupUi(this);
    auntForm.resize(3);
    lines.resize(2);
    labels.resize(3);
    sign_up = new QPushButton("Sign up");
    sign_up->setFixedSize(60, 20);
    for (size_t i = 0; i < 2; i++) {
        lines[i] = new QLineEdit();
        lines[i]->setFixedWidth(180);
        labels[i] = new QLabel();
        auntForm[i] = new QFormLayout();
    }
    labels[2] = new QLabel();
    lines[0]->setPlaceholderText("Your unique id");
    lines[1]->setEchoMode(QLineEdit::Password);
    labels[0]->setText("         Login:");
    labels[1]->setText("Password: ");
    labels[2]->setText("Don't have an account yet?   ");
    labels[2]->setStyleSheet("color: blue;");
    layout->setAlignment(Qt::AlignTop);
    for (size_t i = 0; i < 2; i++) {
        auntForm[i]->addRow(labels[i], lines[i]);
        layout->addLayout(auntForm[i]);
    }
    auntForm[2] = new QFormLayout();
    auntForm[2]->addRow(labels[2], sign_up);
    layout->addLayout(auntForm[2]);
}

Auntification::~Auntification() {
    delete ui;
}

void Auntification::onButtonClickSignUp() {

}
