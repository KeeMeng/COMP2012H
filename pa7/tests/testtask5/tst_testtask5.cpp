#include "tst_testtask5.h"

#include "regularroundwindow.h"
#include "ui_roundwindow.h"

bool validHardModeGuess(const QString& guess, const bool correctLetters[]);

struct CorrectLetters {
    bool isCorrect[26] = {false};
    CorrectLetters& setLetter(const char letter) { isCorrect[letter - 'a'] = true; return *this; }
};

void TestTask5::testHardModeFunction_data() {
    QTest::addColumn<QString>("guess");
    QTest::addColumn<CorrectLetters>("correctLetters");
    QTest::addColumn<bool>("expectedValid");

    QTest::newRow("HOUSE vs. B C") << "house" << (CorrectLetters){}.setLetter('b').setLetter('c') << false;
    QTest::newRow("HOUSE vs. O U") << "house" << (CorrectLetters){}.setLetter('o').setLetter('u') << true;
}

void TestTask5::testHardModeFunction() {
    QFETCH(QString, guess);
    QFETCH(CorrectLetters, correctLetters);
    QFETCH(bool, expectedValid);

    bool actualValid = validHardModeGuess(guess, correctLetters.isCorrect);
    QCOMPARE(actualValid, expectedValid);
}

#define KEY_PRESS(X) if (Key* key = curRound.ui->centralwidget->findChild<Key*>("toolButton_"#X)) \
                        QTest::mouseClick(key, Qt::LeftButton); \
                    else \
                        QTest::keyClick(&curRound, Qt::Key_##X);
#define ENT_PRESS    if (QPushButton* key = curRound.ui->centralwidget->findChild<QPushButton*>("pushButton_Enter")) \
                        QTest::mouseClick(key, Qt::LeftButton); \
                    else \
                        QTest::keyClick(&curRound, Qt::Key_Return);

void TestTask5::testHardModeRoundWindow() {
    hasPopup = false;
    RegularRoundWindow curRound {nullptr, 5, true};
    curRound.wr->setAnswer("sleep");

    KEY_PRESS(P);
    KEY_PRESS(L);
    KEY_PRESS(U);
    KEY_PRESS(C);
    KEY_PRESS(K);
    ENT_PRESS;

    KEY_PRESS(A);
    KEY_PRESS(S);
    KEY_PRESS(S);
    KEY_PRESS(E);
    KEY_PRESS(T);
    QTimer::singleShot(500, this, &TestTask5::verifyInvalidHardModePopup);
    ENT_PRESS;

    if (!hasPopup)
        QFAIL("Did not see the correct popup.");
}

#undef KEY_PRESS
#undef ENT_PRESS

void TestTask5::verifyInvalidHardModePopup() {
    QWidgetList allToplevelWidgets = QApplication::topLevelWidgets();
    for (QWidget *w : allToplevelWidgets) {
        if (w->inherits("QMessageBox")) {
            QMessageBox *mb = qobject_cast<QMessageBox*>(w);
            hasPopup = mb->text() == "You must use yellow and green letters in Hard Mode!";
            QTest::keyClick(mb, Qt::Key_Enter);
            break;
        }
    }
}

QTEST_MAIN(TestTask5)
