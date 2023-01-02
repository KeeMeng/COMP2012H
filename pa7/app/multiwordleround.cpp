#include "multiwordleround.h"

MultiWordleRound::MultiWordleRound(QWidget *parent, const int len, const int numWords):
    WordleRound(parent), numWords(numWords)
{
    this->length = len;
    this->ansMulti = new QString[numWords];
    this->correctGuessesMulti = new bool[numWords];
    dict = Dictionary(length);
    for (int n=0; n<numWords; ++n) {
        this->ansMulti[n] = dict.getRandomAnswer();
        correctGuessesMulti[n] = false;
    }
    initMultiGuesses(parent);
}

MultiWordleRound::~MultiWordleRound() {
    delete [] ansMulti;
    delete [] correctGuessesMulti;
    if (guessesMulti) {
        for (int n=0; n<numWords; ++n) {
            for (int i=0; i<numGuesses; ++i) {
                for (int j=0; j<length; ++j) {
                    SAFE_DELETE(guessesMulti[n][i][j]);
                }
                delete [] guessesMulti[n][i];
            }
            delete [] guessesMulti[n];
        }
        delete [] guessesMulti;
    }
}

int MultiWordleRound::calculateNumGuesses(const int len) {
    return WordleRound::calculateNumGuesses(len) + numWords - 1;
}

void MultiWordleRound::initMultiGuesses(QWidget *parent) {
    numGuesses = MultiWordleRound::calculateNumGuesses(length);
    guessesMulti = new LetterBox***[numWords];
    for (int n=0; n<numWords; ++n) {
        guessesMulti[n] = new LetterBox**[numGuesses];
        for (int i=0; i<numGuesses; ++i) {
            guessesMulti[n][i] = new LetterBox*[length];
            for (int j=0; j<length; ++j) {
                guessesMulti[n][i][j] = new LetterBox(parent);
            }
        }
    }
}

QString MultiWordleRound::getAllAnswers() const {
    QString concat = "";
    for (int n=0; n<numWords; ++n) {
        concat += ansMulti[n];
        if (n != numWords-1) concat += ", ";
    }
    return concat.toUpper();
}

/**
 * TODO: BONUS TASK 2
 *
 * Implement based on WordleRound::registerKey().
 * Note that we don't update QGridLayouts where the answers have been guessed.
 */
void MultiWordleRound::registerKey(const QChar& key) {
    if (curLetter == length) return;        // Already typed all letters for this guess
    if (curGuess == numGuesses) return;     // Out of guesses
    for (int i = 0; i < numWords; i++) {
        if (!correctGuessesMulti[i]) {
            guessesMulti[i][curGuess][curLetter]->setLetter(key);
        }
    }
    curLetter++;
}

/**
 * TODO: BONUS TASK 2
 *
 * Implement based on WordleRound::registerDelKey().
 * Note that we don't update QGridLayouts where the answers have been guessed.
 */
void MultiWordleRound::registerDelKey() {
    if (curLetter == 0) return;             // Nothing to delete
    if (curGuess == numGuesses) return;     // Out of guesses
    curLetter--;
    for (int i = 0; i < numWords; i++) {
        if (!correctGuessesMulti[i]) {
            guessesMulti[i][curGuess][curLetter]->setLetter(' ');
        }
    }
}

/**
 * TODO: BONUS TASK 2
 *
 * Implement based on WordleRound::revertGuess().
 * Note that we don't update QGridLayouts where the answers have been guessed.
 */
void MultiWordleRound::revertGuess() {
    for (int i = 0; i < numWords; i++) {
        if (!correctGuessesMulti[i]) {
            for (int j = 0; j < length; j++) {
                guessesMulti[i][curGuess][j]->setLetter(' ');
            }
        }
    }
    curLetter = 0;
}

// To let this .cpp file know these functions are defined in another source file
QColor* analyzeGuess(const QString& guess, const QString& answer);
QString getCurrentGuess(LetterBox** guess, const int len);
bool validGuess(const QString& guess, const Dictionary& dict);

/**
 * TODO: BONUS TASK 2
 *
 * Implement based on WordleRound::registerEnterKey().
 * Note that we don't update QGridLayouts where the answers have been guessed.
 * You can ignore hard mode and solver related code for this task, as we don't have those options for this mode.
 * At the end, call endGuessAttempt() normally, with parameter as whether *all* words have been guessed correctly.
 *
 * Hint: use and maintain the correctGuessesMulti[] array.
 */
void MultiWordleRound::registerEnterKey() {
    if (curLetter != length) return;
    if (curGuess == numGuesses) return;

    for (int i = 0; i < numWords; i++) {
        if (!correctGuessesMulti[i]) {
            QString guess = getCurrentGuess(guessesMulti[i][curGuess], length);

            if (!validGuess(guess, dict)) {
                revertGuess();
                emit invalidWord();
                return;
            }

            correctGuessesMulti[i] = true;
            QColor* colors = analyzeGuess(guess, ansMulti[i]);
            for (int j = 0; j < length; j++) {
                correctGuessesMulti[i] &= (colors[j] == GREEN);
                guessesMulti[i][curGuess][j]->setColor(colors[j]);
                emit updateKeyboardColor(guessesMulti[i][curGuess][j]->getLetter(), colors[j]);
            }
            delete [] colors;
        }
    }

    bool allCorrectGuess = true;
    for (int i = 0; i < numWords; i++) {
        if (!correctGuessesMulti[i]) {
            allCorrectGuess = false;
        }
    }
    WordleRound::endGuessAttempt(allCorrectGuess);
}

void MultiWordleRound::resetRound() {
    for (int n=0; n<numWords; ++n) {
        ansMulti[n] = dict.getRandomAnswer();
        correctGuessesMulti[n] = false;
        for (int i=0; i<numGuesses; ++i) {
            for (int j=0; j<length; ++j) {
                guessesMulti[n][i][j]->reset();
            }
        }
    }
    emit resetKeyboardColor();
    curGuess = 0;
    curLetter = 0;
    numTries = 0;
}
