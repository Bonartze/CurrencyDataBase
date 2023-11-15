

#ifndef UNTITLED87_MAINWINDOW_HPP
#define UNTITLED87_MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <vector>
#include <pqxx/pqxx>
#include <exception>
#include "insertbank.hpp"
#include "insertaccount.hpp"
#include "insertcurrency.hpp"
#include "transaction.hpp"
#include "stockmarket.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:

    void onButtonClicked0();

    void onButtonClicked1();

    void onButtonClicked2();

    void onButtonClicked3();

    void onButtonClicked4();

private:
    Ui::MainWindow *ui;
    std::vector<QWidget *> windows_for_insert;
    std::vector<QPushButton *> insert_buttons;
};

#endif //UNTITLED87_MAINWINDOW_HPP
