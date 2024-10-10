#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , barsWidget(nullptr)
    , searchRaceWidget(nullptr)
    , textSearchWidget(nullptr)
    , hashComparisonWidget(nullptr)
{

    ui->setupUi(this);

    connect(ui->pushButtonShowBarsWidget, &QPushButton::clicked, this, &MainWindow::on_pushButtonShowBarsWidget_clicked);
    connect(ui->pushButtonSort, &QPushButton::clicked, this, &MainWindow::on_pushButtonSort_clicked);
    connect(ui->pushButtonShowSearchRaceWidget, &QPushButton::clicked, this, &MainWindow::on_pushButtonShowSearchRaceWidget_clicked);
    connect(ui->pushButtonStartTextSearch, &QPushButton::clicked, this, &MainWindow::on_pushButtonStartTextSearch_clicked);
    connect(ui->pushButtonShowHash, &QPushButton::clicked, this, &MainWindow::on_pushButtonShowHash_clicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonShowBarsWidget_clicked()
{
    if (!barsWidget) {
        barsWidget = new BarsWidget(this);//
        std::vector<int> values = {15, 85, 25, 75, 35, 65, 45, 55, 5, 12, 78, 22, 67, 88, 33, 44, 90, 11, 23, 56, 98, 71, 63, 81, 19};
        barsWidget->setValues(values);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(barsWidget);
        layout->addWidget(ui->pushButtonSort);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);
    }
}

void MainWindow::on_pushButtonSort_clicked()
{
    if (barsWidget) {
        std::cout << "Iniciando ordenación..." << std::endl;
        barsWidget->sortAll();
    } else {
        std::cout << "No se ha creado el BarsWidget." << std::endl;
    }
}

void MainWindow::on_pushButtonShowSearchRaceWidget_clicked()
{
    if (!searchRaceWidget) {
        searchRaceWidget = new SearchRaceWidget(this);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(searchRaceWidget);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);
    }
}

void MainWindow::on_pushButtonStartTextSearch_clicked()
{
    if (!textSearchWidget) {
        textSearchWidget = new TextSearchComparisonWidget(this);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(textSearchWidget);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);
    }
}


void MainWindow::on_pushButtonShowHash_clicked()
{
    if (!hashComparisonWidget) {
        hashComparisonWidget = new HashComparisonWidget(this);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(hashComparisonWidget);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);
    }
}

