#ifndef REGULARROUNDWINDOW_H
#define REGULARROUNDWINDOW_H

#include "roundwindow.h"

/**
 * @brief Handles UI for the Regular Wordle mode.
 * Inherits the RoundWindow class, although largely unchanged.
 */
class RegularRoundWindow : public RoundWindow
{

public:
    RegularRoundWindow(QWidget *parent, int wordLength, bool hardMode);
};

#endif // REGULARROUNDWINDOW_H
