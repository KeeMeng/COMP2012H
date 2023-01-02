#include "tst_testtask4.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

#define LABEL_MODE w.ui->centralwidget->findChild<QLabel*>("labelMode")
#define COMBOBOX_MODE w.ui->centralwidget->findChild<QComboBox*>("comboBoxMode")
#define LABEL_WORDLENGTH w.ui->centralwidget->findChild<QLabel*>("labelWordLength")
#define SPINBOX_WORDLENGTH w.ui->centralwidget->findChild<QSpinBox*>("spinBoxWordLength")
#define CHECKBOX_HARDMODE w.ui->centralwidget->findChild<QCheckBox*>("checkBoxHardMode")
#define LABEL_NUMWORDS w.ui->centralwidget->findChild<QLabel*>("labelNumWords")
#define SPINBOX_NUMWORDS w.ui->centralwidget->findChild<QSpinBox*>("spinBoxNumWords")
#define LABEL_TIME w.ui->centralwidget->findChild<QLabel*>("labelTime")
#define COMBOBOX_TIME w.ui->centralwidget->findChild<QComboBox*>("comboBoxTime")

#define WIDGET_CHECK if(!LABEL_MODE || !COMBOBOX_MODE || !LABEL_WORDLENGTH || !SPINBOX_WORDLENGTH || \
                        !CHECKBOX_HARDMODE || !LABEL_NUMWORDS || !SPINBOX_NUMWORDS || !LABEL_TIME || \
                        !COMBOBOX_TIME) QFAIL("Required widgets not found.");

void TestTask4::testSelectModeRegular() {
    MainWindow w;

    WIDGET_CHECK;

    QVERIFY(LABEL_MODE->isVisibleTo(&w));
    QVERIFY(COMBOBOX_MODE->isVisibleTo(&w));
    QVERIFY(LABEL_WORDLENGTH->isVisibleTo(&w));
    QVERIFY(SPINBOX_WORDLENGTH->isVisibleTo(&w));

    COMBOBOX_MODE->setCurrentText("Regular");
    QVERIFY(CHECKBOX_HARDMODE->isVisibleTo(&w));
    QVERIFY(!LABEL_NUMWORDS->isVisibleTo(&w));
    QVERIFY(!SPINBOX_NUMWORDS->isVisibleTo(&w));
    QVERIFY(!LABEL_TIME->isVisibleTo(&w));
    QVERIFY(!COMBOBOX_TIME->isVisibleTo(&w));
}

void TestTask4::testSelectModeAbsurd() {
    MainWindow w;

    WIDGET_CHECK;

    COMBOBOX_MODE->setCurrentText("Absurd");
    QVERIFY(!CHECKBOX_HARDMODE->isVisibleTo(&w));
    QVERIFY(!LABEL_NUMWORDS->isVisibleTo(&w));
    QVERIFY(!SPINBOX_NUMWORDS->isVisibleTo(&w));
    QVERIFY(!LABEL_TIME->isVisibleTo(&w));
    QVERIFY(!COMBOBOX_TIME->isVisibleTo(&w));
}

void TestTask4::testSelectModeMulti() {
    MainWindow w;

    WIDGET_CHECK;

    COMBOBOX_MODE->setCurrentText("Multiple");
    QVERIFY(!CHECKBOX_HARDMODE->isVisibleTo(&w));
    QVERIFY(LABEL_NUMWORDS->isVisibleTo(&w));
    QVERIFY(SPINBOX_NUMWORDS->isVisibleTo(&w));
    QVERIFY(!LABEL_TIME->isVisibleTo(&w));
    QVERIFY(!COMBOBOX_TIME->isVisibleTo(&w));
}

void TestTask4::testSelectModeTimed() {
    MainWindow w;

    WIDGET_CHECK;

    COMBOBOX_MODE->setCurrentText("Timed");
    QVERIFY(CHECKBOX_HARDMODE->isVisibleTo(&w));
    QVERIFY(!LABEL_NUMWORDS->isVisibleTo(&w));
    QVERIFY(!SPINBOX_NUMWORDS->isVisibleTo(&w));
    QVERIFY(LABEL_TIME->isVisibleTo(&w));
    QVERIFY(COMBOBOX_TIME->isVisibleTo(&w));
}

void TestTask4::testStartRegularRound() {
    MainWindow w;

    WIDGET_CHECK;

    COMBOBOX_MODE->setCurrentText("Regular");
    SPINBOX_WORDLENGTH->setValue(6);

    QTest::mouseClick(w.ui->pushButton, Qt::LeftButton);
    while (!w.curRound) {
        // wait for curRound to be initialized
    }
    w.curRound->hide();
    QCOMPARE(w.curRound->wr->getLength(), 6);
}

#undef LABEL_MODE
#undef COMBOBOX_MODE
#undef LABEL_WORDLENGTH
#undef SPINBOX_WORDLENGTH
#undef CHECKBOX_HARDMODE
#undef LABEL_NUMWORDS
#undef SPINBOX_NUMWORDS
#undef LABEL_TIME
#undef COMBOBOX_TIME
#undef WIDGET_CHECK

QTEST_MAIN(TestTask4)
