#include "options.h"

options::options()
{
    player1 = "human";
    player2 = "AI";

    //Конфигурации внешнего вида
    blackPiece = QColor(1,1,1);
    whitePiece = QColor(255,255,255);
    blackCell  = QColor(1,80,1);
    whiteCell = QColor(255,1,255);
    blackCellAttacked = blackPiece;
    whiteCellAttacked = whitePiece;
    blackCellCanMove  = blackPiece;
    whiteCellCanMove  = whitePiece;
}

