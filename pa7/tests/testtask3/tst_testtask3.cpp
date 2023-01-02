#include "tst_testtask3.h"

#include "regularroundwindow.h"
#include "ui_roundwindow.h"
#include "letterbox.h"

#define BOX(X, Y) dynamic_cast<LetterBox*>(curRound.ui->gridLayoutBox->itemAtPosition(X, Y)->widget())
#define KEY_PRESS(X) QTest::keyClick(&curRound, Qt::Key_##X)
#define DEL_PRESS    QTest::keyClick(&curRound, Qt::Key_Delete)
#define ENT_PRESS    QTest::keyClick(&curRound, Qt::Key_Return)

void TestTask3::testKeyPresses() {
    RegularRoundWindow curRound {nullptr, 5, false};

    KEY_PRESS(C);
    QCOMPARE(BOX(0, 0)->getLetter(), 'c');

    KEY_PRESS(O);
    QCOMPARE(BOX(0, 1)->getLetter(), 'o');

    KEY_PRESS(M);
    QCOMPARE(BOX(0, 2)->getLetter(), 'm');

    KEY_PRESS(P);
    QCOMPARE(BOX(0, 3)->getLetter(), 'p');

    KEY_PRESS(S);
    QCOMPARE(BOX(0, 4)->getLetter(), 's');
}

void TestTask3::testKeyPressesWithDel() {
    RegularRoundWindow curRound {nullptr, 5, false};

    KEY_PRESS(F);
    QCOMPARE(BOX(0, 0)->getLetter(), 'f');

    KEY_PRESS(A);
    QCOMPARE(BOX(0, 1)->getLetter(), 'a');

    DEL_PRESS;
    QCOMPARE(BOX(0, 1)->getLetter(), ' ');

    KEY_PRESS(U);
    QCOMPARE(BOX(0, 1)->getLetter(), 'u');

    KEY_PRESS(N);
    QCOMPARE(BOX(0, 2)->getLetter(), 'n');

    KEY_PRESS(K);
    QCOMPARE(BOX(0, 3)->getLetter(), 'k');

    KEY_PRESS(Y);
    QCOMPARE(BOX(0, 4)->getLetter(), 'y');

    DEL_PRESS;
    QCOMPARE(BOX(0, 4)->getLetter(), ' ');
}

void TestTask3::testKeyPressesWithEnter()
{
    RegularRoundWindow curRound {nullptr, 5, false};
    curRound.wr->setAnswer("sleep");

    KEY_PRESS(A);
    QCOMPARE(BOX(0, 0)->getLetter(), 'a');

    KEY_PRESS(S);
    QCOMPARE(BOX(0, 1)->getLetter(), 's');

    KEY_PRESS(S);
    QCOMPARE(BOX(0, 2)->getLetter(), 's');

    KEY_PRESS(E);
    QCOMPARE(BOX(0, 3)->getLetter(), 'e');

    KEY_PRESS(T);
    QCOMPARE(BOX(0, 4)->getLetter(), 't');

    ENT_PRESS;
    QCOMPARE(curRound.ui->centralwidget->findChild<Key*>("toolButton_A")->getColor(), GREY);
    QCOMPARE(curRound.ui->centralwidget->findChild<Key*>("toolButton_S")->getColor(), YELLOW);
    QCOMPARE(curRound.ui->centralwidget->findChild<Key*>("toolButton_E")->getColor(), GREEN);
}

#undef BOX
#undef KEY_PRESS
#undef DEL_PRESS
#undef ENT_PRESS

QTEST_MAIN(TestTask3)
