#ifndef TESTBONUSTASK1_H
#define TESTBONUSTASK1_H

#include <QtTest>

class TestBonusTask1 : public QObject
{
    Q_OBJECT

private:
    QSet<QString> dummyAnswers {};

public:
    TestBonusTask1();
    ~TestBonusTask1() = default;

private slots:
    void testAlterAnswerFunction_data();
    void testAlterAnswerFunction();

    void testAbsurdRoundWindow();
};

#endif // TESTBONUSTASK1_H
