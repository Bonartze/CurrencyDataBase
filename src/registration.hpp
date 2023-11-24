//
// Created by ivan on 23.11.23.
//

#ifndef CURRENCYDATABASE_REGISTRATION_HPP
#define CURRENCYDATABASE_REGISTRATION_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration : public QWidget {
Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration() override;

private:
    Ui::Registration *ui;
};


#endif //CURRENCYDATABASE_REGISTRATION_HPP
