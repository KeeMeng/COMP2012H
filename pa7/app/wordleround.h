#ifndef WORDLEROUND_H
#define WORDLEROUND_H

#include "letterbox.h"
#include "dictionary.h"
#include "helper.h"
#include "solver.h"

#include <QWidget>
#include <QString>

/**
 * @brief Base class for processing a game of Wordle
 */
class WordleRound: public QObject
{
    Q_OBJECT

    friend class TestTask2;
    friend class TestTask3;
    friend class TestTask5;
    friend class TestBonusTask1;
    friend class TestBonusTask3;

private:
    // This is only used during testing
    void setAnswer(const QString& ans) { answer = ans; }

protected:
    int length;         // Word length for this round
    int numGuesses;     // Number of guesses available, calculated via calculateNumGuesses()
    QString answer;     // Answer for this round

    // Hard mode related data members
    bool hardMode;                              // Whether hard mode is enabled
    bool correctLetters[NUM_LETTERS] {false};   // Which letters are correct and need to be used for subsequent guesses

    int curGuess {0};   // Current guess number (row of LetterBox to be edited)
    int curLetter {0};  // Current letter to be edited (column of LetterBox to be edited)
    int numTries {0};   // Number of tries to guess the right word

    LetterBox*** guesses {nullptr}; // 2D array of pointers to LetterBox objects initialized in initGuesses()
    Dictionary dict;                // Dictionary object initialized with 'length'
    Solver solver;                  // Solver object initialized with dict.getAllAnswers()

    /**
     * @brief Get number of guesses for the default mode
     * @param len: length of word
     * @return Number of guesses
     */
    virtual int calculateNumGuesses(int len);

    /**
     * @brief Initializes guesses, a 2D array of pointers to LetterBox objects
     * @param parent: Pointer to RoundWindow
     */
    void initGuesses(QWidget *parent);

    /**
     * @brief Revert all LetterBoxes to default
     */
    virtual void revertGuess();

    /**
     * @brief Called at the end of registerEnterKey().
     * If guess is correct, emit roundWin().
     * Else, add 1 to curGuess. If it equals numGuesses, emit roundLose().
     * Also set curLetter to 0.
     * @param correctGuess: whether current guess is correct
     */
    virtual void endGuessAttempt(bool correctGuess);

public:
    WordleRound(QWidget *parent);   // "default" constructor that doesn't initialize data members
    WordleRound(QWidget *parent, int len, bool hardMode = false);
    virtual ~WordleRound();

    int getLength() const { return length; }
    int getNumGuesses() const { return numGuesses; }
    QString getAnswer() const { return answer; }
    int getNumTries() const { return numTries; }
    LetterBox*** getGuesses() const { return guesses; }

    /**
     * @brief Returns true if the player has not made any guesses
     * @return bool: true if curGuess = 0
     */
    bool isFirstGuess() const { return curGuess == 0; }

    /**
     * @brief Register that a letter key is pressed.
     * If last letter has been entered or round ended, ignore.
     * Otherwise, update the current LetterBox and curLetter.
     * @param key: letter pressed (lowercase)
     */
    virtual void registerKey(const QChar& key);

    /**
     * @brief Register that the Delete key is pressed.
     * If no letters have been entered or round ended, ignore.
     * Otherwise, update the current LetterBox with ' ' and curLetter.
     */
    virtual void registerDelKey();

    /**
     * @brief Register that the Enter key is pressed.
     * If not all letters have been entered or round ended, ignore.
     * Otherwise, check if guess is valid. If not, emit corresponding signal.
     * If guess is valid, calculate and emit signals to color the boxes.
     * Finally, call endGuessAttempt() to check winning condition and update data members.
     */
    virtual void registerEnterKey();

    /**
     * @brief End the round and emit corresponding signal
     * @param win: whether answer was guessed correctly
     */
    virtual void endRound(bool win);

    /**
     * @brief Reset the round to initial state
     */
    virtual void resetRound();

    /**
     * @brief Get hint from solver
     * @return "long words" if length is too high;
     * "too many words" if there are too many possible answer;
     * hint given by solver otherwise.
     */
    QString getHint();

signals:
    /**
     * @brief Emitted if word is not in dictionary
     */
    void invalidWord();

    /**
     * @brief Emitted if guess did not use correct letters in hard mode
     */
    void invalidHardWord();

    /**
     * @brief Emitted if round ended with a win
     */
    void roundWin();

    /**
     * @brief Emitted if round ended with a loss
     */
    void roundLose();

    /**
     * @brief Emitted to tell Keyboard to update key to color.
     * Keyboard will handle Wordle coloring convention.
     * @param key: letter to be updated (lowercase)
     * @param color: new color
     */
    void updateKeyboardColor(const QChar& key, const QColor& color);

    /**
     * @brief Emitted to tell Keyboard to reset all key colors.
     */
    void resetKeyboardColor();
};

#endif // WORDLEROUND_H
