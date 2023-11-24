//
// Created by ivan on 24.11.23.
//

#ifndef CURRENCYDATABASE_MANAGETABLES_HPP
#define CURRENCYDATABASE_MANAGETABLES_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ManageTables; }
QT_END_NAMESPACE

class ManageTables : public QWidget {
Q_OBJECT

public:
    explicit ManageTables(QWidget *parent = nullptr);
    ~ManageTables() override;

private:
    Ui::ManageTables *ui;
};


#endif //CURRENCYDATABASE_MANAGETABLES_HPP
