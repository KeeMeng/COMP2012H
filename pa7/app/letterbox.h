#ifndef LETTERBOX_H
#define LETTERBOX_H

#include <QLineEdit>
#include <QColor>

// Convenient QColor defines
static const QColor GREY = Qt::gray;
static const QColor YELLOW = Qt::yellow;
static const QColor GREEN = Qt::green;

/**
 * @brief Used in WordleRound for the on-screen letter boxes.
 * Extends QLineEdit for text and background color manipulation.
 */
class LetterBox : public QLineEdit
{
    Q_OBJECT

private:
    QChar letter {' '};
    QColor default_color;

public:
    LetterBox(QWidget* parent);

    /**
     * @brief Change the current letter
     * @param l: new letter (lowercase)
     */
    void setLetter(const QChar& l);

    /**
     * @brief Change the current color
     * @param c: new color
     */
    void setColor(const QColor& c);

    /**
     * @brief Reset to default state (light gray, no letter)
     */
    void reset();

    /**
     * @brief Get the current letter (lowercase)
     * @return The current letter in lowercase
     */
    QChar getLetter() const { return letter; }
};

#endif // LETTERBOX_H
