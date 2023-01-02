#include "tst_testbonustask5.h"

#include "dictionary.h"

void TestBonusTask5::testReadAnswerFile_data() {
    QTest::addColumn<int>("wordLength");
    QTest::addColumn<int>("expectedAnswerCount");
    QTest::addColumn<QString>("word");
    QTest::addColumn<unsigned long long>("expectedCount");

    QTest::newRow("5 letters") << 5 << 9385 << "hours" << 198242904ULL;
    QTest::newRow("10 letters") << 10 << 9396 << "electronic" << 76707502ULL;
}

void TestBonusTask5::testReadAnswerFile() {
    QFETCH(int, wordLength);
    QFETCH(int, expectedAnswerCount);
    QFETCH(QString, word);
    QFETCH(unsigned long long, expectedCount);

    try {
        Dictionary dict {wordLength};

        QCOMPARE(dict.getAllAnswers().count(), expectedAnswerCount);
        for (const Dictionary::WordFrequency& wf : dict.answers) {
            if (wf.word == word) {
                QCOMPARE(wf.count, expectedCount);
                break;
            }
        }
    }
    catch (const DictionaryException& e) {
        QFAIL("Unexpected dictionary exception occured.");
    }
}

QTEST_MAIN(TestBonusTask5)
