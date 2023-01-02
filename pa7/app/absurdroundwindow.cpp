#include "absurdroundwindow.h"
#include "ui_roundwindow.h"
#include "absurdwordleround.h"

AbsurdRoundWindow::AbsurdRoundWindow(QWidget *parent, const int wordLength):
    RoundWindow(parent)
{
    title = "AbsurdWordle";
    ui->label->setText(title);

    /**
     * TODO: BONUS TASK 1
     *
     * Implement the constructor based on RegularRoundWindow constructor.
     * No need to connect to keyboard color update slots.
     */

    wr = new AbsurdWordleRound(this, wordLength);
    kb->setCurrentRound(wr);
    generateLetterBoxes(ui->gridLayoutBox, wr->getGuesses(), wr->getNumGuesses(), wr->getLength());
}

void AbsurdRoundWindow::popupRoundLose() {
    QMessageBox::information(this, "You lost!",
        "The current correct answer is " + wr->getAnswer().toUpper() + ".");
    ui->label->setText("You lost! (Answer: " + wr->getAnswer().toUpper() + ")");
    ui->actionGive_Up->setEnabled(false);
    ui->actionCheat->setEnabled(false);
    ui->actionHint->setEnabled(false);
}

void AbsurdRoundWindow::popupCheat() {
    QMessageBox::information(this, "Cheat", "The current correct answer is " + wr->getAnswer().toUpper() + ".");
}

void AbsurdRoundWindow::popupHint() {
    QMessageBox::information(this, "Hint unavailable", "Unable to give hint for this mode.");
}
