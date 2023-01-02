#ifndef TIMEDWORDLEROUND_H
#define TIMEDWORDLEROUND_H

#include "wordleround.h"

/**
 * @brief Handles the logic for the Timed Wordle mode.
 * Inherits the WordleRound class.
 *
 * Signals need to be re-routed to TimedRoundWindow slots in the constructor.
 *
 * Reimplements endRound() to continue playing after guessing/failed guess.
 */
class TimedWordleRound : public WordleRound
{
    Q_OBJECT

private:
    int score {0};

public:
    TimedWordleRound(QWidget *parent, int len, bool hardMode = false);

    void setScore(int newScore) { score = newScore; }
    int getScore() const { return score; }

    /**
     * @brief Same as base class endRound() but reset round immediately, and add 1 to score if guess is correct
     * @param win: whether guess is correct
     */
    virtual void endRound(bool win) override;

    /**
     * @brief Reset to initial state (score = 0)
     */
    void resetTimedRound();

public slots:
    /**
     * @brief Disable user input as game is over
     */
    void endTimedRound();

    /**
     * @brief Skip to next word (treat current word as loss)
     */
    void skipCurrentWord();

signals:
    /**
     * @brief Emitted when score changes
     */
    void scoreUpdated();
};

#endif // TIMEDWORDLEROUND_H
