#ifndef UI_INSERTBANK_H
#define UI_INSERTBANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsertBank
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InsertBank)
    {
        if (InsertBank->objectName().isEmpty())
            InsertBank->setObjectName(QString::fromUtf8("InsertBank"));
        InsertBank->resize(400, 300);
        centralwidget = new QWidget(InsertBank);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        InsertBank->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InsertBank);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 17));
        InsertBank->setMenuBar(menubar);
        statusbar = new QStatusBar(InsertBank);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        InsertBank->setStatusBar(statusbar);

        retranslateUi(InsertBank);

        QMetaObject::connectSlotsByName(InsertBank);
    }

    void retranslateUi(QMainWindow *InsertBank)
    {
        InsertBank->setWindowTitle(QCoreApplication::translate("InsertBank", "InsertBank", nullptr));
    }

};

namespace Ui {
    class InsertBank: public Ui_InsertBank {};
}

QT_END_NAMESPACE

#endif
