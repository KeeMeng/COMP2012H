#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QPushButton>

#include "helper.h"
#include "key.h"
#include "wordleround.h"

/**
 * @brief Holds the 26 letter keys and the Del/Enter key.
 * Communicates with the current WordleRound:
 *  - Send key input (from on-screen or actual keyboard) to the round
 *  - Receives color update from the round to color the keys
 *
 *  Usage: After initializing a Keyboard object,
 *  add the 26 A-Z keys via addKey(),
 *  add Delete and Enter keys via addDelKey() and addEnterKey(),
 *  assign the keyboard to the current WordleRound via setCurrentRound(),
 *  connect the WordleRound's color update signals with this Keyboard's slots (if needed).
 */
class Keyboard: public QObject
{
    Q_OBJECT

private:
    Key* keys[NUM_LETTERS] = {nullptr};
    QPushButton *delKey = nullptr, *enterKey = nullptr;
    WordleRound *curRound = nullptr;

public:
    Keyboard();

    /**
     * @brief Add a Key to this keyboard
     * @param key: pointer to Key/QToolButton object
     * @param keyChar: corresponding letter (Uppercase)
     */
    void addKey(Key *key, char keyChar);

    /**
     * @brief Add the Delete key to this keyboard
     * @param key: pointer to QPushButton object
     */
    void addDelKey(QPushButton *key);

    /**
     * @brief Add the Enter key to this keyboard
     * @param key: pointer to QPushButton object
     */
    void addEnterKey(QPushButton *key);

    /**
     * @brief Link this Keyboard with the current WordleRound
     * @param wr: pointer to a WordleRound or any derived class
     */
    void setCurrentRound(WordleRound *wr);

    /**
     * @brief Tell the WordleRound to register a letter key
     * @param key: corresponding letter (lowercase)
     */
    void keyPressed(const QChar& key) const;

public slots:
    /**
     * @brief Used by the widget keyboard; calls keyPressed()
     */
    void keyOnScreenPressed() const;

    /**
     * @brief Tell the WordleRound to register the Delete key
     */
    void delKeyPressed() const;

    /**
     * @brief Tell the WordleRound to register the Enter key
     */
    void enterKeyPressed() const;

    /**
     * @brief Update the Key of the corresponding letter with the new color.
     * Follows Wordle convention to keep the "highest" color
     * @param key: letter (lowercase) to be updated
     * @param color: new color
     */
    void updateKeyColor(const QChar& key, const QColor& color);

    /**
     * @brief Resets all keys' colors to default
     */
    void resetKeyColor();

};

#endif // KEYBOARD_H
