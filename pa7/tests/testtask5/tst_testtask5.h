#ifndef TESTTASK5_H
#define TESTTASK5_H

#include <QtTest>

class TestTask5 : public QObject
{
    Q_OBJECT

private:
    bool hasPopup {false};

public:
    TestTask5() = default;
    ~TestTask5() = default;

public slots:
    void verifyInvalidHardModePopup();

private slots:
    void testHardModeFunction_data();
    void testHardModeFunction();

    void testHardModeRoundWindow();
};

#endif // TESTTASK5_H
