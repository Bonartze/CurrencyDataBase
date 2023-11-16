
#include "insertaccount.hpp"
#include "ui_InsertAccount.h"


InsertAccount::InsertAccount(QWidget *parent) :
        QWidget(parent), ui(new Ui::InsertAccount) {
    ui->setupUi(this);
    insert_into_account = new QPushButton("Insert data", this);
    insert_into_account->setGeometry(10, 10, 50, 20);
    insert_into_account->show();
    connect(insert_into_account, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    insert_line.resize(4);
    for (int i = 0; i < 4; i++) {
        insert_line[i] = new QLineEdit(this);
        insert_line[i]->setGeometry(30 * i, 40, 30, 40);
    }
}

InsertAccount::~InsertAccount() {
    delete ui;
}

void InsertAccount::onButtonClicked() {
    std::string id = insert_line[0]->text().toStdString();
    std::string balance = insert_line[1]->text().toStdString();
    std::string bank_id = insert_line[2]->text().toStdString();
    std::string stock_id = insert_line[3]->text().toStdString();
    pqxx::work w(ConnectionTool::GetConnect());
    w.exec_params("INSERT INTO public.\"Account\" VALUES ($1, $2, $3, $4);", id, balance, bank_id, stock_id);
    w.commit();
    for (int i = 0; i < 4; i++)
        insert_line[i]->clear();
}