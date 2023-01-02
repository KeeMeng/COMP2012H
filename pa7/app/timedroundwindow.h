#ifndef TIMEDROUNDWINDOW_H
#define TIMEDROUNDWINDOW_H

#include "roundwindow.h"

#include <QTime>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>

/**
 * @brief Handles UI for the Timed Wordle mode.
 * Inherits the RoundWindow class.
 *
 * Adds several widgets to the default RoundWindow UI, configured in the constructor.
 * Replaces some popup slots with writing text to messageLineEdit.
 * Reimplements popupConfirmGiveUp(), popupConfirmReset(),
 * adds popupRoundOver() to handle ending the timed round
 */
class TimedRoundWindow : public RoundWindow
{

    friend class TestBonusTask3;

private:
    int minutes;
    QTime timeLeft;

    QGridLayout *timerLayout {nullptr};           // Layout holding the widgets below
    QTimer *oneSecTimer {nullptr};                // Timer that triggers every second
    QPushButton *skipWordPushButton {nullptr};    // Button to skip the current word
    QLineEdit *timerLineEdit {nullptr};           // Displays time left
    QLineEdit *messageLineEdit {nullptr};         // Displays game messages
    QLineEdit *scoreLineEdit {nullptr};           // Displays current score

public:
    TimedRoundWindow(QWidget *parent, int wordLength, bool hardMode, int minutes);
    virtual ~TimedRoundWindow();

public slots:
    /**
     * @brief Called every second (connected to oneSecTimer)
     */
    void updateTimer();

    /**
     * @brief Clear text on messageLineEdit.
     * Whenever text on messageLineEdit is set, call QTimer::singleShot() to call this after 1 second
     */
    void clearMessage();

    /**
     * @brief Display invalid word message on messageLineEdit
     */
    void msgInvalidWord();

    /**
     * @brief Display invalid hard mode guess message on messageLineEdit
     */
    void msgInvalidHardWord();

    /**
     * @brief Display word guesses message on messageLineEdit
     */
    void msgRoundWin();

    /**
     * @brief Display word unguessed message on messageLineEdit
     */
    void msgRoundLose();

    /**
     * @brief Update the score on scoreLineEdit
     */
    void scoreUpdate();

    /**
     * @brief Generates popup when user chooses "Give Up", asks for confirmation.
     * If Yes is chosen, end the game
     */
    virtual void popupConfirmGiveUp() override;

    /**
     * @brief Generates popup when user chooses "Reset Round", asks for confirmation.
     * If Yes is chosen, resets timer and tells the TimedWordleRound to restart the game.
     * Re-enables options other than Reset Round and updates the title
     */
    virtual void popupConfirmReset() override;

    /**
     * @brief Generates popup signifying that game has ended (via giving up or running out of time).
     * Disables options other than Reset Round and updates the title.
     * Also stops timer and tells the TimedWordleRound to end the game.
     */
    void popupRoundOver();

signals:
    /**
     * @brief Emitted when skipWordPushButton is clicked
     */
    void skipCurrentWord();

};

#endif // TIMEDROUNDWINDOW_H
