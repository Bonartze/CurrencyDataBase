
#ifndef UNTITLED87_INSERTBANK_HPP
#define UNTITLED87_INSERTBANK_HPP

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class InsertBank; }
QT_END_NAMESPACE

class InsertBank : public QMainWindow {
Q_OBJECT

public:
    explicit InsertBank(QWidget *parent = nullptr);

    ~InsertBank() override;

private:
    Ui::InsertBank *ui;
};


#endif //UNTITLED87_INSERTBANK_HPP
