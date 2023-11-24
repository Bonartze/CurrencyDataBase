#ifndef CURRENCYDATABASE_AUNTIFICATION_HPP
#define CURRENCYDATABASE_AUNTIFICATION_HPP

#include <QWidget>
#include <QFormLayout>
#include "registration.hpp"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QStackedWidget>
#include <QMainWindow>
#include <QStatusBar>

QT_BEGIN_NAMESPACE
namespace Ui { class Auntification; }
QT_END_NAMESPACE

class Auntification : public QWidget {
Q_OBJECT

public:
    explicit Auntification(QWidget *parent = nullptr);

    ~Auntification() override;

    QStackedWidget*& getStackedWidget();
private slots:

    void onButtonClickSignUp();

    void onButtonClickedLogIn();

private:
    QStatusBar *sb;
    registration *registration_;
    Ui::Auntification *ui;
    QFormLayout *auntForm;
    std::vector<QLabel *> labels;
    std::vector<QLineEdit *> lines;
    QVBoxLayout *layout;
    QPushButton *sign_up;
    QPushButton *log_in;
    QHBoxLayout *lo;
    QMainWindow *account;
    QStackedWidget* stackedWidget;
};


#endif
