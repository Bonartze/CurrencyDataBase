#ifndef CURRENCYDATABASE_AUNTIFICATION_HPP
#define CURRENCYDATABASE_AUNTIFICATION_HPP

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Auntification; }
QT_END_NAMESPACE

class Auntification : public QWidget {
Q_OBJECT

public:
    explicit Auntification(QWidget *parent = nullptr);

    ~Auntification() override;
private slots:
    void onButtonClickSignUp();

private:
    Ui::Auntification *ui;
    std::vector<QFormLayout *> auntForm;
    std::vector<QLabel *> labels;
    std::vector<QLineEdit *> lines;
    QVBoxLayout *layout;
    QPushButton *sign_up;
};


#endif
