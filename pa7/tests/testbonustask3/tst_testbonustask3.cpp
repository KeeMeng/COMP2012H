#include "tst_testbonustask3.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timedroundwindow.h"
#include "ui_roundwindow.h"

#include <QComboBox>
#include <QSpinBox>

QString timeToStr(const QTime& time);
QString scoreToStr(const int score);

#define KEY_PRESS(X) if (Key* key = curRound.ui->centralwidget->findChild<Key*>("toolButton_"#X)) \
                        QTest::mouseClick(key, Qt::LeftButton); \
                    else \
                        QTest::keyClick(&curRound, Qt::Key_##X);
#define ENT_PRESS    if (QPushButton* key = curRound.ui->centralwidget->findChild<QPushButton*>("pushButton_Enter")) \
                        QTest::mouseClick(key, Qt::LeftButton); \
                    else \
                        QTest::keyClick(&curRound, Qt::Key_Return);

void TestBonusTask3::testTimedRoundWindowBasic() {
    TimedRoundWindow curRound {nullptr, 5, false, 3};
    QCOMPARE(curRound.timeLeft, QTime(0, 3, 0));
    if (!curRound.timerLineEdit) QFAIL("Timer display not implemented.");
    QCOMPARE(curRound.timerLineEdit->text(), timeToStr(QTime(0, 3, 0)));
    if (!curRound.scoreLineEdit) QFAIL("Score display not implemented.");
    QCOMPARE(curRound.scoreLineEdit->text(), scoreToStr(0));
}

void TestBonusTask3::testTimedRoundWindowInvalidWord() {
    TimedRoundWindow curRound {nullptr, 5, false, 1};
    curRound.wr->setAnswer("sleep");

    KEY_PRESS(A); KEY_PRESS(B); KEY_PRESS(C); KEY_PRESS(D); KEY_PRESS(E);
    ENT_PRESS;
    if (!curRound.messageLineEdit) QFAIL("Message display not implemented.");
    QCOMPARE(curRound.messageLineEdit->text(), "Word not in dictionary.");
}

void TestBonusTask3::testTimedRoundWindowRoundWin() {
    TimedRoundWindow curRound {nullptr, 5, false, 1};
    curRound.wr->setAnswer("sleep");

    KEY_PRESS(S); KEY_PRESS(L); KEY_PRESS(E); KEY_PRESS(E); KEY_PRESS(P);
    ENT_PRESS;
    if (!curRound.messageLineEdit) QFAIL("Message display not implemented.");
    QCOMPARE(curRound.messageLineEdit->text(), "Correct! +1 point.");
    if (!curRound.scoreLineEdit) QFAIL("Score display not implemented.");
    QCOMPARE(curRound.scoreLineEdit->text(), scoreToStr(1));
}

void TestBonusTask3::testTimedRoundWindowSkipWord() {
    TimedRoundWindow curRound {nullptr, 5, false, 1};
    curRound.wr->setAnswer("sleep");

    KEY_PRESS(S); KEY_PRESS(T); KEY_PRESS(E); KEY_PRESS(A); KEY_PRESS(K);
    ENT_PRESS;
    if (!curRound.skipWordPushButton) QFAIL("Skip button not implemented.");
    QTest::mouseClick(curRound.skipWordPushButton, Qt::LeftButton);
    QCOMPARE(dynamic_cast<LetterBox*>(curRound.ui->gridLayoutBox->itemAtPosition(0, 0)->widget())->getLetter(), ' ');
}

#undef KEY_PRESS
#undef ENT_PRESS

#define COMBOBOX_MODE w.ui->centralwidget->findChild<QComboBox*>("comboBoxMode")
#define SPINBOX_WORDLENGTH w.ui->centralwidget->findChild<QSpinBox*>("spinBoxWordLength")
#define COMBOBOX_TIME w.ui->centralwidget->findChild<QComboBox*>("comboBoxTime")
#define WIDGET_CHECK if(!COMBOBOX_MODE || !SPINBOX_WORDLENGTH || !COMBOBOX_TIME) QFAIL("Required widgets not found.");

void TestBonusTask3::testTimedMainWindow() {
    MainWindow w;

    WIDGET_CHECK;

    COMBOBOX_MODE->setCurrentText("Timed");
    SPINBOX_WORDLENGTH->setValue(5);
    COMBOBOX_TIME->setCurrentText("3 minutes");

    QTest::mouseClick(w.ui->pushButton, Qt::LeftButton);
    while (!w.curRound) {
        // wait for curRound to be initialized
    }
    w.curRound->hide();

    if (!dynamic_cast<TimedRoundWindow*>(w.curRound)->timerLineEdit) QFAIL("Timer display not implemented.");
    QCOMPARE(dynamic_cast<TimedRoundWindow*>(w.curRound)->timerLineEdit->text(), timeToStr(QTime(0, 3, 0)));
}

#undef COMBOBOX_MODE
#undef SPINBOX_WORDLENGTH
#undef COMBOBOX_TIME
#undef WIDGET_CHECK

QTEST_MAIN(TestBonusTask3)
