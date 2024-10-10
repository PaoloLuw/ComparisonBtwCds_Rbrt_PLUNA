#ifndef BARSWIDGET_H
#define BARSWIDGET_H

#include <QWidget>
#include <vector>
#include <QPainter>

class BarsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BarsWidget(QWidget *parent = nullptr);

    void setValues(const std::vector<int>& values);
    void sortAll();


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<int> m_values;
    std::vector<int> m_valuesBubble;     // Para Bubble Sort
    std::vector<int> m_valuesSelection;  // Para Selection Sort
    std::vector<int> m_valuesInsertion;  // Para Insertion Sort
    std::vector<int> m_valuesQuick;      // Para Quick Sort
    std::vector<int> m_valuesMerge;      // Para Merge Sort
    std::vector<int> m_valuesHeap;       // Para Heap Sort

    std::vector<int> originalValues;     // Valores originales


    size_t currentQuickSortStep;      // Paso actual para QuickSort
    size_t currentMergeStep;

    int divition_height; // Altura de la división de la pantalla
    int divition_width;  // Ancho de la división de la pantalla
    int paintX;          // Posición X para pintar barras
    int paintY;          // Posición Y para pintar barras

    void sortBubble();    // Bubble Sort
    void sortSelection(); // Selection Sort
    void sortInsertion(); // Insertion Sort
    void sortQuick();     // Quick Sort
    void sortHeap();      // Heap Sort
    int currentSortMethod; // Método de ordenamiento activo


    void quickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void heapify(std::vector<int>& values, int n, int i);

    void divide(int height, int width);
    void positionXandY(int posIm, int cuadros_p_altura, int cuadros_p_anchura);

    void drawBars(QPainter &painter, const std::vector<int>& values, const QString &algorithmName, int pos, int cuadros_p_altura, int cuadros_p_anchura);

};

#endif // BARSWIDGET_H
