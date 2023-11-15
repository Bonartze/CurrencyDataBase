
#ifndef UNTITLED87_INSERTCURRENCY_HPP
#define UNTITLED87_INSERTCURRENCY_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class InsertCurrency; }
QT_END_NAMESPACE

class InsertCurrency : public QWidget {
Q_OBJECT

public:
    explicit InsertCurrency(QWidget *parent = nullptr);

    ~InsertCurrency() override;

private:
    Ui::InsertCurrency *ui;
};


#endif //UNTITLED87_INSERTCURRENCY_HPP
