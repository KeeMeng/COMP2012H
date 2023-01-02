#include "solver.h"
#include "letterbox.h"

#include <cmath>
#include <QColor>

Solver::Solver(const QSet<QString>& allWords)
{
    this->allWords = possibleAnswers = allWords;
}

void Solver::reset(const QSet<QString>& allWords) {
    possibleAnswers = allWords;
}

// Reuse this function in wordleround.cpp
QColor* analyzeGuess(const QString& guess, const QString& answer);

// Helper function to convert color to bin index
int colorToInt(const QColor* const colors, const int length) {
    int index = 0;
    for (int i=0; i<length; ++i) {
        if (colors[i] == GREY) index += 0 * pow(3, i);
        else if (colors[i] == YELLOW) index += 1 * pow(3, i);
        else if (colors[i] == GREEN) index += 2 * pow(3, i);
    }
    return index;
}

/**
 * TODO: BONUS TASK 4
 *
 * @brief Calculate the average entropy for guessing this word
 * @param word: word to compute entropy
 * @param possibleAnswers: set of remaining possible answers
 * @return double: average entropy associated with this guess
 *
 * - Generate a bin (int array) of size 3^length for each possible QColor arrangement
 * - For each possible answer:
 *      + Get the QColor arrangement if 'word' was a guess for 'answer' using analyzeGuess(),
 *      + Convert to bin index using colorToInt(), add 1 to that bin
 * - Calculate entropy using the formula:
 *      entropy = Sum(- p * log2(p));
 *   where p is the probability each QColor arrangement would be the actual result (= bin[i] / number of answers)
 */
double computeEntropy(const QString& word, const QSet<QString>& possibleAnswers) {
    int* bin = new int[pow(3, word.length())];
    for (long long i = 0; i < pow(3, word.length()); i++) {
        bin[i] = 0;
    }

    double entropy = 0.0;
    for (QSet<QString>::const_iterator i = possibleAnswers.begin(); i != possibleAnswers.end(); i++) {
        QColor* color = analyzeGuess(word, *i);
        bin[colorToInt(color, word.length())]++;
        delete [] color;
    }

    double p = 0.0;
    for (long long i = 0; i < pow(3, word.length()); i++) {
        p = (double)bin[i] / (double)possibleAnswers.size();
        if (p > 0) {
            entropy -= p * log2(p);
        }
    }

    delete [] bin;

    return entropy;
}

/**
 * TODO: BONUS TASK 4
 *
 * If only 1 possible answer left, return that answer.
 *
 * Else, for each word in all possible words,
 * calculate its entropy with computeEntropy().
 * Return the word with the highest entropy.
 */
QString Solver::hint() {
    if (!enabled) return "";

    if (possibleAnswers.size() == 1) {
        return *possibleAnswers.begin();
    } else {
        double entropy = 0.0;
        double highest_entropy = 0.0;
        QString word = "";
        for (QSet<QString>::const_iterator i = allWords.begin(); i != allWords.end(); i++) {
            entropy = computeEntropy(*i, possibleAnswers);
            if (entropy > highest_entropy) {
                highest_entropy = entropy;
                word = *i;
            }
        }
        return word;
    }
}

/**
 * TODO: BONUS TASK 4
 *
 * For each word in remaining possible answers,
 * calculate the color sequence if 'guess' was used as a guess.
 * If the color does not match with the provided colors,
 * the word must not be a possible solution,
 * remove it from the set of possible answers.
 */
void Solver::updateAnswers(const QString& guess, QColor* const colors) {
    if (!enabled) return;

    QList<QString> toRemove;
    for (QSet<QString>::iterator i = possibleAnswers.begin(); i != possibleAnswers.end(); i++) {
        QColor* possibleColors = analyzeGuess(guess, *i);
        for (int j = 0; j < guess.length(); j++) {
            if (possibleColors[j] != colors[j]) {
                toRemove.append(*i);
                break;
            }
        }
        delete [] possibleColors;
    }

    for (int i = 0; i < toRemove.length(); i++) {
        possibleAnswers.remove(toRemove[i]);
    }
}
