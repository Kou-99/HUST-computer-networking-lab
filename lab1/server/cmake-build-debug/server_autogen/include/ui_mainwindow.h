/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *addressText;
    QLineEdit *portText;
    QLineEdit *pathText;
    QVBoxLayout *verticalLayout_3;
    QPushButton *startButt;
    QPushButton *stopButt;
    QLabel *label_2;
    QTextEdit *Log;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(461, 302);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 441, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_4->addWidget(label_4);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_4->addWidget(label);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        addressText = new QLineEdit(verticalLayoutWidget);
        addressText->setObjectName(QStringLiteral("addressText"));

        verticalLayout_2->addWidget(addressText);

        portText = new QLineEdit(verticalLayoutWidget);
        portText->setObjectName(QStringLiteral("portText"));

        verticalLayout_2->addWidget(portText);

        pathText = new QLineEdit(verticalLayoutWidget);
        pathText->setObjectName(QStringLiteral("pathText"));

        verticalLayout_2->addWidget(pathText);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        startButt = new QPushButton(verticalLayoutWidget);
        startButt->setObjectName(QStringLiteral("startButt"));

        verticalLayout_3->addWidget(startButt);

        stopButt = new QPushButton(verticalLayoutWidget);
        stopButt->setObjectName(QStringLiteral("stopButt"));

        verticalLayout_3->addWidget(stopButt);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        Log = new QTextEdit(verticalLayoutWidget);
        Log->setObjectName(QStringLiteral("Log"));
        Log->setReadOnly(true);

        verticalLayout->addWidget(Log);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Listen Address", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Port Number", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Default Path", Q_NULLPTR));
        startButt->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        stopButt->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Log", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
