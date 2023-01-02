#ifndef KEY_H
#define KEY_H

#include <QToolButton>
#include <QColor>

/**
 * @brief Used in Keyboard for the buttons A to Z.
 * Extends QToolButton for background color manipulation.
 */
class Key : public QToolButton
{
    Q_OBJECT

private:
    QColor color {Qt::lightGray};

public:
    Key(QWidget* parent);

    /**
     * @brief Change the key color
     * @param c: new color
     */
    void setColor(const QColor& c);

    /**
     * @brief Reset the key color to default (light gray)
     */
    void reset();

    /**
     * @brief Get the key's current color
     * @return QColor: current color
     */
    QColor getColor() const { return color; }
};

#endif // KEY_H
