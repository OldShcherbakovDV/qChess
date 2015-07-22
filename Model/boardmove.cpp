#include "boardmove.h"

boardMove::boardMove()
{

}

boardMove::boardMove(const boardPosition &start, const boardPosition &end, piece *moved, piece::type promote) :
    lStart(start), lEnd(end), lMovedPiece(moved), lPromote(promote)
{

}

bool boardMove::needPromotion(const QList<boardMove> &legals) const
{
    if (lMovedPiece->getType() != piece::PAWN){
        return false;
    }
    else if (lEnd.y() != 0 || lEnd.y() != 7){
        return false;
    }
    else if (lPromote != piece::NOTYPE){
        return false;
    }
    else if (!isLegal(legals)){
        return false;
    }
    return true;
}

bool boardMove::isLegal(const QList<boardMove> &legals) const
{
    return legals.contains(*this);
}

