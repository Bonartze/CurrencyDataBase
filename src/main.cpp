#include <QApplication>
#include <QPushButton>
#include "mainwindow.hpp"
#include <pqxx/pqxx>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow *mw = new MainWindow();
    mw->show();
    return QApplication::exec();
}