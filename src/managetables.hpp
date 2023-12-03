#ifndef CURRENCYDATABASE_MANAGETABLES_HPP
#define CURRENCYDATABASE_MANAGETABLES_HPP

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLayout>
#include "ConnectionTool.hpp"
#include <QFormLayout>
#include <exception>
#include <QMessageBox>
#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class ManageTables; }
QT_END_NAMESPACE

class ManageTables : public QWidget {
Q_OBJECT

public:
    explicit ManageTables(QWidget *parent = nullptr, QStackedWidget *s = nullptr);

    ~ManageTables() override;

private slots:

    void onButtonClickedNext();

    void onButtonClickedInsert();

    void onButtonClickedDelete();

    void onButtonClickedClear();

    void onButtonClickedBack();

private:
    QMessageBox *mb;
    QPushButton *next;
    QStackedWidget *st;
    Ui::ManageTables *ui;
    QVBoxLayout *choose_table_layout;
    std::vector<QWidget *> inserting_windows;
    std::vector<QRadioButton *> table_check_buttons;
    std::vector<QFormLayout *> layouts;
    std::unordered_map<std::string, std::vector<QLineEdit *>> lines_for_actions;
    std::vector<QPushButton *> back_buttons;
    std::vector<QPushButton *> alter_table;
};


#endif
