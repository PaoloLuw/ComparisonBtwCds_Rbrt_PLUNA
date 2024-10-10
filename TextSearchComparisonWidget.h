#ifndef TEXTSEARCHCOMPARISONWIDGET_H
#define TEXTSEARCHCOMPARISONWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QVector>
#include <QString>

class TextSearchComparisonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextSearchComparisonWidget(QWidget *parent = nullptr);

private slots:
    void startComparison(const QString &text, const QString &pattern);
    void bruteForceSearch(const QString &text, const QString &pattern, int index);
    void kmpSearch(const QString &text, const QString &pattern, int index);
    void rabinKarpSearch(const QString &text, const QString &pattern, int index);
    void boyerMooreSearch(const QString &text, const QString &pattern, int index);
    void ahoCorasickSearch(const QString &text, const QString &pattern, int index);
    void computeLPSArray(const QString &pattern, int m, QVector<int> &lps);

private:
    QLineEdit *textInput;
    QLineEdit *patternInput;
    QPushButton *startButton;
    QLabel *timeLabels[5];
    QVector<QProgressBar *> searchBars;
};

#endif // TEXTSEARCHCOMPARISONWIDGET_H
