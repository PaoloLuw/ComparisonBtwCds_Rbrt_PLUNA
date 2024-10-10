#include "TextSearchComparisonWidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <chrono>
#include <algorithm>
#include <QTextStream>

TextSearchComparisonWidget::TextSearchComparisonWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    textInput = new QLineEdit(this);
    textInput->setPlaceholderText("Introduce el texto");
    layout->addWidget(textInput);

    patternInput = new QLineEdit(this);
    patternInput->setPlaceholderText("Introduce el patrón");
    layout->addWidget(patternInput);

    startButton = new QPushButton("Iniciar Búsqueda", this);
    layout->addWidget(startButton);

    for (int i = 0; i < 5; ++i) {
        timeLabels[i] = new QLabel("0 ms", this);
        timeLabels[i]->setAlignment(Qt::AlignCenter);
        layout->addWidget(timeLabels[i]);

        QProgressBar *bar = new QProgressBar(this);
        bar->setRange(0, 100);
        bar->setValue(0);
        searchBars.push_back(bar);
        layout->addWidget(bar);
    }

    setLayout(layout);

    connect(startButton, &QPushButton::clicked, [this]() {
        QString text = textInput->text();
        QString pattern = patternInput->text();
        startComparison(text, pattern);
    });
}

void TextSearchComparisonWidget::startComparison(const QString &text, const QString &pattern) {
    for (int i = 0; i < 5; ++i) {
        searchBars[i]->setValue(0);
        searchBars[i]->setStyleSheet("QProgressBar { background-color: grey; }");
        timeLabels[i]->setText("0 ms");
    }

    bruteForceSearch(text, pattern, 0);
    kmpSearch(text, pattern, 1);
    rabinKarpSearch(text, pattern, 2);
    boyerMooreSearch(text, pattern, 3);
    ahoCorasickSearch(text, pattern, 4);
}

void TextSearchComparisonWidget::bruteForceSearch(const QString &text, const QString &pattern, int index) {
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int textLen = text.length();
    int patternLen = pattern.length();
    bool found = false;

    for (int i = 0; i <= textLen - patternLen; ++i) {
        if (text.mid(i, patternLen) == pattern) {
            found = true;
            break;
        }
    }

    if (found) {
        searchBars[index]->setValue(100);
        searchBars[index]->setStyleSheet("QProgressBar { background-color: green; }");
    } else {
        searchBars[index]->setStyleSheet("QProgressBar { background-color: red; }");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[index]->setText(QString("Fuerza Bruta tardó %1 ms").arg(duration / 1000.0));
}

void TextSearchComparisonWidget::kmpSearch(const QString &text, const QString &pattern, int index) {
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int m = pattern.length();
    int n = text.length();

    QVector<int> lps(m);
    computeLPSArray(pattern, m, lps);

    int i = 0; // Índice para text
    int j = 0; // Índice para pattern
    bool found = false;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            found = true;
            break;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (found) {
        searchBars[index]->setValue(100);
        searchBars[index]->setStyleSheet("QProgressBar { background-color: green; }");
    } else {
        searchBars[index]->setStyleSheet("QProgressBar { background-color: red; }");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[index]->setText(QString("Knuth-Morris-Pratt (KMP) tardó %1 ms").arg(duration / 1000.0));
}

void TextSearchComparisonWidget::computeLPSArray(const QString &pattern, int m, QVector<int> &lps) {
    int len = 0; // Longitud del anterior prefijo más largo
    lps[0] = 0;  // LPS[0] siempre es 0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void TextSearchComparisonWidget::rabinKarpSearch(const QString &text, const QString &pattern, int index) {
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int m = pattern.length();
    int n = text.length();
    const int d = 256; // Número de caracteres posibles
    const int q = 101; // Un número primo para la hash
    int p = 0; // Hash del patrón
    int t = 0; // Hash del texto
    int h = 1;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i].unicode()) % q;
        t = (d * t + text[i].unicode()) % q;
    }

    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            if (text.mid(i, m) == pattern) {
                found = true;
                break;
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i].unicode() * h) + text[i + m].unicode()) % q;
            if (t < 0)
                t += q;
        }
    }

    if (found) {
        searchBars[index]->setValue(100);
        searchBars[index]->setStyleSheet("QProgressBar { background-color: green; }");
    } else {
        searchBars[index]->setStyleSheet("QProgressBar { background-color: red; }");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[index]->setText(QString("Rabin-Karp tardó %1 ms").arg(duration / 1000.0));
}

void TextSearchComparisonWidget::boyerMooreSearch(const QString &text, const QString &pattern, int index) {
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo

    int m = pattern.length();
    int n = text.length();
    QVector<int> badChar(256, -1); // Inicializar la tabla de bad character

    for (int i = 0; i < m; i++)
        badChar[pattern[i].unicode()] = i;

    int s = 0; // Desplazamiento de patrón
    bool found = false;

    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            found = true;
            break; // Salir del bucle si se encuentra
        } else {
            s += std::max(1, j - badChar[text[s + j].unicode()]);
        }
    }

    if (found) {
        searchBars[index]->setValue(100);
        searchBars[index]->setStyleSheet("QProgressBar { background-color: green; }");
    } else {
        searchBars[index]->setStyleSheet("QProgressBar { background-color: red; }");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[index]->setText(QString("Boyer-Moore tardó %1 ms").arg(duration / 1000.0));
}

void TextSearchComparisonWidget::ahoCorasickSearch(const QString &text, const QString &pattern, int index) {
    auto start = std::chrono::high_resolution_clock::now(); // Iniciar tiempo


    int n = text.length();
    int m = pattern.length();
    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        if (text.mid(i, m) == pattern) {
            found = true;
            break;
        }
    }

    if (found) {
        searchBars[index]->setValue(100);
        searchBars[index]->setStyleSheet("QProgressBar { background-color: green; }");
    } else {
        searchBars[index]->setStyleSheet("QProgressBar { background-color: red; }");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    timeLabels[index]->setText(QString("Aho-Corasick tardó %1 ms").arg(duration / 1000.0));
}
