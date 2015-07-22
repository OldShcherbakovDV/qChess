#include "board.h"

board::board()
{
    setDefault();
    if(!isSetup) {
        setupPieces();
    }
}

void board::setupPieces()
{
    for(int i=0; i <= 2; i++) {
        for(int j=0; j <= 6; j++) {
            allPieces[i][j] = new piece(piece::color(i), piece::type(j));
        }
    }
    isSetup = true;
}

void board::setDefault()
{
    for (int i=0; i < 2; i++) {
        lColors[i] = 0LL;
    }

    for (int i=0; i < 6; i++) {
        lPieces[i] = 0LL;
        lPieceCount[piece::WHITE][i] = 0;
        lPieceCount[piece::BLACK][i] = 0;
    }

    lCastlingFlags = 0x9100000000000091LL;
    lEnpassling = 0LL;
    lTotalPiece[piece::WHITE] = 0;
    lTotalPiece[piece::BLACK] = 0;
}

piece *board::getPiece(const boardPosition &bp) const
{
    mask m;         //Маска определяющая положение фигуры
    piece::color c; //Цвет фигуры
    if (isOccupied(bp)){ // Если на клетке стоит фигура
        m = bitBoard::getMask(bp);
        c = lColors[piece::WHITE] & m ? piece::WHITE : piece::BLACK; // Если бит цвета опущен то даст лож т к 1*0 даст ноль, а операция проходит побитово
        for (int i = 0; i < 6; ++i){ // для каждого типа фигур
            if (lPieces[i] & m){ // аналогично цвету
                return allPieces[i];
            }
        }
    }
    return nullptr;
}

void board::setPiece(piece *p, const boardPosition &bp)
{
    if (isOccupied(bp)){ // если позиция занята другой фигурой
        piece *deletePiece = getPiece(bp);
        lPieceCount[deletePiece->getColor()][deletePiece->getType()]--;
        lTotalPiece[deletePiece->getColor()]--;
        removePiece(bp);
    }
    bitBoard bb1(lPieces[p->getType()]), bb2(lColors[p->getColor()]);
    bb1.setBit(bp);
    bb2.setBit(bp);
    lPieces[p->getType()] = bb1.getBoard();
    lColors[p->getColor()] = bb2.getBoard();
    if (p->getType() == piece::KING){
        kingsPos[p->getColor()] = bp;
    }

}

void board::removePiece(const boardPosition &bp)
{
    mask m = ~bitBoard::getMask(bp);
    piece *p = getPiece(bp);
    lPieces[p->getType()] &= m;
    lColors[p->getColor()] &= m;


}

bool board::isPathClear(boardMove &bm) const
{
    bool swap = (bm.getStart().x() > bm.getEnd().x());
    boardPosition start = swap ? bm.getEnd() : bm.getStart();
    boardPosition end = swap ? bm.getStart() : bm.getEnd();

    int topBottomSing = (end.y() - start.y())/((end.y() - start.y() == 0) ? 1 : abs((end.y() - start.y())));
    int leftRightSing = (end.x() - start.x()) ? 1 : 0;

    for (boardPosition i = start; i != end;){
        i.setX(i.x() + leftRightSing);
        i.setY(i.y() + topBottomSing);
        if (isOccupied(i)){
            return false;
        }
    }
    return true;
}

bool board::isOccupied(const boardPosition &bp) const
{
    return (lColors[piece::WHITE] | lColors[piece::BLACK]) & bitBoard::getMask(bp);
}

QList<boardMove> board::getLegalMoves(const boardPosition &bp) const
{
    QList<boardMove> moves;
    boardMove move;
    piece *curPiece = getPiece(bp);
    if (curPiece == nullptr){
        return moves;
    }

    switch (curPiece->type) { // По типу фигуры моделируем её поведение
    case piece::PAWN: //Пешка
        if (curPiece->getColor() == piece::BLACK){
            if (!isOccupied(bp.getBottom())){ // ход на одну позицию вперет
                move = boardMove(bp, bp.getBottom());
                moves.append(move);
            }
            if (bp.y() == 6 && isPathClear(bp.getBottom().getBottom())){ // ход на две позицию вперет
                move = boardMove(bp, bp.getBottom().getBottom());
                if (move.isLegal())
                    moves.append(move);
            }
            move = boardMove(bp, bp.getRightBottom()); // Взятие вправо
            if (move.isLegal() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
            move = boardMove(bp, bp.getLeftBottom()); // Взятие влево
            if (move.isLegal() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
        }
        else {
            if (!isOccupied(bp.getTop())){ // ход на одну позицию вперет
                move = boardMove(bp, bp.getTop());
                moves.append(move);
            }
            if (bp.y() == 1 && isPathClear(bp.getTop().getTop())){ // ход на две позицию вперет
                move = boardMove(bp, bp.getTop().getTop());
                if (move.isLegal())
                    moves.append(move);
            }
            move = boardMove(bp, bp.getRightTop()); // Взятие вправо
            if (move.isLegal() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
            move = boardMove(bp, bp.getLeftTop()); // Взятие влево
            if (move.isLegal() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
        }
        break;
    case piece::ROOK: //Ладья

        break;
    default:
        break;
    }

}

