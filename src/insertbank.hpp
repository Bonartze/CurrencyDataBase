
#ifndef UNTITLED87_INSERTBANK_HPP
#define UNTITLED87_INSERTBANK_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

#include "ConnectionTool.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class InsertBank; }
QT_END_NAMESPACE

class InsertBank : public QMainWindow {
Q_OBJECT

public:
    explicit InsertBank(QWidget *parent = nullptr);

    ~InsertBank() override;

private slots:

    void onButtonClicked();

    void onButtonClickedDeleted();

    void onButtonClickedDeletedOne();

    void onButtonCLickedChart();

private:
    QPieSeries *series;
    QPieSlice *slice;
    QChart *chart;
    QChartView *chartview;

    std::vector<QLineEdit *> insert_line_bank;
    std::vector<QPushButton *> buttons;
    Ui::InsertBank *ui;

    std::vector<QLabel *> labels;


    QHBoxLayout *layout_;
    QVBoxLayout *vl_;
    QLabel *label_;
    QWidget *centralWidget;

};


#endif
