#include "key.h"

QString getStyleSheet(const QString& color) {
    return
        "QToolButton { background-color: " + color + "; }"
    ;
}

Key::Key(QWidget *parent): QToolButton(parent)
{
    setColor(Qt::lightGray);
}

void Key::setColor(const QColor& c) {
    color = c;
    if (c == Qt::gray) {
        setStyleSheet(getStyleSheet("gray"));
    }
    else if (c == Qt::yellow) {
        setStyleSheet(getStyleSheet("yellow"));
    }
    else if (c == Qt::green) {
        setStyleSheet(getStyleSheet("lime"));
    }
    else if (c == Qt::lightGray) {
        setStyleSheet(getStyleSheet("gainsboro"));
    }
}

void Key::reset() {
    setColor(Qt::lightGray);
}
