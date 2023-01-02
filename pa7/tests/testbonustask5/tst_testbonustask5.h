#ifndef TESTBONUSTASK5_H
#define TESTBONUSTASK5_H

#include <QtTest>

class TestBonusTask5 : public QObject
{
    Q_OBJECT

public:
    TestBonusTask5() = default;
    ~TestBonusTask5() = default;

private slots:
    void testReadAnswerFile_data();
    void testReadAnswerFile();
};

#endif // TESTBONUSTASK5_H
