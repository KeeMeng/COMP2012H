#include "wordleround.h"
#include "roundwindow.h"

// A rough formula to give more guesses to very long and very short words
int WordleRound::calculateNumGuesses(const int len) {
    return (26 / len) + (len / 3) + (len / 7);
}

void WordleRound::initGuesses(QWidget *parent) {
    numGuesses = this->calculateNumGuesses(length);
    guesses = new LetterBox**[numGuesses];
    for (int i=0; i<numGuesses; ++i) {
        guesses[i] = new LetterBox*[length];
        for (int j=0; j<length; ++j) {
            guesses[i][j] = new LetterBox(parent);
        }
    }
}

WordleRound::WordleRound(QWidget *parent) {
    connect(this, &WordleRound::invalidWord, static_cast<RoundWindow*>(parent), &RoundWindow::popupInvalidWord);
    connect(this, &WordleRound::invalidHardWord, static_cast<RoundWindow*>(parent), &RoundWindow::popupInvalidHardWord);
    connect(this, &WordleRound::roundWin, static_cast<RoundWindow*>(parent), &RoundWindow::popupRoundWin);
    connect(this, &WordleRound::roundLose, static_cast<RoundWindow*>(parent), &RoundWindow::popupRoundLose);
}

WordleRound::WordleRound(QWidget *parent, const int len, const bool hardMode):
    WordleRound(parent)
{
    this->length = len;
    this->hardMode = hardMode;
    dict = Dictionary(length);
    solver = Solver(dict.getAllAnswers());
    answer = dict.getRandomAnswer();
}

WordleRound::~WordleRound() {
    if (guesses) {
        for (int i=0; i<numGuesses; ++i) {
            for (int j=0; j<length; ++j) {
                SAFE_DELETE(guesses[i][j]);
            }
            delete [] guesses[i];
        }
        delete [] guesses;
    }
}

/**
 * TODO: TASK 1
 *
 * @brief Calculates the color sequence for given guess and answer
 * @param guess: Player's guess
 * @param answer: The answer to be compared with
 * @return QColor array
 *
 * First, create a QColor array of result and a bool array of assigned letters.
 * Perform a 2 pass scheme:
 * - First pass: For each letter in 'guess', if it equals the corresponding letter in 'answer':
 *      + Set result to GREEN,
 *      + Set assigned to true (this position in 'answer' has been assigned to a letter in 'guess'),
 *   Else, set result to GREY and assigned to false
 * - Second pass: For each remaining letter in 'guess' not colored GREEN:
 *   Loop over letters in 'answer'. If the letters are the same and the 'answer' letter is not assigned:
 *      + Set result to YELLOW,
 *      + Set assigned to true (this position in 'answer' has been assigned to a letter in 'guess')
 *      + Move to next letter in 'guess'
 * Return QColor array result.
 *
 * Note: result is a dynamic array since length is not a constant, so delete [] must be called after result is used!
 */
QColor* analyzeGuess(const QString& guess, const QString& answer) {
    int word_length = guess.length();
    QColor* colors = new QColor[word_length];
    bool* assigned = new bool[word_length];

    // green
    for (int i = 0; i < word_length; i++) {
        if (guess.at(i) == answer.at(i)) {
            assigned[i] = true;
            colors[i] = GREEN;
        } else {
            assigned[i] = false;
            colors[i] = GREY;
        }
    }
    // yellow
    for (int i = 0; i < word_length; i++) {
        if (guess.at(i) != answer.at(i)) {
            for (int j = 0; j < word_length; j++) {
                if (guess.at(i) == answer.at(j) && !assigned[j]) {
                    assigned[j] = true;
                    colors[i] = YELLOW;
                    break;
                }
            }
        }
    }
    delete [] assigned;
    return colors;
}

void WordleRound::registerKey(const QChar& key) {
    if (curLetter == length) return;        // Already typed all letters for this guess
    if (curGuess == numGuesses) return;     // Out of guesses
    guesses[curGuess][curLetter]->setLetter(key);
    ++curLetter;
}

void WordleRound::registerDelKey() {
    if (curLetter == 0) return;             // Nothing to delete
    if (curGuess == numGuesses) return;     // Out of guesses
    --curLetter;
    guesses[curGuess][curLetter]->setLetter(' ');
}

QString getCurrentGuess(LetterBox** guess, const int len) {
    QChar* guessChar = new QChar[len + 1];
    for (int i=0; i<len; ++i) {
        guessChar[i] = guess[i]->getLetter();
    }
    guessChar[len] = '\0';
    QString guessStr {guessChar};
    delete [] guessChar;
    return guessStr;
}

void WordleRound::revertGuess() {
    for (int i=0; i<length; ++i) {
        guesses[curGuess][i]->setLetter(' ');
    }
    curLetter = 0;
}

/**
 * @brief Returns true if 'guess' appears in dictionary's word list
 * @param guess: Player's guess
 * @param dict: Dictionary object
 * @return true if guess appears in dictionary.words
 */
bool validGuess(const QString& guess, const Dictionary& dict) {
    return dict.isValidWord(guess);
}

/**
 * TODO: TASK 5
 *
 * @brief Returns true if 'guess' uses all correct letters
 * @param guess: Player's guess
 * @param correctLetters: bool array of size NUM_LETTERS corresponding to whether letter is correct
 * @return true if guess contains all letters where correctLetters[letter] is true
 *
 * Hint: you can use QString.contains() to check if string contains a letter.
 */
bool validHardModeGuess(const QString& guess, const bool correctLetters[]) {
    for (int i = 0; i < 26; i++) {
        if (correctLetters[i]) {
            if (!guess.contains((QChar)(i + 'a'))) {
                return false;
            }
        }
    }

    return true;
}


void WordleRound::registerEnterKey() {
    if (curLetter != length) return;        // Have not typed all letters
    if (curGuess == numGuesses) return;     // Out of guesses

    // Convert current guess to QString
    QString guess = getCurrentGuess(guesses[curGuess], length);

    // Check if guess is in dictionary
    if (!validGuess(guess, dict)) {
        revertGuess();
        emit invalidWord();
        return;
    }

    /**
     * TODO: TASK 5
     *
     * If hardMode is enabled, validate that correct letters are used.
     * If not, revert guess and emit signal, then return early.
     */

    if (hardMode) {
        if (!validHardModeGuess(guess, correctLetters)) {
            revertGuess();
            emit invalidHardWord();
            return;
        }
    }



    // Color the boxes according to result
    bool correctGuess = true;
    QColor* colors = analyzeGuess(guess, answer);
    for (int i=0; i<length; ++i) {
        correctGuess &= (colors[i] == GREEN);
        guesses[curGuess][i]->setColor(colors[i]);
        emit updateKeyboardColor(guesses[curGuess][i]->getLetter(), colors[i]);

        /**
         * TODO: TASK 5
         *
         * If a letter is not GREY, it must be used in next guesses
         * set correctLetters[index] to true, where index = 0 if letter = 'a', etc.
         */

        for (int i = 0; i < length; i++) {
            if (colors[i] == YELLOW || colors[i] == GREEN) {
                correctLetters[guess[i].toLatin1() - 'a'] = true;
            }
        }
    }

    /**
     * TODO: BONUS TASK 4
     *
     * Update the set of remaining possible answers
     */

    solver.updateAnswers(guess, colors);


    delete [] colors;

    // Finish guess attempt
    endGuessAttempt(correctGuess);
}

void WordleRound::endGuessAttempt(const bool correctGuess) {
    if (correctGuess) {
        endRound(true);
    }
    else {
        ++curGuess;
        if (curGuess == numGuesses) {
            endRound(false);
        }
    }
    curLetter = 0;
}

void WordleRound::endRound(const bool win) {
    numTries = curGuess + 1;
    if (win) {
        emit roundWin();
    }
    else {
        emit roundLose();
    }
    curGuess = numGuesses;
}

void WordleRound::resetRound() {
    answer = dict.getRandomAnswer();
    solver.reset(dict.getAllAnswers());
    for (int i=0; i<numGuesses; ++i) {
        for (int j=0; j<length; ++j) {
            guesses[i][j]->reset();
        }
    }
    emit resetKeyboardColor();
    curGuess = 0;
    curLetter = 0;
    numTries = 0;
    for (int i=0; i<NUM_LETTERS; ++i) {
        correctLetters[i] = false;
    }
}

QString WordleRound::getHint() {
    // Lower this number if your computer cannot allocate enough memory
    if (length > 10) return "long words";
    if (solver.getRemainingNumAnswers() * length > 5000) return "too many words";
    return solver.hint();
}
