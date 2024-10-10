#ifndef HASHCOMPARISONWIDGET_H
#define HASHCOMPARISONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <vector>
#include <functional>

class HashComparisonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HashComparisonWidget(QWidget *parent = nullptr);

private slots:
    void compareHashes();

private:
    void setupUI();
    void displayResults(std::vector<long long> times);

    // Algoritmos de hash
    unsigned long long simpleSumHash(const std::string &input);
    unsigned long long xorHash(const std::string &input);
    unsigned long long djb2Hash(const std::string &input);
    unsigned long long fnv1aHash(const std::string &input);
    unsigned long long rotatingHash(const std::string &input);

    QLineEdit *inputField;  // Campo de texto para ingresar el input
    std::vector<QLabel*> labels;
    std::vector<QProgressBar*> progressBars;
    QPushButton *startButton;
};

#endif // HASHCOMPARISONWIDGET_H
