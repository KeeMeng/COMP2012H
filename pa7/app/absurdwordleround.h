#ifndef ABSURDWORDLEROUND_H
#define ABSURDWORDLEROUND_H

#include "wordleround.h"

/**
 * @brief Handles the logic for the Absurd Wordle mode.
 * Inherits the WordleRound class.
 *
 * Reimplements calculateNumGuesses() to change number of guesses.
 * Reimplements endGuessAttempt() to alter answer after each wrong guess.
 *
 * Bonus Task 4: Solver is ignored in this mode, disable in the constructor.
 */
class AbsurdWordleRound : public WordleRound
{

private:
    /**
     * @brief Get number of guesses for the Absurd Wordle mode
     * @param len: length of word
     * @return Number of guesses. For this mode, 1 more than regular mode
     */
    virtual int calculateNumGuesses(int len) override;

    /**
     * @brief Extends base class endGuessAttempt() with altering the answer
     * @param correctGuess: whether current guess is correct
     */
    virtual void endGuessAttempt(bool correctGuess) override;

public:
    AbsurdWordleRound(QWidget *parent, int len);

};

#endif // ABSURDWORDLEROUND_H
