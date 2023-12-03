#include "managetables.hpp"
#include "ui_ManageTables.h"

ManageTables::ManageTables(QWidget *parent, QStackedWidget *s) :
        QWidget(parent), ui(new Ui::ManageTables), st(s) {
    ui->setupUi(this);
    alter_table.resize(15);
    table_check_buttons.resize(6);
    alter_table.resize(3);
    back_buttons.resize(5);
    inserting_windows.resize(5);
    layouts.resize(5);
    for (size_t i = 0; i < 15; i += 3) {
        alter_table[i] = new QPushButton("Insert");
        alter_table[i + 1] = new QPushButton("Delete");
        alter_table[i + 2] = new QPushButton("Clear");
        alter_table[i]->setFixedSize(120, 120);
        alter_table[i + 1]->setFixedSize(120, 120);
        alter_table[i + 2]->setFixedSize(120, 120);
    }

    lines_for_actions["account"].resize(6);
    lines_for_actions["bank"].resize(2);
    lines_for_actions["currency"].resize(2);
    lines_for_actions["stockmarket"].resize(5);
    lines_for_actions["transaction"].resize(4);


    for (size_t i = 0; i < 5; i++) {
        back_buttons[i] = new QPushButton("Back");
        back_buttons[i]->setFixedSize(120, 120);
    }
    for (size_t i = 0; i < 6; i++) {
        lines_for_actions["account"][i] = new QLineEdit();
        lines_for_actions["account"][i]->setFixedWidth(150);
    }
    for (size_t i = 0; i < 2; i++) {
        lines_for_actions["bank"][i] = new QLineEdit();
        lines_for_actions["bank"][i]->setFixedWidth(150);
    }
    for (size_t i = 0; i < 2; i++) {
        lines_for_actions["currency"][i] = new QLineEdit();
        lines_for_actions["currency"][i]->setFixedWidth(150);
    }
    for (size_t i = 0; i < 5; i++) {
        lines_for_actions["stockmarket"][i] = new QLineEdit();
        lines_for_actions["stockmarket"][i]->setFixedWidth(150);
    }
    for (size_t i = 0; i < 4; i++) {
        lines_for_actions["transaction"][i] = new QLineEdit();
        lines_for_actions["transaction"][i]->setFixedWidth(150);
    }
    for (size_t i = 0; i < 5; i++) {
        inserting_windows[i] = new QWidget();
        st->addWidget(inserting_windows[i]);    // 0, 1, 2, 3, 4
    }
    for (size_t i = 0; i < 5; i++) {
        layouts[i] = new QFormLayout(inserting_windows[i]);
        layouts[i]->setAlignment(Qt::AlignTop);
    }
    layouts[0]->addRow(new QLabel("id: "), lines_for_actions["account"][0]);
    layouts[0]->addRow(new QLabel("balance: "), lines_for_actions["account"][1]);
    layouts[0]->addRow(new QLabel("bank_id: "), lines_for_actions["account"][2]);
    layouts[0]->addRow(new QLabel("stock_id: "), lines_for_actions["account"][3]);
    layouts[0]->addRow(new QLabel("login: "), lines_for_actions["account"][4]);
    layouts[0]->addRow(new QLabel("password: "), lines_for_actions["account"][5]);

    layouts[1]->addRow(new QLabel("id: "), lines_for_actions["bank"][0]);
    layouts[1]->addRow(new QLabel("name: "), lines_for_actions["bank"][1]);

    layouts[2]->addRow(new QLabel("id: "), lines_for_actions["currency"][0]);
    layouts[2]->addRow(new QLabel("name: "), lines_for_actions["currency"][1]);

    layouts[3]->addRow(new QLabel("id: "), lines_for_actions["stockmarket"][0]);
    layouts[3]->addRow(new QLabel("currency_id_from: "), lines_for_actions["stockmarket"][1]);
    layouts[3]->addRow(new QLabel("currency_id_to: "), lines_for_actions["stockmarket"][2]);
    layouts[3]->addRow(new QLabel("rate: "), lines_for_actions["stockmarket"][3]);
    layouts[3]->addRow(new QLabel("date: "), lines_for_actions["stockmarket"][4]);

    layouts[4]->addRow(new QLabel("id: "), lines_for_actions["transaction"][0]);
    layouts[4]->addRow(new QLabel("account_id_from: "), lines_for_actions["transaction"][1]);
    layouts[4]->addRow(new QLabel("amount: "), lines_for_actions["transaction"][2]);
    layouts[4]->addRow(new QLabel("date: "), lines_for_actions["transaction"][3]);

    for (size_t i = 0; i < 5; i++) {
        layouts[i]->addWidget(back_buttons[i]);
    }
    for (size_t i = 0, j = 0; i < 5; i++, j += 3) {
        QHBoxLayout *v = new QHBoxLayout();
        v->addWidget(back_buttons[i]);
        v->addWidget(alter_table[j]);
        v->addWidget(alter_table[j + 1]);
        v->addWidget(alter_table[j + 2]);
        layouts[i]->addRow(v);
    }
    mb = new QMessageBox();
    mb->setFixedSize(600, 600);
    choose_table_layout = new QVBoxLayout(this);
    choose_table_layout->addWidget(new QLabel("Choose table to manage: "));
    for (size_t i = 0; i < 6; i++) {
        table_check_buttons[i] = new QRadioButton();
        choose_table_layout->addWidget(table_check_buttons[i]);
    }
    next = new QPushButton("OK");
    next->setFixedSize(120, 120);
    choose_table_layout->addWidget(next);
    table_check_buttons[0]->setText("Account");
    table_check_buttons[1]->setText("Bank");
    table_check_buttons[2]->setText("Currency");
    table_check_buttons[3]->setText("StockMarket");
    table_check_buttons[4]->setText("Transaction");
    table_check_buttons[5]->setText("Clear all");
    choose_table_layout->setAlignment(Qt::AlignTop);
    connect(next, &QPushButton::clicked, this, &ManageTables::onButtonClickedNext);
    for (size_t i = 0; i < 5; i++)
        connect(back_buttons[i], &QPushButton::clicked, this, &ManageTables::onButtonClickedBack);
    for (size_t i = 0; i < 15; i += 3) {
        connect(alter_table[i], &QPushButton::clicked, this, &ManageTables::onButtonClickedInsert);
        connect(alter_table[i + 1], &QPushButton::clicked, this, &ManageTables::onButtonClickedDelete);
        connect(alter_table[i + 2], &QPushButton::clicked, this, &ManageTables::onButtonClickedClear);
    }
}

ManageTables::~ManageTables() {
    delete ui;
}

void ManageTables::onButtonClickedNext() {
    if (table_check_buttons[0]->isChecked()) {
        st->setCurrentIndex(1000);
    } else if (table_check_buttons[1]->isChecked()) {
        st->setCurrentIndex(1001);
    } else if (table_check_buttons[2]->isChecked()) {
        st->setCurrentIndex(1002);
    } else if (table_check_buttons[3]->isChecked()) {
        st->setCurrentIndex(1003);
    } else if (table_check_buttons[4]->isChecked()) {
        st->setCurrentIndex(1004);
    } else if (table_check_buttons[5]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            w.exec("DELETE FROM public.\"Transaction\";\n"
                   "DELETE FROM public.\"Account\";\n"
                   "DELETE FROM public.\"StockMarket\";\n"
                   "DELETE FROM public.\"Bank\";\n"
                   "DELETE FROM public.\"Currency\";\n"
            );
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
            return;
        }
        mb->setText("All notes are cleared successfully!");
        mb->exec();
    } else {
        mb->setText("Please chose option");
        mb->exec();
    }
}

void ManageTables::onButtonClickedBack() {
    st->setCurrentIndex(1010);
}

void ManageTables::onButtonClickedInsert() {
    if (table_check_buttons[0]->isChecked()) {
        std::string id, balance, bank_id, stock_id, login, password;

        id = lines_for_actions["account"][0]->text().toStdString();
        balance = lines_for_actions["account"][1]->text().toStdString();
        bank_id = lines_for_actions["account"][2]->text().toStdString();
        stock_id = lines_for_actions["account"][3]->text().toStdString();
        login = lines_for_actions["account"][4]->text().toStdString();
        password = lines_for_actions["account"][5]->text().toStdString();
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            w.exec_params("INSERT INTO public.\"Account\" VALUES ($1, $2, $3, $4, $5, $6);", id, balance, bank_id,
                          stock_id, login, password);
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
        for (int i = 0; i < 6; i++)
            lines_for_actions["account"][i]->clear();
    } else if (table_check_buttons[1]->isChecked()) {
        try {
            std::string id = lines_for_actions["bank"][0]->text().toStdString();
            std::string name = lines_for_actions["bank"][1]->text().toStdString();
            pqxx::work w(ConnectionTool::GetConnect());
            w.exec_params("INSERT INTO public.\"Bank\" VALUES ($1, $2);", id, name);
            w.commit();
            for (int i = 0; i < 2; i++)
                lines_for_actions["bank"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[2]->isChecked()) {
        try {
            std::string id = lines_for_actions["currency"][0]->text().toStdString();
            std::string name = lines_for_actions["currency"][1]->text().toStdString();
            pqxx::work w(ConnectionTool::GetConnect());
            w.exec_params("INSERT INTO public.\"Currency\" VALUES ($1, $2);", id, name);


            w.commit();
            for (int i = 0; i < 2; i++)
                lines_for_actions["currency"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[3]->isChecked()) {
        try {
            std::string id = lines_for_actions["stockmarket"][0]->text().toStdString();
            std::string currency_id_from = lines_for_actions["stockmarket"][1]->text().toStdString();
            std::string currency_id_to = lines_for_actions["stockmarket"][2]->text().toStdString();
            std::string rate_ = lines_for_actions["stockmarket"][3]->text().toStdString();
            std::string date = lines_for_actions["stockmarket"][4]->text().toStdString();
            pqxx::work w(ConnectionTool::GetConnect());
            w.exec_params("INSERT INTO public.\"StockMarket\" VALUES ($1, $2, $3, $4, $5)", id, currency_id_from,
                          currency_id_to, rate_, date);
            w.commit();
            for (int i = 0; i < 5; i++)
                lines_for_actions["stockmarket"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[4]->isChecked()) {
        try {
            std::string id = lines_for_actions["transaction"][0]->text().toStdString();
            std::string account_id_from = lines_for_actions["transaction"][1]->text().toStdString();
            std::string amount = lines_for_actions["transaction"][2]->text().toStdString();
            std::string date = lines_for_actions["transaction"][3]->text().toStdString();
            pqxx::work w(ConnectionTool::GetConnect());
            w.exec_params("INSERT INTO public.\"Transaction\" VALUES ($1, $2, $3, $4);", id, account_id_from, amount,
                          date);
            w.commit();
            for (int i = 0; i < 4; i++)
                lines_for_actions["transaction"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    }
}

void ManageTables::onButtonClickedDelete() {
    if (table_check_buttons[0]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            int id = lines_for_actions["account"][0]->text().toInt();
            w.exec_params("DELETE FROM public.\"Account\" WHERE id = $1", id);
            w.commit();
            for (int i = 0; i < 6; i++)
                lines_for_actions["account"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[1]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            int id = lines_for_actions["bank"][0]->text().toInt();
            w.exec_params("DELETE FROM public.\"Bank\" WHERE id = $1", id);
            w.commit();
            for (int i = 0; i < 2; i++)
                lines_for_actions["bank"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[2]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            int id = lines_for_actions["currency"][0]->text().toInt();
            w.exec_params("DELETE FROM public.\"Currency\" WHERE id = $1", id);
            w.commit();
            for (int i = 0; i < 2; i++)
                lines_for_actions["currency"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[3]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            int id = lines_for_actions["stockmarket"][0]->text().toInt();
            w.exec_params("DELETE FROM public.\"StockMarket\" WHERE id = $1", id);
            w.commit();
            for (int i = 0; i < 5; i++)
                lines_for_actions["stockmarket"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[4]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            int id = lines_for_actions["transaction"][0]->text().toInt();
            w.exec_params("DELETE FROM public.\"Transaction\" WHERE id = $1", id);
            w.commit();
            for (int i = 0; i < 4; i++)
                lines_for_actions["transaction"][i]->clear();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    }
}

void ManageTables::onButtonClickedClear() {
    if (table_check_buttons[0]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            auto res_query = w.exec("DELETE FROM public.\"Account\";");
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[1]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            auto res_query = w.exec("DELETE FROM public.\"Bank\";");
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[2]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            auto res_query = w.exec("DELETE FROM public.\"Currency\";");
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[3]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            auto res_query = w.exec("DELETE FROM public.\"StockMarket\";");
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    } else if (table_check_buttons[4]->isChecked()) {
        try {
            pqxx::work w(ConnectionTool::GetConnect());
            auto res_query = w.exec("DELETE FROM public.\"Transaction\";");
            w.commit();
        }
        catch (std::exception &ex) {
            QMessageBox::critical(nullptr, "Error", ex.what(), QMessageBox::Ok);
        }
    }
}

