#ifndef MULTIROUNDWINDOW_H
#define MULTIROUNDWINDOW_H

#include "roundwindow.h"

/**
 * @brief Handles UI for the Multi Wordle mode.
 * Inherits the RoundWindow class.
 *
 * Reimplements some popup() functions to modify the texts.
 * Adds extra QGridLayout for the additional words.
 */
class MultiRoundWindow : public RoundWindow
{

private:
    int numWords;
    QGridLayout **extraGridLayoutBox {nullptr};

public:
    MultiRoundWindow(QWidget *parent, int wordLength, int numWords);
    virtual ~MultiRoundWindow();

public slots:
    virtual void popupRoundWin() override;
    virtual void popupRoundLose() override;
    virtual void popupCheat() override;
    virtual void popupHint() override;
};

#endif // MULTIROUNDWINDOW_H
