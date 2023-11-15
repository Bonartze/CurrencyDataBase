//
// Created by ivan on 15.11.23.
//

#ifndef UNTITLED87_INSERTACCOUNT_HPP
#define UNTITLED87_INSERTACCOUNT_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class InsertAccount; }
QT_END_NAMESPACE

class InsertAccount : public QWidget {
Q_OBJECT

public:
    explicit InsertAccount(QWidget *parent = nullptr);

    ~InsertAccount() override;

private:
    Ui::InsertAccount *ui;
};


#endif //UNTITLED87_INSERTACCOUNT_HPP
