#include "hashcomparisonwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <chrono>
#include <iostream>
#include <algorithm>

HashComparisonWidget::HashComparisonWidget(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void HashComparisonWidget::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout;

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Ingresa el texto para generar los hashes");
    layout->addWidget(inputField);

    const QString algorithmNames[5] = {
        "Simple Sum Hash",
        "XOR Hash",
        "DJB2 Hash",
        "FNV-1a Hash",
        "Rotating Hash"
    };

    for (int i = 0; i < 5; ++i) {
        QLabel *label = new QLabel(this);
        label->setText(algorithmNames[i] + ": ");
        labels.push_back(label);
        layout->addWidget(label);

        QProgressBar *progressBar = new QProgressBar(this);
        progressBar->setRange(0, 100);  // Se llenará al 100%
        progressBars.push_back(progressBar);
        layout->addWidget(progressBar);
    }

    startButton = new QPushButton("Iniciar Comparación", this);
    connect(startButton, &QPushButton::clicked, this, &HashComparisonWidget::compareHashes);
    layout->addWidget(startButton);

    setLayout(layout);
}


void HashComparisonWidget::compareHashes()
{
    std::string input = inputField->text().toStdString();
    if (input.empty()) {
        input = "Texto por defecto";  // Si el campo está vacío, usar un texto por defecto
    }

    std::vector<long long> times(5);

    // Algoritmos de hash
    std::vector<std::function<unsigned long long(const std::string&)>> hashAlgorithms = {
        [this](const std::string& input) { return this->simpleSumHash(input); },
        [this](const std::string& input) { return this->xorHash(input); },
        [this](const std::string& input) { return this->djb2Hash(input); },
        [this](const std::string& input) { return this->fnv1aHash(input); },
        [this](const std::string& input) { return this->rotatingHash(input); }
    };

    for (int i = 0; i < 5; ++i) {
        progressBars[i]->setValue(0);  // Resetear progreso

        auto start = std::chrono::high_resolution_clock::now();

        for (int j = 0; j < 1000000; ++j) {
            volatile unsigned long long hashValue = hashAlgorithms[i](input);

            if (j % 10000 == 0) {  // Actualizar la barra cada 10000 iteraciones
                progressBars[i]->setValue((j * 100) / 1000000);  // Convertir a porcentaje
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        times[i] = std::chrono::duration<double, std::micro>(end - start).count();  // En microsegundos

        progressBars[i]->setValue(100);
    }

    displayResults(times);
}


void HashComparisonWidget::displayResults(std::vector<long long> times)
{
    long long minTime = *std::min_element(times.begin(), times.end());

    for (int i = 0; i < 5; ++i) {
        QString algorithmName = "";
        switch (i) {
        case 0: algorithmName = "Suma Simple Hash"; break;
        case 1: algorithmName = "XOR Hash"; break;
        case 2: algorithmName = "DJB2 Hash"; break;
        case 3: algorithmName = "FNV-1a Hash"; break;
        case 4: algorithmName = "Hash Rotatorio"; break;
        }
        labels[i]->setText(algorithmName + ": " + QString::number(times[i]) + " µs");

        if (times[i] == minTime) {
            progressBars[i]->setStyleSheet("QProgressBar::chunk { background-color: blue; }");
        } else {
            progressBars[i]->setStyleSheet("QProgressBar::chunk { background-color: gray; }");
        }
    }
}

unsigned long long HashComparisonWidget::simpleSumHash(const std::string &input)
{
    unsigned long long hash = 0;
    for (char c : input) {
        hash += static_cast<unsigned long long>(c);
    }
    return hash;
}

unsigned long long HashComparisonWidget::xorHash(const std::string &input)
{
    unsigned long long hash = 0;
    for (char c : input) {
        hash ^= static_cast<unsigned long long>(c);
    }
    return hash;
}

unsigned long long HashComparisonWidget::djb2Hash(const std::string &input)
{
    unsigned long long hash = 5381;
    for (char c : input) {
        hash = ((hash << 5) + hash) + static_cast<unsigned long long>(c);  // hash * 33 + c
    }
    return hash;
}

unsigned long long HashComparisonWidget::fnv1aHash(const std::string &input)
{
    unsigned long long hash = 14695981039346656037ULL;
    unsigned long long fnvPrime = 1099511628211ULL;
    for (char c : input) {
        hash ^= static_cast<unsigned long long>(c);
        hash *= fnvPrime;
    }
    return hash;
}

unsigned long long HashComparisonWidget::rotatingHash(const std::string &input)
{
    unsigned long long hash = 0;
    for (char c : input) {
        hash = (hash << 4) ^ (hash >> 28) ^ static_cast<unsigned long long>(c);
    }
    return hash;
}
