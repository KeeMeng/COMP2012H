#ifndef TESTTASK3_H
#define TESTTASK3_H

#include <QtTest>

class TestTask3 : public QObject
{
    Q_OBJECT

public:
    TestTask3() = default;
    ~TestTask3() = default;

private slots:
    void testKeyPresses();
    void testKeyPressesWithDel();
    void testKeyPressesWithEnter();

};

#endif // TESTTASK3_H
