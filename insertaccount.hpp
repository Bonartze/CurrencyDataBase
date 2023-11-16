
#ifndef UNTITLED87_INSERTACCOUNT_HPP
#define UNTITLED87_INSERTACCOUNT_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertAccount; }
QT_END_NAMESPACE

class InsertAccount : public QWidget {
Q_OBJECT
public:
    explicit InsertAccount(QWidget *parent = nullptr);

    ~InsertAccount() override;

private slots:

    void onButtonClicked();

private:
    std::vector<QLineEdit *> insert_line;
    Ui::InsertAccount *ui;
    QPushButton *insert_into_account;
};

#endif
