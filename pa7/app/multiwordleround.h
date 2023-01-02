#ifndef MULTIWORDLEROUND_H
#define MULTIWORDLEROUND_H

#include "wordleround.h"

/**
 * @brief Handles UI for the Multi Wordle mode.
 * Inherits the RoundWindow class.
 *
 * Replaces answer and guesses with corresponding arrays
 * (the original data members still exist but will be unused).
 *
 * Reimplements calculateNumGuesses() to change number of guesses.
 * Replaces initGuesses() with initMultipleGuesses() to initialize the 3D array of LetterBox* instead.
 * Reimplements revertGuess(), registerKey(), registerDelKey(), registerEnterKey(), resetRound()
 * to handle the 3D array of LetterBox*.
 *
 * Solver (bonus task 4) is ignored in this mode, no need to initialize.
 */
class MultiWordleRound : public WordleRound
{

    friend class TestBonusTask2;

private:
    // This is only used during testing
    void setAnswerMulti(const QString ans[]) { for (int i=0; i<numWords; ++i) ansMulti[i] = ans[i]; }

private:
    QString *ansMulti;
    int numWords;

    bool *correctGuessesMulti;
    LetterBox**** guessesMulti {nullptr};

    /**
     * @brief Get number of guesses for the Multi Wordle mode
     * @param len: length of word
     * @return Number of guesses. For this mode, 1 more for each extra word
     */
    virtual int calculateNumGuesses(int len) override;

    /**
     * @brief Initializes guessesMulti, a 3D array of pointers to LetterBox objects
     * @param parent: Pointer to RoundWindow
     */
    void initMultiGuesses(QWidget *parent);

    /**
     * @brief Revert all LetterBoxes to default
     */
    virtual void revertGuess() override;

public:
    MultiWordleRound(QWidget *parent, int len, int numWords);
    virtual ~MultiWordleRound();

    /**
     * @brief Get one of the current answers
     * @param index: Index of answer to get (from left to right)
     * @return QString: answer at index (lowercase)
     */
    QString getAnswerMulti(int index) const { return ansMulti[index]; }

    /**
     * @brief Get all answers separated by comma for printing purpose
     * @return QString: all answers separated by comma (lowercase)
     */
    QString getAllAnswers() const;

    /**
     * @brief Get one of the 2D arrays of LetterBox*
     * @param index: Index of 2D array of LetterBox*
     * @return LetterBox*** (equivalent to regular mode's "guesses")
     */
    LetterBox*** getGuessesMulti(int index) const { return guessesMulti[index]; }

    virtual void registerKey(const QChar& key) override;
    virtual void registerDelKey() override;
    virtual void registerEnterKey() override;

    virtual void resetRound() override;
};

#endif // MULTIWORDLEROUND_H
