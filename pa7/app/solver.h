#ifndef SOLVER_H
#define SOLVER_H

#include <QSet>
#include <QColor>

/**
 * @brief Bonus Task 4: Gives hints to the player.
 *
 * Maintains a set of possible answers to the current round.
 * Calculates the "best" next guess by finding the possible answer
 * that reduces the most amount of entropy.
 *
 * To initialize, pass all possible answers to the constructor (using dict.getAllAnswers())
 */
class Solver
{

    friend class TestBonusTask4;

private:
    // If enabled is false, solver will not update or give hint
    bool enabled {true};
    QSet<QString> allWords {};
    QSet<QString> possibleAnswers {};

public:
    Solver() = default;
    Solver(const QSet<QString>& allWords);

    bool isEnabled() const { return enabled; }
    void setEnabled(bool enable) { enabled = enable; }

    /**
     * @brief Reset to original state (all answers are possible)
     * @param allWords: all possible answers (using dict.getAllAnswers())
     */
    void reset(const QSet<QString>& allWords);

    /**
     * @brief Give hint based on remaining possible answers
     * @return QString: "best" next guess
     */
    QString hint();

    /**
     * @brief Update the set of possible answers based on result of current guess.
     * Remove all answers that would not result in the same coloring sequence.
     * @param guess: current guess
     * @param colors: QColor sequence associated with this guess
     */
    void updateAnswers(const QString& guess, QColor* colors);

    /**
     * @brief Get the remaining number of possible answers
     * @return int: remaining number of possible answers
     */
    int getRemainingNumAnswers() const { return possibleAnswers.count(); }
};

#endif // SOLVER_H
