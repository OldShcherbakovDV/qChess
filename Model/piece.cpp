#include "piece.h"

piece::piece(piece::color c, piece::type t) : lColor(c), lType(t)
{

}

void piece::turnPawnToOtherPiece(piece::type t)
{
    if (lType == PAWN && t != KING)
        lType = t;
}
