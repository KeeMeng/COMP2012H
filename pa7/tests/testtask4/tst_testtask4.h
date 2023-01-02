#ifndef TESTTASK4_H
#define TESTTASK4_H

#include <QtTest>

class TestTask4 : public QObject
{
    Q_OBJECT

public:
    TestTask4() = default;
    ~TestTask4() = default;

private slots:
    void testSelectModeRegular();
    void testSelectModeAbsurd();
    void testSelectModeMulti();
    void testSelectModeTimed();

    void testStartRegularRound();
};

#endif // TESTTASK4_H
