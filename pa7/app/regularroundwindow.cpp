#include "regularroundwindow.h"
#include "ui_roundwindow.h"
#include "regularwordleround.h"

RegularRoundWindow::RegularRoundWindow(QWidget *parent, const int wordLength, const bool hardMode):
    RoundWindow(parent)
{
    wr = new RegularWordleRound(this, wordLength, hardMode);
    kb->setCurrentRound(wr);
    generateLetterBoxes(ui->gridLayoutBox, wr->getGuesses(), wr->getNumGuesses(), wr->getLength());

    connect(wr, &WordleRound::updateKeyboardColor, kb, &Keyboard::updateKeyColor);
    connect(wr, &WordleRound::resetKeyboardColor, kb, &Keyboard::resetKeyColor);
}
