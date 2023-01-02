#ifndef REGULARWORDLEROUND_H
#define REGULARWORDLEROUND_H

#include "wordleround.h"

/**
 * @brief Handles the logic for the Absurd Wordle mode.
 * Inherits the WordleRound class, although largely unchanged.
 */
class RegularWordleRound : public WordleRound
{

public:
    RegularWordleRound(QWidget *parent, int len, bool hardMode = false);
};

#endif // REGULARWORDLEROUND_H
