#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "barswidget.h"
#include "searchracewidget.h"
#include "TextSearchComparisonWidget.h"
#include "HashComparisonWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSort_clicked();
    void on_pushButtonShowBarsWidget_clicked();

private:
    Ui::MainWindow *ui;
    BarsWidget *barsWidget;
    SearchRaceWidget *searchRaceWidget;
    TextSearchComparisonWidget *textSearchWidget;
    HashComparisonWidget *hashComparisonWidget;


private slots:
    void on_pushButtonShowSearchRaceWidget_clicked();
    void on_pushButtonStartTextSearch_clicked();
    void on_pushButtonShowHash_clicked();

};

#endif // MAINWINDOW_H
