#include "tst_testbonustask4.h"

#include "solver.h"
#include "letterbox.h"

double computeEntropy(const QString& word, const QSet<QString>& possibleAnswers);

TestBonusTask4::TestBonusTask4()
{
    dummyAnswers.insert("spell");
    dummyAnswers.insert("swell");
    dummyAnswers.insert("shell");
    dummyAnswers.insert("smell");
    dummyAnswers.insert("sells");
    dummyAnswers.insert("match");
    dummyAnswers.insert("latch");
    dummyAnswers.insert("catch");
    dummyAnswers.insert("morph");
}

void TestBonusTask4::testComputeEntropy_data() {
    QTest::addColumn<QString>("wordSmallEntropy");
    QTest::addColumn<QString>("wordLargeEntropy");

    QTest::newRow("FAKES less entropy than SPELL") << "fakes" << "spell";
    QTest::newRow("HATCH less entropy than WIMPY") << "hatch" << "wimpy";
}

void TestBonusTask4::testComputeEntropy() {
    QFETCH(QString, wordSmallEntropy);
    QFETCH(QString, wordLargeEntropy);

    double smallEntropy = computeEntropy(wordSmallEntropy, dummyAnswers);
    double largeEntropy = computeEntropy(wordLargeEntropy, dummyAnswers);

    QVERIFY2(smallEntropy < largeEntropy,
             QString(QString::number(smallEntropy) + " is not smaller than " + QString::number(largeEntropy)).toStdString().c_str());
}

void TestBonusTask4::testSolverHint() {
    Solver solver {dummyAnswers};

    // Uncomment to debug entropy values
    for (const QString& word : qAsConst(dummyAnswers)) {
        qDebug() << word << ": " << computeEntropy(word, dummyAnswers);
    }

    QCOMPARE(solver.hint(), "morph");
}

void TestBonusTask4::testSolverHintWithUpdate() {
    Solver solver {dummyAnswers};

    QColor colors[5] = {GREY, GREY, GREY, GREY, YELLOW};
    solver.updateAnswers("banks", colors);

    qDebug() << solver.possibleAnswers;

    QCOMPARE(solver.getRemainingNumAnswers(), 4);
    QCOMPARE(solver.hint(), "morph");
}

QTEST_MAIN(TestBonusTask4)
