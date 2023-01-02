#ifndef TST_TESTBONUSTASK3_H
#define TST_TESTBONUSTASK3_H

#include <QtTest>

class TestBonusTask3 : public QObject
{
    Q_OBJECT

public:
    TestBonusTask3() = default;
    ~TestBonusTask3() = default;

private slots:
    void testTimedRoundWindowBasic();
    void testTimedRoundWindowInvalidWord();
    void testTimedRoundWindowRoundWin();
    void testTimedRoundWindowSkipWord();

    void testTimedMainWindow();
};

#endif // TST_TESTBONUSTASK3_H
