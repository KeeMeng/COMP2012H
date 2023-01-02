#include "regularwordleround.h"

RegularWordleRound::RegularWordleRound(QWidget *parent, const int len, const bool hardMode):
    WordleRound(parent, len, hardMode)
{
    initGuesses(parent);
}
