/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonSort;
    QPushButton *pushButtonShowBarsWidget;
    QPushButton *pushButtonShowSearchRaceWidget;
    QPushButton *pushButtonStartTextSearch;
    QPushButton *pushButtonShowHash;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButtonSort = new QPushButton(centralwidget);
        pushButtonSort->setObjectName("pushButtonSort");
        pushButtonSort->setGeometry(QRect(720, 0, 83, 29));
        pushButtonShowBarsWidget = new QPushButton(centralwidget);
        pushButtonShowBarsWidget->setObjectName("pushButtonShowBarsWidget");
        pushButtonShowBarsWidget->setGeometry(QRect(360, 180, 231, 29));
        pushButtonShowSearchRaceWidget = new QPushButton(centralwidget);
        pushButtonShowSearchRaceWidget->setObjectName("pushButtonShowSearchRaceWidget");
        pushButtonShowSearchRaceWidget->setGeometry(QRect(360, 230, 231, 29));
        pushButtonStartTextSearch = new QPushButton(centralwidget);
        pushButtonStartTextSearch->setObjectName("pushButtonStartTextSearch");
        pushButtonStartTextSearch->setGeometry(QRect(360, 280, 211, 29));
        pushButtonShowHash = new QPushButton(centralwidget);
        pushButtonShowHash->setObjectName("pushButtonShowHash");
        pushButtonShowHash->setGeometry(QRect(360, 330, 191, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 60, 301, 51));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 220, 181, 51));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 170, 211, 51));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(190, 270, 151, 51));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(210, 320, 121, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonSort->setText(QCoreApplication::translate("MainWindow", "Ordenar", nullptr));
        pushButtonShowBarsWidget->setText(QCoreApplication::translate("MainWindow", "Ir a ordenar Algoritmos", nullptr));
        pushButtonShowSearchRaceWidget->setText(QCoreApplication::translate("MainWindow", "Ir a comparar busquedas", nullptr));
        pushButtonStartTextSearch->setText(QCoreApplication::translate("MainWindow", "ir a comparar textos", nullptr));
        pushButtonShowHash->setText(QCoreApplication::translate("MainWindow", "ir a comparar hash", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "PROYECTO: COMPARADOR DE ALGORITMOS", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Algortimos de Busqueda:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Algortimos de Ordenamiento:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Algortimos Textuales:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Algortimos Hash:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
