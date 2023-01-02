#ifndef TESTBONUSTASK2_H
#define TESTBONUSTASK2_H

#include <QtTest>

class TestBonusTask2 : public QObject
{
    Q_OBJECT

public:
    TestBonusTask2() = default;
    ~TestBonusTask2() = default;

private slots:
    void testGridLayoutInit_data();
    void testGridLayoutInit();

    void testMultiRoundWindowSimple();

    void testMultiMainWindowSimple();
};

#endif // TESTBONUSTASK2_H
