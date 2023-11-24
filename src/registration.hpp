#ifndef CURRENCYDATABASE_REGISTRATION_HPP
#define CURRENCYDATABASE_REGISTRATION_HPP

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QStatusBar>
#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class registration; }
QT_END_NAMESPACE

class registration : public QWidget {
Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);

    ~registration() override;

private slots:

    void onButtonClickedSignUp();

private:
    Ui::registration *ui;
    std::vector<QLineEdit *> registration_lines;
    std::vector<QLabel *> registration_labels;
    QFormLayout *registrationTools;
    QPushButton *sign_up_;
};


#endif
