#include "options.h"

options::options()
{
    player1 = "human";
    player2 = "AI";

    //Конфигурации внешнего вида
    blackPiece = QColor(0,0,0);
    whitePiece = QColor(175,144,91);
    blackCell  = QColor(99,40,23);
    whiteCell  = QColor(244,219,178);
    blackCellAttacked = QColor(198,60,57);
    whiteCellAttacked = QColor(255,76,73);
    blackCellCanMove  = QColor(99,159,23);
    whiteCellCanMove  = QColor(126,216,106);
    deadCell          = QColor(198,155,155);
}

