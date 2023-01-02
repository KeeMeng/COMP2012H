#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "roundwindow.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The starting window for user to select game mode
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    // For testing purposes, these classes can access UI
    friend class TestTask4;
    friend class TestTask5;
    friend class TestBonusTask1;
    friend class TestBonusTask2;
    friend class TestBonusTask3;

private:
    Ui::MainWindow *ui;
    RoundWindow *curRound {nullptr};

    /**
     * @brief Hide the extra options (Time, Number of Words, Hard Mode)
     */
    void resetExtraOptions();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    /**
     * @brief Called when the Start button is clicked.
     * Starts a new RoundWindow depending on current selected mode and options,
     * then hide this window.
     */
    void start();

    /**
     * @brief Called when the RoundWindow is closed.
     * Show this window and delete the RoundWindow.
     */
    void returnToMain();

    /**
     * @brief Called when the mode ComboBox is updated.
     * Updates the extra options accordingly
     * @param mode: new mode
     */
    void modeChanged(const QString &mode);

};

#endif // MAINWINDOW_H
