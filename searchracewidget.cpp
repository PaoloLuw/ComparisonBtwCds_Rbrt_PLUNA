#include "searchracewidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>
#include <algorithm>  // Para std::sort
#include <cmath>      // Para sqrt()
#include <random>     // Para generación de números aleatorios

SearchRaceWidget::SearchRaceWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    std::vector<int> allValues;
    for (int i = 1; i <= 10000000; ++i) {
        allValues.push_back(i);
    }
    targetValue = 9999;  // Un valor alto

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allValues.begin(), allValues.end(), gen);

    dataValues = allValues;

    for (int i = 0; i < 5; ++i) {
        timeLabels[i] = new QLabel("0 ms", this);
        timeLabels[i]->setAlignment(Qt::AlignCenter);
        timeLabels[i]->setStyleSheet("QLabel { background-color: transparent; }");
        layout->addWidget(timeLabels[i]);

        QProgressBar *bar = new QProgressBar(this);
        bar->setRange(0, 100);
        bar->setValue(0);
        bar->setStyleSheet("QProgressBar { background-color: blue; }");
        searchBars.push_back(bar);
        layout->addWidget(bar);
    }


    // Crear QLineEdit para ingresar el valor objetivo
    lineEditTargetValue = new QLineEdit(this);
    lineEditTargetValue->setPlaceholderText("Ingrese un valor Numerico");
    layout->addWidget(lineEditTargetValue); // Agregar al layout

    // Botón para establecer el valor objetivo
    QPushButton *setValueButton = new QPushButton("Establecer Valor Numerico", this);
    layout->addWidget(setValueButton); // Agregar al layout

    // Conectar el botón a la función para establecer el valor
    connect(setValueButton, &QPushButton::clicked, this, &SearchRaceWidget::setTargetValue);

    // Botón para iniciar la búsqueda
    QPushButton *startButton = new QPushButton("Iniciar Carrera", this);
    layout->addWidget(startButton);
    connect(startButton, &QPushButton::clicked, this, &SearchRaceWidget::startSearchRace);

    setLayout(layout);
}
void SearchRaceWidget::setTargetValue() {
    bool ok;
    int inputValue = lineEditTargetValue->text().toInt(&ok);

    if (ok) {
        targetValue = inputValue; // Asignar el nuevo valor a targetValue
        qDebug() << "Nuevo valor objetivo establecido:" << targetValue; // Imprimir el nuevo valor
    } else {
        qDebug() << "Por favor, ingrese un número válido."; // Manejar entrada no válida
    }
}
void SearchRaceWidget::startSearchRace() {
    if (dataValues.empty()) {
        std::cout << "El vector de datos está vacío, no se puede realizar la búsqueda." << std::endl;
        return;
    }

    for (auto &bar : searchBars) {
        bar->setValue(0);
        bar->setStyleSheet("QProgressBar::chunk { background-color: grey; }");
    }

    std::sort(dataValues.begin(), dataValues.end());

    startTime = std::chrono::high_resolution_clock::now(); // Comienza el tiempo

    runLinearSearch();
    runBinarySearch();
    runJumpSearch();
    runInterpolationSearch();
    runExponentialSearch();
}

void SearchRaceWidget::runLinearSearch() {
    bool found = false;
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    for (size_t i = 0; i < dataValues.size(); ++i) {
        if (dataValues[i] == targetValue) {
            searchBars[0]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
            searchBars[0]->setValue(100);  // Encuentra el valor
            std::cout << "Algoritmo 1 (Búsqueda Lineal) encontró el valor " << targetValue << " en la posición " << i << "!" << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        searchBars[0]->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        searchBars[0]->setValue(100);  // No encuentra el valor
        std::cout << "Algoritmo 1 (Búsqueda Lineal) no encontró el valor." << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[0]->setText(QString("Búsqueda Lineal tardó %1 ms").arg(duration / 1000.0));

}

void SearchRaceWidget::runBinarySearch() {
    bool found = false;
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int left = 0, right = dataValues.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (dataValues[mid] == targetValue) {
            searchBars[1]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
            searchBars[1]->setValue(100);  // Encuentra el valor
            std::cout << "Algoritmo 2 (Búsqueda Binaria) encontró el valor " << targetValue << " en la posición " << mid << "!" << std::endl;
            found = true;
            break;
        } else if (dataValues[mid] < targetValue) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        searchBars[1]->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        searchBars[1]->setValue(100);  // No encuentra el valor
        std::cout << "Algoritmo 2 (Búsqueda Binaria) no encontró el valor." << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[1]->setText(QString("Búsqueda Binaria tardó %1 ms").arg(duration / 1000.0));

}

void SearchRaceWidget::runJumpSearch() {
    bool found = false;
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int n = dataValues.size();
    int jump = sqrt(n);
    int prev = 0;

    while (dataValues[std::min(jump, n) - 1] < targetValue) {
        prev = jump;
        jump += sqrt(n);
        if (prev >= n) {
            break;
        }
    }

    for (int i = prev; i < std::min(jump, n); ++i) {
        if (dataValues[i] == targetValue) {
            searchBars[2]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
            searchBars[2]->setValue(100);  // Encuentra el valor
            std::cout << "Algoritmo 3 (Búsqueda de Salto) encontró el valor " << targetValue << " en la posición " << i << "!" << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        searchBars[2]->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        searchBars[2]->setValue(100);  // No encuentra el valor
        std::cout << "Algoritmo 3 (Búsqueda de Salto) no encontró el valor." << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[2]->setText(QString("Búsqueda de Salto tardó %1 ms").arg(duration / 1000.0));

}

void SearchRaceWidget::runInterpolationSearch() {
    bool found = false;
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int low = 0, high = dataValues.size() - 1;

    while (low <= high && targetValue >= dataValues[low] && targetValue <= dataValues[high]) {
        if (low == high) {
            if (dataValues[low] == targetValue) {
                searchBars[3]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
                searchBars[3]->setValue(100);
                std::cout << "Algoritmo 4 (Búsqueda Interpolacional) encontró el valor " << targetValue << " en la posición " << low << "!" << std::endl;
                found = true;
            }
            break;
        }

        // Fórmula de interpolación
        int pos = low + ((double)(high - low) / (dataValues[high] - dataValues[low])) * (targetValue - dataValues[low]);

        if (dataValues[pos] == targetValue) {
            searchBars[3]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
            searchBars[3]->setValue(100);
            std::cout << "Algoritmo 4 (Búsqueda Interpolacional) encontró el valor " << targetValue << " en la posición " << pos << "!" << std::endl;
            found = true;
            break;
        }

        if (dataValues[pos] < targetValue) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    if (!found) {
        searchBars[3]->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        searchBars[3]->setValue(100);  // No encuentra el valor
        std::cout << "Algoritmo 4 (Búsqueda Interpolacional) no encontró el valor." << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[3]->setText(QString("Búsqueda Interpolacional tardó %1 ms").arg(duration / 1000.0));

}

void SearchRaceWidget::runExponentialSearch() {
    bool found = false;
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    if (dataValues.empty()) return;

    if (dataValues[0] == targetValue) {
        searchBars[4]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
        searchBars[4]->setValue(100);
        std::cout << "Algoritmo 5 (Búsqueda Exponencial) encontró el valor " << targetValue << " en la posición 0!" << std::endl;
        return;
    }

    int bound = 1;
    while (bound < dataValues.size() && dataValues[bound] <= targetValue) {
        bound *= 2;
    }

    int left = bound / 2;
    int right = std::min(bound, (int)dataValues.size() - 1);

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (dataValues[mid] == targetValue) {
            searchBars[4]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
            searchBars[4]->setValue(100);
            std::cout << "Algoritmo 5 (Búsqueda Exponencial) encontró el valor " << targetValue << " en la posición " << mid << "!" << std::endl;
            found = true;
            break;
        } else if (dataValues[mid] < targetValue) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        searchBars[4]->setStyleSheet("QProgressBar::chunk { background-color: red; }");
        searchBars[4]->setValue(100);  // No encuentra el valor
        std::cout << "Algoritmo 5 (Búsqueda Exponencial) no encontró el valor." << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[4]->setText(QString("Búsqueda Exponencial tardó %1 ms").arg(duration / 1000.0));

}
