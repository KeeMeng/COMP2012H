#include "tst_testtask1.h"

// add necessary includes here
#include "letterbox.h"
QColor* analyzeGuess(const QString& guess, const QString& answer);

struct Color5 {
    QColor color[5];

    inline bool operator==(const Color5& other) const {
        for (int i=0; i<5; ++i) if (color[i] != other.color[i]) return false;
        return true;
    }
};

struct Color9 {
    QColor color[9];

    inline bool operator==(const Color9& other) const {
        for (int i=0; i<9; ++i) if (color[i] != other.color[i]) return false;
        return true;
    }
};


void TestTask1::testAnalyzeGuess_data() {
    QTest::addColumn<QString>("guess");
    QTest::addColumn<QString>("answer");
    QTest::addColumn<Color5>("expectedColor");

    QTest::newRow("PLUCK vs. SLEEP") << "pluck" << "sleep" << (Color5){YELLOW, GREEN, GREY, GREY, GREY};
    QTest::newRow("ASSET vs. SLEEP") << "asset" << "sleep" << (Color5){GREY, YELLOW, GREY, GREEN, GREY};
    QTest::newRow("PLUMP vs. SLEEP") << "plump" << "sleep" << (Color5){GREY, GREEN, GREY, GREY, GREEN};
    QTest::newRow("GEESE vs. SLEEP") << "geese" << "sleep" << (Color5){GREY, YELLOW, GREEN, YELLOW, GREY};
}

void TestTask1::testAnalyzeGuess()
{
    QFETCH(QString, guess);
    QFETCH(QString, answer);
    QFETCH(Color5, expectedColor);
    QColor *color = analyzeGuess(guess, answer);
    if (!color) {
        QFAIL("Got nullptr for color array");
    }
    Color5 actualColor;
    for (int i=0; i<5; ++i) {
        actualColor.color[i] = color[i];
    }
    delete [] color;

    QCOMPARE(actualColor, expectedColor);
}

void TestTask1::testAnalyzeGuessLong_data() {
    QTest::addColumn<QString>("guess");
    QTest::addColumn<QString>("answer");
    QTest::addColumn<Color9>("expectedColor");

    QTest::newRow("DOCTORATE vs. HYDROGENS") << "doctorate" << "hydrogens"
             << (Color9){YELLOW, GREY, GREY, GREY, GREEN, YELLOW, GREY, GREY, YELLOW};
}

void TestTask1::testAnalyzeGuessLong()
{
    QFETCH(QString, guess);
    QFETCH(QString, answer);
    QFETCH(Color9, expectedColor);
    QColor *color = analyzeGuess(guess, answer);
    if (!color) {
        QFAIL("Got nullptr for color array");
    }
    Color9 actualColor;
    for (int i=0; i<9; ++i) {
        actualColor.color[i] = color[i];
    }
    delete [] color;

    QCOMPARE(actualColor, expectedColor);
}

QTEST_MAIN(TestTask1)
