#include "searchcomparisonwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <iostream>

SearchComparisonWindow::SearchComparisonWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Crear etiquetas para mostrar el estado de cada algoritmo
    QLabel *statusLabel = new QLabel("Carrera de búsqueda iniciada...", this);
    layout->addWidget(statusLabel);

    // Estado de los algoritmos de búsqueda (inicialmente en progreso)
    linearSearchFound = false;
    binarySearchFound = false;

    setLayout(layout);
}

void SearchComparisonWindow::startSearchRace(const std::vector<int>& values, int target)
{
    // Ejecutar los diferentes algoritmos de búsqueda
    linearSearch(values, target);
    binarySearch(values, target);
    // Llamar a los demás algoritmos de búsqueda...
}

void SearchComparisonWindow::linearSearch(const std::vector<int>& values, int target)
{
    std::cout << "Iniciando búsqueda lineal..." << std::endl;
    int i = 0;
    int size = values.size();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, &i, size, values, target, timer]() {
        if (i < size) {
            if (values[i] == target) {
                linearSearchFound = true;  // Encontrado
                timer->stop();
            }
            i++;
        } else {
            linearSearchFound = false;  // No encontrado
            timer->stop();
        }
        update();  // Llamar al repaint para actualizar la ventana
    });
    timer->start(100);
}

void SearchComparisonWindow::binarySearch(const std::vector<int>& values, int target)
{
    std::cout << "Iniciando búsqueda binaria..." << std::endl;
    int left = 0, right = values.size() - 1;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, &left, &right, values, target, timer]() {
        if (left <= right) {
            int mid = left + (right - left) / 2;

            if (values[mid] == target) {
                binarySearchFound = true;  // Encontrado
                timer->stop();
            } else if (values[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            binarySearchFound = false;  // No encontrado
            timer->stop();
        }
        update();  // Llamar al repaint para actualizar la ventana
    });
    timer->start(100);
}

void SearchComparisonWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Definir los colores según si el algoritmo encontró el objetivo o no
    QColor linearSearchColor = linearSearchFound ? Qt::green : Qt::red;
    QColor binarySearchColor = binarySearchFound ? Qt::green : Qt::red;

    // Dibujar las barras de búsqueda
    painter.setBrush(linearSearchColor);
    painter.drawRect(50, 50, 200, 30);  // Barra de búsqueda lineal

    painter.setBrush(binarySearchColor);
    painter.drawRect(50, 100, 200, 30);  // Barra de búsqueda binaria

    // Puedes añadir más barras para otros algoritmos aquí...
}
