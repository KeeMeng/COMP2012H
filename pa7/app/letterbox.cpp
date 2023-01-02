#include "letterbox.h"

LetterBox::LetterBox(QWidget* parent): QLineEdit(parent)
{
    setEnabled(false);
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(50, 40);
    QPalette palette = this->palette();
    default_color = palette.color(QPalette::Base);
    palette.setColor(QPalette::Text, Qt::black);
    setPalette(palette);
}

void LetterBox::setLetter(const QChar& l) {
    letter = l;
    setText(QString(letter).toUpper());
}

void LetterBox::setColor(const QColor& c) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, c);
    setPalette(palette);
}

void LetterBox::reset() {
    setLetter(' ');
    setColor(default_color);
}
