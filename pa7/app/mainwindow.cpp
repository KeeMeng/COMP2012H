#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"

#include "regularroundwindow.h"
#include "multiroundwindow.h"
#include "timedroundwindow.h"
#include "absurdroundwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap logo {":/images/logo.png"};
    ui->labelLogo->setPixmap(logo.scaled(logo.size() / 1.5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->labelLogo->setScaledContents(false);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::start);

    /**
     * TODO: TASK 4
     *
     * Connect the mode comboBox's currentTextChanged() signal with MainWindow modeChanged() slot.
     * We also need to hide the non-default options. Call modeChanged() using comboBoxMode's current text.
     */

    connect(ui->comboBoxMode, &QComboBox::currentTextChanged, this, &MainWindow::modeChanged);

    modeChanged(ui->comboBoxMode->currentText());

}

MainWindow::~MainWindow()
{
    delete ui;
    SAFE_DELETE(curRound);
}

/**
 * TODO: TASK 4
 *
 * Hide the widgets other than mode selection, word length selection and Play button
 */
void MainWindow::resetExtraOptions() {
    ui->labelNumWords->hide();
    ui->spinBoxNumWords->hide();
    ui->labelTime->hide();
    ui->comboBoxTime->hide();
    ui->checkBoxHardMode->hide();
}

void MainWindow::start() {
    /**
     * TODO: TASK 4
     *
     * Get wordLength, mode and hardMode from the corresponding widgets' values
     */
    const int wordLength = this->ui->spinBoxWordLength->value();
    const QString mode = this->ui->comboBoxMode->currentText();
    const bool hardMode = this->ui->checkBoxHardMode->isChecked();
    if (mode == "Regular") {
        try {
            // Create a new RoundWindow object and assign to curRound. Connect its close signal with returnToMain.
            curRound = new RegularRoundWindow(nullptr, wordLength, hardMode);
            connect(curRound, &RoundWindow::closeRound, this, &MainWindow::returnToMain);

            // Show the round window and hide this one
            curRound->show();
            hide();
        } catch (const DictionaryException& e) {
            // Something went wrong with initializing Dictionary. Start a pop-up message and delete curRound.
            QMessageBox::information(this, "Unable to start round", e.what());
            SAFE_DELETE(curRound);
        }
    }
    else if (mode == "Absurd") {
        /**
         * TODO: BONUS TASK 1
         *
         * You can refer to the code above to create a new AbsurdRoundWindow object,
         * and safely return if DictionaryException would be thrown.
         */
        try {
            curRound = new AbsurdRoundWindow(nullptr, wordLength);
            connect(curRound, &RoundWindow::closeRound, this, &MainWindow::returnToMain);

            curRound->show();
            hide();
        } catch (const DictionaryException& e) {
            // Something went wrong with initializing Dictionary. Start a pop-up message and delete curRound.
            QMessageBox::information(this, "Unable to start round", e.what());
            SAFE_DELETE(curRound);
        }
    }
    else if (mode == "Multiple") {
        /**
         * TODO: BONUS TASK 2
         *
         * You can refer to the code above to create a new MultiRoundWindow object,
         * and safely return if DictionaryException would be thrown.
         */
        try {
            curRound = new MultiRoundWindow(nullptr, wordLength, this->ui->spinBoxNumWords->value());
            connect(curRound, &RoundWindow::closeRound, this, &MainWindow::returnToMain);

            curRound->show();
            hide();
        } catch (const DictionaryException& e) {
            // Something went wrong with initializing Dictionary. Start a pop-up message and delete curRound.
            QMessageBox::information(this, "Unable to start round", e.what());
            SAFE_DELETE(curRound);
        }
    }
    else if (mode == "Timed") {
        /**
         * TODO: BONUS TASK 3
         *
         * You can refer to the code above to create a new TimedRoundWindow object,
         * and safely return if DictionaryException would be thrown.
         *
         * Hint: use QString split() and toInt() to get the number of minutes.
         */
        try {
            curRound = new TimedRoundWindow(nullptr, wordLength, hardMode, this->ui->comboBoxTime->currentText().split(" ")[0].toInt());
            connect(curRound, &RoundWindow::closeRound, this, &MainWindow::returnToMain);

            curRound->show();
            hide();
        } catch (const DictionaryException& e) {
            // Something went wrong with initializing Dictionary. Start a pop-up message and delete curRound.
            QMessageBox::information(this, "Unable to start round", e.what());
            SAFE_DELETE(curRound);
        }
    }
}

void MainWindow::returnToMain() {
    this->show();
    SAFE_DELETE(curRound);
}

/**
 * TODO: TASK 4
 *
 * This function is called whenever the mode is changed.
 * Hide all of the extra options, then depending on the mode text
 * ("Regular", "Absurd", "Multiple" or "Timed"),
 * show the corresponding widgets:
 *
 * - Regular: Hard Mode
 * - Multiple: Number of words
 * - Timed: Time and Hard Mode
 * - Absurd: None
 */
void MainWindow::modeChanged(const QString &mode) {
    resetExtraOptions();
    if (mode == "Regular") {
        ui->checkBoxHardMode->show();
    } else if (mode == "Multiple") {
        ui->labelNumWords->show();
        ui->spinBoxNumWords->show();
    } else if (mode == "Timed") {
        ui->labelTime->show();
        ui->comboBoxTime->show();
        ui->checkBoxHardMode->show();
    } else if (mode == "Absurd") {
    }
}
