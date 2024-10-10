#ifndef SEARCHRACEWIDGET_H
#define SEARCHRACEWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <vector>
#include <chrono>
#include <QLabel>
#include <QLineEdit>

class SearchRaceWidget : public QWidget {
    Q_OBJECT

public:
    explicit SearchRaceWidget(QWidget *parent = nullptr);

private:
    void setTargetValue();
    void runLinearSearch();
    void runBinarySearch();
    void runJumpSearch();
    void startSearchRace();
    void updateProgress();
    void runInterpolationSearch();
    void runExponentialSearch();

    std::vector<QProgressBar *> searchBars;
    QTimer *timer;
    int currentProgress;

    std::vector<int> dataValues;
    int targetValue;

    QLabel *timeLabels[5];
    std::chrono::high_resolution_clock::time_point startTime;

    QLineEdit *lineEditTargetValue;
};

#endif // SEARCHRACEWIDGET_H
