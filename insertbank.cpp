
// You may need to build the project (run Qt uic code generator) to get "ui_InsertBank.h" resolved

#include "insertbank.hpp"
#include "ui_InsertBank.h"


InsertBank::InsertBank(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::InsertBank) {
    ui->setupUi(this);
}

InsertBank::~InsertBank() {
    delete ui;
}
