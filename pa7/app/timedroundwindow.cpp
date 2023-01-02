#include "timedroundwindow.h"
#include "ui_roundwindow.h"
#include "timedwordleround.h"

// Helper macro to convert WordleRound pointer to TimedWordleRound pointer,
// so that TimedWordleRound exclusive functions can be called
#define twr dynamic_cast<TimedWordleRound*>(wr)


// IMPORTANT: Use these function to convert time and score to QString
// so that the text format is consistent for testing
QString timeToStr(const QTime& time) { return time.toString("mm:ss"); }
QString scoreToStr(const int score) { return "Score: " + QString::number(score); }


TimedRoundWindow::TimedRoundWindow(QWidget *parent, int wordLength, bool hardMode, int minutes):
    RoundWindow(parent), minutes(minutes)
{
    title = "TimedWordle";
    ui->label->setText(title);

    /**
     * TODO: BONUS TASK 3
     *
     * First, implement the constructor based on RegularRoundWindow constrcutor.
     * Then, initialize the extra data members and widgets:
     *
     * timeLeft is a QTime object holding the amount of time left.
     *
     * timerLayout is a QGridLayout, to be inserted into ui->centralwidget->layout() by calling insertLayout().
     * Hint: convert to QVBoxLayout* by using dynamic_cast<QVBoxLayout*>(ui->centralwidget->layout())
     *
     * oneSecTimer points to a QTimer object.
     * Connect its timeout() signal to TimedRoundWindow updateTimer() slot.
     * Start the timer to be triggered every 1000ms.
     *
     * Initialize the 3 QLineEdit and 1 QPushButton objects, add them into timerLayout in a 2x2 grid.
     * For all QLineEdits: setEnabled(false) and setAlignment(Qt::AlignCenter);
     * For all widgets: setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     * Set timerLineEdit and scoreLineEdit's texts to the initial state.
     * Set skipWordPushButton's text to "Skip word" and connect button's clicked() to skipCurrentWord().
     *
     * Note: use the functions defined above to convert time and score to QStrings.
     */

    wr = new TimedWordleRound(this, wordLength, hardMode);
    kb->setCurrentRound(twr);
    generateLetterBoxes(ui->gridLayoutBox, twr->getGuesses(), twr->getNumGuesses(), twr->getLength());
    connect(twr, &WordleRound::updateKeyboardColor, kb, &Keyboard::updateKeyColor);
    connect(twr, &WordleRound::resetKeyboardColor, kb, &Keyboard::resetKeyColor);

    timeLeft.setHMS(0, minutes, 0);

    timerLayout = new QGridLayout;
    dynamic_cast<QVBoxLayout*>(ui->centralwidget->layout())->insertLayout(0, timerLayout);

    oneSecTimer = new QTimer(this);
    connect(oneSecTimer, &QTimer::timeout, this, &TimedRoundWindow::updateTimer);
    oneSecTimer->start(1000);


    skipWordPushButton = new QPushButton;
    timerLineEdit = new QLineEdit;
    messageLineEdit = new QLineEdit;
    scoreLineEdit = new QLineEdit;

    timerLineEdit->setEnabled(false);
    messageLineEdit->setEnabled(false);
    scoreLineEdit->setEnabled(false);

    timerLineEdit->setAlignment(Qt::AlignCenter);
    messageLineEdit->setAlignment(Qt::AlignCenter);
    scoreLineEdit->setAlignment(Qt::AlignCenter);

    skipWordPushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    timerLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scoreLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    timerLayout->addWidget(timerLineEdit, 0, 0, Qt::AlignCenter);
    timerLayout->addWidget(skipWordPushButton, 0, 1, Qt::AlignCenter);
    timerLayout->addWidget(scoreLineEdit, 1, 0, Qt::AlignCenter);
    timerLayout->addWidget(messageLineEdit, 1, 1, Qt::AlignCenter);

    timerLineEdit->setText(timeToStr(timeLeft));
    scoreLineEdit->setText(scoreToStr(0));

    skipWordPushButton->setText("Skip Word");
    connect(skipWordPushButton, &QPushButton::clicked, twr, &TimedWordleRound::skipCurrentWord);


}

TimedRoundWindow::~TimedRoundWindow() {
    delete timerLayout;
    delete oneSecTimer;
    delete skipWordPushButton;
    delete timerLineEdit;
    delete messageLineEdit;
    delete scoreLineEdit;
}

/**
 * TODO: BONUS TASK 3
 *
 * If timeLeft goes below 0, call popupRoundOver().
 * Else, subtract 1 second from timeLeft and update the timerLineEdit.
 */
void TimedRoundWindow::updateTimer() {
    if (timeLeft.secsTo(QTime::currentTime()) < 0) {
        popupRoundOver();
    } else {
        timeLeft = timeLeft.addSecs(-1);
        timerLineEdit->setText(timeToStr(timeLeft));
    }
}

void TimedRoundWindow::clearMessage() {
    messageLineEdit->setText("");
}

void TimedRoundWindow::msgInvalidWord() {
    messageLineEdit->setText("Word not in dictionary.");
    QTimer::singleShot(1000, this, &TimedRoundWindow::clearMessage);
}

void TimedRoundWindow::msgInvalidHardWord() {
    messageLineEdit->setText("Did not use correct letters.");
    QTimer::singleShot(1000, this, &TimedRoundWindow::clearMessage);
}

void TimedRoundWindow::msgRoundWin() {
    messageLineEdit->setText("Correct! +1 point.");
    QTimer::singleShot(1000, this, &TimedRoundWindow::clearMessage);
}

void TimedRoundWindow::msgRoundLose() {
    messageLineEdit->setText("The answer was: " + wr->getAnswer().toUpper());
    QTimer::singleShot(1000, this, &TimedRoundWindow::clearMessage);
}

void TimedRoundWindow::scoreUpdate() {
    scoreLineEdit->setText(scoreToStr(twr->getScore()));
}

void TimedRoundWindow::popupConfirmGiveUp() {
    QMessageBox::StandardButton choice =
            QMessageBox::question(this, "Give up?", "Would you like to forfeit this round?");
    if (choice == QMessageBox::Yes) {
        popupRoundOver();
    }
}

void TimedRoundWindow::popupConfirmReset() {
    QMessageBox::StandardButton choice =
            QMessageBox::question(this, "Reset?", "Would you like restart the round? A new answer will be generated.");
    if (choice == QMessageBox::Yes) {
        twr->resetTimedRound();

        timeLeft = QTime(0, minutes, 0);
        oneSecTimer->start(1000);
        timerLineEdit->setText(timeToStr(timeLeft));

        ui->label->setText(title);
        ui->actionGive_Up->setEnabled(true);
        ui->actionCheat->setEnabled(true);
        ui->actionHint->setEnabled(true);
    }
}

void TimedRoundWindow::popupRoundOver() {
    QMessageBox::information(this, "Game over!",
        "You guessed " + QString::number(twr->getScore()) + " words in " + QString::number(minutes) + " minutes!");
    ui->actionGive_Up->setEnabled(false);
    ui->actionCheat->setEnabled(false);
    ui->actionHint->setEnabled(false);
    ui->label->setText("Game over!");

    oneSecTimer->stop();
    twr->endTimedRound();
}
