#ifndef ABSURDROUNDWINDOW_H
#define ABSURDROUNDWINDOW_H

#include "roundwindow.h"

/**
 * @brief Handles UI for the Absurd Wordle mode.
 * Inherits the RoundWindow class.
 *
 * Reimplements some popup() functions to modify the texts.
 */
class AbsurdRoundWindow : public RoundWindow
{

public:
    AbsurdRoundWindow(QWidget *parent = nullptr, int wordLength = 5);

public slots:
    virtual void popupRoundLose() override;
    virtual void popupCheat() override;
    virtual void popupHint() override;
};

#endif // ABSURDROUNDWINDOW_H
