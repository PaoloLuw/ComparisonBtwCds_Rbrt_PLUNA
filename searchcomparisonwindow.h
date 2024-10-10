#ifndef SEARCHCOMPARISONWINDOW_H
#define SEARCHCOMPARISONWINDOW_H

#include <QWidget>
#include <vector>
#include <QProgressBar>  // Añadimos QProgressBar para las barras de progreso


class SearchComparisonWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchComparisonWindow(QWidget *parent = nullptr);
    void startSearchRace(const std::vector<int>& values, int target);  // Método para iniciar la comparación

private:


    void linearSearch(const std::vector<int>& values, int target);
    void binarySearch(const std::vector<int>& values, int target);
    bool linearSearchFound;
    bool binarySearchFound;


protected:
    // Sobrescribir el método paintEvent para personalizar el dibujo
    void paintEvent(QPaintEvent *event) override;
};

#endif // SEARCHCOMPARISONWINDOW_H
