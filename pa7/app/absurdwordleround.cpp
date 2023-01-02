#include "absurdwordleround.h"

#include <QList>

AbsurdWordleRound::AbsurdWordleRound(QWidget *parent, const int len):
    WordleRound(parent, len, false)
{
    initGuesses(parent);
    solver.setEnabled(false);
}

// Add extra guesses for this mode
int AbsurdWordleRound::calculateNumGuesses(const int len) {
    return WordleRound::calculateNumGuesses(len) + 5;
}

/**
 * TODO: BONUS TASK 1
 *
 * @brief Change the 'answer' by one letter, so that it still belongs to 'allAnswers'.
 * @param answer: original answer word
 * @param allAnswers: all possible answers, new answer must come from this set
 * @return a word from 'allAnswers' that differs from 'answer' by (at most) one letter.
 *
 * Create a list of words considered "adjacent" to the current answer:
 * words that differ by the answer by exactly one letter.
 *
 * For each possible answer, loop over each letter
 * and count the number of times the letter is different
 * for the current answer and possible answer.
 * If this value is 1, add the possible answer to the "adjacent" list.
 *
 * Finally, select a random word from the "adjacent" list to be the new answer.
 * If this list is empty, return the original answer.
 */
QString alterAnswer(const QString& answer, const QSet<QString>& allAnswers) {
    QSet<QString>::const_iterator i;
    QList<QString> adjacent;
    for (i = allAnswers.begin(); i != allAnswers.end(); i++) {
        int difference = 0;
        for (int j = 0; j < answer.length(); j++) {
            if (i->at(j) != answer[j]) {
                difference++;
            }
        }
        if (difference == 1) {
            adjacent.append(*i);
        }
    }
    if (adjacent.length() == 0) {
        return answer;
    } else if (adjacent.length() == 1) {
        return adjacent[0];
    } else {
        return adjacent.at(arc4random() % adjacent.length());
    }
}


void AbsurdWordleRound::endGuessAttempt(const bool correctGuess) {
    // Perform endGuess tasks like normal
    WordleRound::endGuessAttempt(correctGuess);

    // If incorrect guess and game has not ended, change the answer by one letter
    if (!correctGuess && curGuess != numGuesses) {
        answer = alterAnswer(answer, dict.getAllAnswers());
    }
}
