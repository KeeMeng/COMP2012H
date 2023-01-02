#include "tst_testbonustask1.h"

#include "absurdroundwindow.h"
#include "ui_roundwindow.h"

QString alterAnswer(const QString& answer, const QSet<QString>& allAnswers);

TestBonusTask1::TestBonusTask1() {
    dummyAnswers.insert("spell");
    dummyAnswers.insert("swell");
    dummyAnswers.insert("shell");
    dummyAnswers.insert("smell");
    dummyAnswers.insert("sells");
    dummyAnswers.insert("match");
    dummyAnswers.insert("latch");
}

void TestBonusTask1::testAlterAnswerFunction_data() {
    QTest::addColumn<QString>("answer");
    QTest::addColumn<QSet<QString>>("possibleAlters");

    QSet<QString> spellAdj {"swell", "shell", "smell"};
    QTest::newRow("SPELL") << "spell" << spellAdj;

    QSet<QString> latchAdj {"match"};
    QTest::newRow("LATCH") << "latch" << latchAdj;

    QSet<QString> sellsAdj {"sells"};
    QTest::newRow("SELLS") << "sells" << sellsAdj;
}

void TestBonusTask1::testAlterAnswerFunction() {
    QFETCH(QString, answer);
    QFETCH(QSet<QString>, possibleAlters);

    QString alteredAnswer = alterAnswer(answer, dummyAnswers);
    QVERIFY2(possibleAlters.find(alteredAnswer) != possibleAlters.end(), QString("got " + alteredAnswer).toStdString().c_str());
}

#define KEY_PRESS(X) if (Key* key = curRound.ui->centralwidget->findChild<Key*>("toolButton_"#X)) \
                        QTest::mouseClick(key, Qt::LeftButton); \
                    else \
                        QTest::keyClick(&curRound, Qt::Key_##X);
#define ENT_PRESS    if (QPushButton* key = curRound.ui->centralwidget->findChild<QPushButton*>("pushButton_Enter")) \
                        QTest::mouseClick(key, Qt::LeftButton); \
                    else \
                        QTest::keyClick(&curRound, Qt::Key_Return);

void TestBonusTask1::testAbsurdRoundWindow() {
    AbsurdRoundWindow curRound {nullptr, 5};
    curRound.wr->setAnswer("sleep");

    KEY_PRESS(T);
    KEY_PRESS(E);
    KEY_PRESS(S);
    KEY_PRESS(T);
    KEY_PRESS(S);
    ENT_PRESS;

    QString alter = curRound.wr->getAnswer();
    int numDiffLetters = (alter[0] != 's') + (alter[1] != 'l') + (alter[2] != 'e') + (alter[3] != 'e') + (alter[4] != 'p');
    QCOMPARE(numDiffLetters, 1);
}

#undef KEY_PRESS
#undef ENT_PRESS

QTEST_MAIN(TestBonusTask1)
