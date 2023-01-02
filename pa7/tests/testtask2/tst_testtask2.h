#ifndef TESTTASK2_H
#define TESTTASK2_H

#include <QtTest>

class TestTask2 : public QObject
{
    Q_OBJECT

public:
    TestTask2() = default;
    ~TestTask2() = default;

private slots:
    void testKeyPresses();
    void testKeyPressesWithDel();
    void testKeyPressesWithEnter();

};

#endif // TESTTASK2_H
