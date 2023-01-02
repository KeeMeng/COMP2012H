#ifndef TST_TESTTASK1_H
#define TST_TESTTASK1_H

#include <QtTest>

class TestTask1 : public QObject
{
    Q_OBJECT

public:
    TestTask1() = default;
    ~TestTask1() = default;

private slots:
    void testAnalyzeGuess_data();
    void testAnalyzeGuess();

    void testAnalyzeGuessLong_data();
    void testAnalyzeGuessLong();
};

#endif // TST_TESTTASK1_H
