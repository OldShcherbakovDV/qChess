#include "piece.h"

piece::piece(piece::color c, piece::type t) : lType(t), lColor(c)
{

}

void piece::turnPawnToOtherPiece(piece::type t)
{
    if (lType == PAWN && t != KING && t != NOTYPE)
        lType = t;
}
