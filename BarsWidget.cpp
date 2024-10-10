#include "barswidget.h"
#include <QPainter>
#include <QTimer>
#include <algorithm>
#include <iostream>
#include <functional>
#include <QThread>


BarsWidget::BarsWidget(QWidget *parent)
    : QWidget(parent), currentSortMethod(0)
{
    originalValues = { };
    m_values = originalValues;
    m_valuesBubble = originalValues;
    m_valuesSelection = originalValues;
    m_valuesInsertion = originalValues;
    m_valuesQuick = originalValues;
    m_valuesMerge = originalValues;
    m_valuesHeap = originalValues;
}

void BarsWidget::setValues(const std::vector<int>& values)
{
    originalValues = values;
    m_valuesBubble = values;
    m_valuesSelection = values;
    m_valuesInsertion = values;
    m_valuesQuick = values;
    m_valuesHeap = values;
    update();
}

void BarsWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    int cuadros_p_altura = 2;
    int cuadros_p_anchura = 3;
    divide(cuadros_p_altura, cuadros_p_anchura);

    drawBars(painter, m_valuesBubble, "Bubble Sort", 1, cuadros_p_altura, cuadros_p_anchura);
    drawBars(painter, m_valuesSelection, "Selection Sort", 2, cuadros_p_altura, cuadros_p_anchura);
    drawBars(painter, m_valuesInsertion, "Insertion Sort", 3, cuadros_p_altura, cuadros_p_anchura);
    drawBars(painter, m_valuesQuick, "Quick Sort", 4, cuadros_p_altura, cuadros_p_anchura);
    drawBars(painter, m_valuesHeap, "Heap Sort", 5, cuadros_p_altura, cuadros_p_anchura);
}
void BarsWidget::drawBars(QPainter &painter, const std::vector<int>& values, const QString &algorithmName, int pos, int cuadros_p_altura, int cuadros_p_anchura)
{
    positionXandY(pos, cuadros_p_altura, cuadros_p_anchura);
    int barWidth = divition_width / values.size();
    int maxBarHeight = divition_height;

    for (size_t i = 0; i < values.size(); ++i) {
        int barHeight = static_cast<int>(maxBarHeight * (static_cast<double>(values[i]) / 110));
        painter.drawRect(paintX + i * barWidth, divition_height - barHeight - paintY, barWidth - 2, barHeight);
    }

    int textWidth = painter.fontMetrics().horizontalAdvance(algorithmName);
    int textX = paintX + (divition_width - textWidth) / 2;

    int textY = (paintY < 0) ? (-paintY + 20) : (paintY + 20);
    painter.drawText(textX, textY, algorithmName);
}



void BarsWidget::sortAll()
{
    sortBubble();
    sortSelection();
    sortInsertion();
    sortQuick();
    sortHeap();
    update(); // Actualiza después de mover

}

void BarsWidget::sortBubble()
{
    QTimer* timer = new QTimer(this);
    size_t i = 0, j = 0;

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (i < m_valuesBubble.size() - 1) {
            if (j < m_valuesBubble.size() - i - 1) {
                if (m_valuesBubble[j] > m_valuesBubble[j + 1]) {
                    std::swap(m_valuesBubble[j], m_valuesBubble[j + 1]);
                    update();
                }
                j++;
            } else {
                j = 0;
                i++;
            }
        } else {
            timer->stop();
        }
    });

    timer->start(100);
}


void BarsWidget::sortSelection()
{
    QTimer* timer = new QTimer(this);
    size_t i = 0, minIndex = 0;

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (i < m_valuesSelection.size() - 1) {
            minIndex = i;
            for (size_t j = i + 1; j < m_valuesSelection.size(); ++j) {
                if (m_valuesSelection[j] < m_valuesSelection[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                std::swap(m_valuesSelection[i], m_valuesSelection[minIndex]);
                update();
            }
            i++;
        } else {
            timer->stop();
        }
    });

    timer->start(100);
}


void BarsWidget::sortInsertion()
{
    QTimer* timer = new QTimer(this);
    size_t i = 1, j;

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (i < m_valuesInsertion.size()) {
            int key = m_valuesInsertion[i];
            j = i - 1;

            while (j != SIZE_MAX && j < m_valuesInsertion.size() && m_valuesInsertion[j] > key) {
                m_valuesInsertion[j + 1] = m_valuesInsertion[j];
                j--;
            }
            m_valuesInsertion[j + 1] = key;
            update();
            i++;
        } else {
            timer->stop();
            delete timer;
        }
    });

    timer->start(100);
}

void BarsWidget::sortQuick()
{
    currentQuickSortStep = 0;
    quickSort(m_valuesQuick.begin(), m_valuesQuick.end());
}

void BarsWidget::quickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    if (begin < end) {
        auto pivot = *begin;  // Tomar el primer elemento como pivote
        auto left = begin + 1;  // Inicio a la izquierda del pivote
        auto right = end - 1;   // Fin a la derecha del último elemento

        // Realizar la partición
        while (left <= right) {
            // Mover el puntero izquierdo hacia la derecha mientras sea menor que el pivote
            while (left <= right && *left <= pivot) left++;

            // Mover el puntero derecho hacia la izquierda mientras sea mayor que el pivote
            while (left <= right && *right > pivot) right--;

            // Si los índices no se han cruzado, intercambiar los elementos
            if (left < right) {
                std::swap(*left, *right);
                update();  // Actualizar la visualización
            }
        }

        // Intercambiar el pivote con el elemento de la derecha
        std::swap(*begin, *right);
        update();  // Actualizar la visualización

        // Aplicar la recursión a los subarrays con un temporizador para la animación
        QTimer::singleShot(100, this, [=]() {
            quickSort(begin, right);       // Lado izquierdo del pivote
            quickSort(right + 1, end);     // Lado derecho del pivote
        });
    }
}


void BarsWidget::heapify(std::vector<int>& values, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && values[left] > values[largest]) {
        largest = left;
    }

    if (right < n && values[right] > values[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(values[i], values[largest]);
        update();
        heapify(values, n, largest);
    }
}

void BarsWidget::sortHeap()
{
    QTimer* timer = new QTimer(this);
    int n = m_valuesHeap.size();
    int i = n;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(m_valuesHeap, n, i);
    }

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (i > 1) {
            std::swap(m_valuesHeap[0], m_valuesHeap[i - 1]);
            update();

            heapify(m_valuesHeap, i - 1, 0);
            i--; // Disminuye el tamaño del heap
        } else {
            if (!m_valuesHeap.empty() && m_valuesHeap[0] == *std::max_element(m_valuesHeap.begin(), m_valuesHeap.end())) {
                int firstValue = m_valuesHeap[0];
                for (int j = 0; j < m_valuesHeap.size() - 1; ++j) {
                    m_valuesHeap[j] = m_valuesHeap[j + 1];
                }
                m_valuesHeap.back() = firstValue;
            }

            timer->stop();
            delete timer;
        }
    });

    timer->start(100);
}





void BarsWidget::divide(int height, int width) {
    int height_original = this->height();
    int width_original = this->width();
    divition_height = height_original / height;
    divition_width = width_original / width;
}

void BarsWidget::positionXandY(int posIm, int cuadros_p_altura, int cuadros_p_anchura) {
    int a, b;
    int count = 0;
    bool found = false;

    for (int i = 1; i <= cuadros_p_anchura; i++) {
        for (int j = 1; j <= cuadros_p_altura; j++) {
            count++;
            if (count == posIm) {
                a = j - 1;
                b = i - 1;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    paintX = b * divition_width;
    paintY = a * divition_height * -1;
}
