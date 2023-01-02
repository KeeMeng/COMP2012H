#include "dictionary.h"

#include <QDebug>
#include <QFile>
#include <QDir>

Dictionary::Dictionary(int word_length): word_length(word_length)
{
    QString wordsFilename {":/dictionary/words_{}.txt"};
    wordsFilename.replace("{}", QString::number(word_length));
    QFile wordsFile(wordsFilename);
    if (wordsFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&wordsFile);
        while (!in.atEnd()) {
            QString word = in.readLine();
            words.insert(word);
        }
        if (words.empty()) {
            throw DictionaryException("No valid English words with this length.");
        }
    }
    else {
        throw DictionaryException("Something went wrong reading words.");
    }

    /**
     * TODO: BONUS TASK 5
     *
     * Read the word frequency list from answers_{}.csv and put into 'answers'.
     *
     * Hint: You can reference the code above to read from a file
     * and throw exceptions if file is unavailable or there are no answers.
     */


    QString answersFilename {":/dictionary/answers_{}.csv"};
    answersFilename.replace("{}", QString::number(word_length));
    QFile answersFile(answersFilename);
    if (answersFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&answersFile);
        in.readLine();
        while (!in.atEnd()) {
            QList<QString> line = in.readLine().split(',');
            WordFrequency wordf;
            wordf.word = line[0];
            wordf.count = line[1].toULongLong();
            answers.append(wordf);
            answerCount++;
        }
        if (answers.empty()) {
            throw DictionaryException("No valid English words with this length.");
        }
    }
    else {
        throw DictionaryException("Something went wrong reading words.");
    }
}

/**
 * TODO: BONUS TASK 5
 *
 * Return a random word from the answer list.
 * The word count should reflect how likely this word would be picked as an answer.
 *
 * Hint: You can generate 2 random 32-bit numbers and combine into a 64-bit random unsigned long long.
 */
QString Dictionary::getRandomAnswer() const {
    int i1 = arc4random();
    int i2 = arc4random();
    unsigned long long index = (((long long)i1 << 32) | (long long)i2);

    // total words include duplicates
    unsigned long long total_words = 0;
    Q_FOREACH (const WordFrequency& wordf, answers) {
        total_words += wordf.count;
    }

    index %= total_words;

    Q_FOREACH (const WordFrequency& wordf, answers) {
        if (index < wordf.count) {
            return wordf.word;
        }
        index -= wordf.count;
    }

    // should never occur
    return answers.at(arc4random() % words.size()).word;
}

/**
 * TODO: BONUS TASK 5
 *
 * Return a word set using 'answers' instead of 'words'
 */
QSet<QString> Dictionary::getAllAnswers() const {
    QSet<QString> common_words = {};

    for (unsigned long long i = 0; i < answerCount; i++) {
        common_words.insert(answers.at(i).word);
    }

    return common_words;
}

bool Dictionary::isValidWord(const QString& word) const {
    QSet<QString>::const_iterator it = words.find(word);
    return it != words.end();
}
