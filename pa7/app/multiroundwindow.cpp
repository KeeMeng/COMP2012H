#include "multiroundwindow.h"
#include "ui_roundwindow.h"
#include "multiwordleround.h"

// Helper macro to convert WordleRound pointer to MultiWordleRound pointer,
// so that MultiWordleRound exclusive functions can be called
#define mwr dynamic_cast<MultiWordleRound*>(wr)

MultiRoundWindow::MultiRoundWindow(QWidget *parent, const int wordLength, const int numWords):
    RoundWindow(parent),
    numWords(numWords)
{
    title = "MultiWordle";
    ui->label->setText(title);

    /**
     * TODO: BONUS TASK 2
     *
     * Implement the constructor based on RegularRoundWindow constructor.
     *
     * Initialize extraGridLayoutBox as a QGridLayout array of size numWords - 1,
     * then insert each layout into the UI by calling QHBoxLayout::insertLayout()
     *
     * Hint: use QHBoxLayout::insertSpacing() to add spacing between adjacent QGridLayouts. 50px should be fine for size.
     *
     * Finally, call generateLetterBoxes() for each QGridLayout and its corresponding 2D LetterBox array.
     */

    wr = new MultiWordleRound(this, wordLength, numWords);
    kb->setCurrentRound(mwr);

    extraGridLayoutBox = new QGridLayout*[numWords - 1];

    for (int i = 0; i < numWords - 1; i++) {
        QGridLayout* grid = new QGridLayout;
        extraGridLayoutBox[i] = grid;
        ui->horizontalLayoutGuesses->insertSpacing(2 * i + 2, 50);
        ui->horizontalLayoutGuesses->insertLayout(2 * i + 3, grid);
    }

    generateLetterBoxes(ui->gridLayoutBox, mwr->getGuessesMulti(0), mwr->getNumGuesses(), mwr->getLength());
    for (int i = 0; i < numWords - 1; i++) {
        generateLetterBoxes(extraGridLayoutBox[i], mwr->getGuessesMulti(i + 1), mwr->getNumGuesses(), mwr->getLength());
    }

    connect(mwr, &MultiWordleRound::updateKeyboardColor, kb, &Keyboard::updateKeyColor);
    connect(mwr, &MultiWordleRound::resetKeyboardColor, kb, &Keyboard::resetKeyColor);
}

MultiRoundWindow::~MultiRoundWindow() {
    for (int n=1; n<numWords; ++n) {
        delete extraGridLayoutBox[n-1];
    }
    delete [] extraGridLayoutBox;
}

void MultiRoundWindow::popupRoundWin() {
    QMessageBox::information(this, "You won!",
        "Congratulations! You guessed the right words in " + QString::number(wr->getNumTries()) + " tries!");
    ui->label->setText("You won!");
    ui->actionGive_Up->setEnabled(false);
    ui->actionCheat->setEnabled(false);
    ui->actionHint->setEnabled(false);
}

void MultiRoundWindow::popupRoundLose() {
    QMessageBox::information(this, "You lost!",
        "The correct answers are: " + mwr->getAllAnswers() + ".");
    ui->label->setText("You lost! (Answers: " + mwr->getAllAnswers() + ")");
    ui->actionGive_Up->setEnabled(false);
    ui->actionCheat->setEnabled(false);
    ui->actionHint->setEnabled(false);
}

void MultiRoundWindow::popupCheat() {
    QMessageBox::information(this, "Cheat", "The correct answers are: " + mwr->getAllAnswers() + ".");
}

void MultiRoundWindow::popupHint() {
    QMessageBox::information(this, "Hint unavailable", "Unable to give hint for this mode.");
}
