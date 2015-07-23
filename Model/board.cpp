#include "board.h"

mask board::pawnAttacks[2][64];
mask board::knightAttacks[64];
mask board::kingAttacks[64];
mask board::xAttacks[64][256];
mask board::yAttacks[64][256];
mask board::diagAttacksLeftTop[64][256];
mask board::diagAttacksRightTop[64][256];
int board::pow2[8];
piece *board::allPieces[2][6]; //Указатель на фигуру каждого типа
bool board::isSetup;

board::board()
{
    setDefault();
    if(!isSetup) {
        setupPieces();
    }
}

board::~board()
{

}

void board::init()
{
    pow2[0] = 1;
    for(int i = 1; i < 8; i++)
        pow2[i] = 2*pow2[i-1];

    // Инициализация атак для фигур атакующих по фиксированным полям
    for(int i = 0; i < 64; i++) {

        bitBoard pawnW, pawnB, knight, king;

        // Пешки
        pawnW.setBit(boardPosition(i).getRightBottom());
        pawnW.setBit(boardPosition(i).getRightTop());
        pawnB.setBit(boardPosition(i).getLeftBottom());
        pawnB.setBit(boardPosition(i).getLeftTop());
        pawnAttacks[piece::WHITE][i] = pawnW.getBoard();
        pawnAttacks[piece::BLACK][i] = pawnB.getBoard();

        // Koни
        knight.setBit(boardPosition(i).getRightBottom().getRight());
        knight.setBit(boardPosition(i).getRightTop().getRight());
        knight.setBit(boardPosition(i).getLeftBottom().getLeft());
        knight.setBit(boardPosition(i).getLeftTop().getLeft());
        knight.setBit(boardPosition(i).getRightBottom().getBottom());
        knight.setBit(boardPosition(i).getRightTop().getTop());
        knight.setBit(boardPosition(i).getLeftBottom().getBottom());
        knight.setBit(boardPosition(i).getLeftTop().getTop());
        knightAttacks[i] = knight.getBoard();

        // Короли
        king.setBit(boardPosition(i).getRightBottom());
        king.setBit(boardPosition(i).getRightTop());
        king.setBit(boardPosition(i).getLeftBottom());
        king.setBit(boardPosition(i).getLeftTop());
        king.setBit(boardPosition(i).getRight());
        king.setBit(boardPosition(i).getTop());
        king.setBit(boardPosition(i).getBottom());
        king.setBit(boardPosition(i).getLeft());
        kingAttacks[i] = king.getBoard();
    }

    // Инициализация атак для фигур атакующих по линиям
    mask state;
    for(int rank = 0; rank < 8; rank++) {
        for(int file = 0; file < 8; file++) {
            for(state = 0LL; state < 256LL; state++) {

                xAttacks[rank*8 + file][state] = 0LL;
                boardPosition bp(file, rank);
                bool occupied = false;

                // Вправо
                for(bp = bp.getRight(); !bp.isValid() && !occupied; bp = bp.getRight()) {
                    xAttacks[rank*8 + file][state] |= bitBoard::getMask(bp);
                    occupied = bitBoard::getMask(bp) & (state << rank*8);
                }

                bp = boardPosition(file, rank);
                occupied = false;

                // Влево
                for(bp = bp.getLeft(); !bp.isValid() && !occupied; bp = bp.getLeft()) {
                    xAttacks[rank*8 + file][state] |= bitBoard::getMask(bp);
                    occupied = bitBoard::getMask(bp) & (state << rank*8);
                }

                // Initialize the file attack masks for sliding pieces
                yAttacks[rank*8 + file][state] = 0LL;
                bp = boardPosition(file, rank);
                occupied = false;

                // вверх
                for(bp = bp.getTop(); !bp.isValid() && !occupied; bp = bp.getTop()) {
                    yAttacks[rank*8 + file][state] |= bitBoard::getMask(bp);
                    occupied = bitBoard::getMask(bp) & (state << rank*8);
                }

                bp = boardPosition(file, rank);
                occupied = false;

                // Вниз
                for(bp = bp.getBottom(); !bp.isValid() && !occupied; bp = bp.getBottom()) {
                    yAttacks[rank*8 + file][state] |= bitBoard::getMask(bp);
                    occupied = bitBoard::getMask(bp) & (state << rank*8);
                }


                diagAttacksRightTop[rank*8 + file][state] = 0LL;
                bp = boardPosition(file, rank);
                occupied = false;
                int shift;

                // Вправо-вверх
                for(bp = bp.getRightTop(); !bp.isValid() && ! occupied; bp = bp.getRightTop()){
                    diagAttacksRightTop[rank*8 + file][state] |= bitBoard::getMask(bp);
                    shift = (rank+file < 8) ? bp.x() : 7-bp.y();
                    occupied = (state >> shift) & 1LL;
                }

                bp = boardPosition(file, rank);
                occupied = false;

                // Влево-вниз
                for(bp = bp.getLeftBottom(); !bp.isValid() && ! occupied; bp = bp.getLeftBottom()){
                    diagAttacksRightTop[rank*8 + file][state] |= bitBoard::getMask(bp);
                    shift = (rank+file < 8) ? bp.x() : 7-bp.y();
                    occupied = (state >> shift) & 1LL;
                }


                diagAttacksLeftTop[rank*8 + file][state] = 0LL;
                bp = boardPosition(file, rank);
                occupied = false;

                // Влево-вниз
                for(bp = bp.getLeftTop(); !bp.isValid() && ! occupied; bp = bp.getLeftTop()){
                    diagAttacksLeftTop[rank*8 + file][state] |= bitBoard::getMask(bp);
                    shift = (rank+file < 8) ? bp.x() : 7-bp.y();
                    occupied = (state >> shift) & 1LL;
                }

                bp = boardPosition(file, rank);
                occupied = false;

                // Влево-вниз
                for(bp = bp.getRightBottom(); !bp.isValid() && ! occupied; bp = bp.getRightBottom()){
                    diagAttacksLeftTop[rank*8 + file][state] |= bitBoard::getMask(bp);
                    shift = (rank+file < 8) ? bp.x() : 7-bp.y();
                    occupied = (state >> shift) & 1LL;
                }
            }
        }
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

void board::setSpecialPieceFlags(const boardMove &bm)
{
    piece::color c = getPiece(bm.getStart())->getColor();
    piece::type  t = getPiece(bm.getStart())->getType();

    // Отчищаем отмеченые ходы на
    lEnpassling = 0LL;
    // Отмечаем переремещение фигуры в флагах рокировки
    lCastlingFlags &= ~bitBoard::getMask(bm.getEnd());
    if (t == piece::KING){
        lCastlingFlags &= ~bitBoard::getMask(bm.getStart());
    }
    else if (t == piece::PAWN){
        lEnpassling |= bitBoard::getMask((c == piece::WHITE) ? bm.getStart().getTop() : bm.getStart().getBottom());
    }
}

void board::update(const boardMove &bm)
{
    piece::color c = getPiece(bm.getStart())->getColor();
    piece::type  t = getPiece(bm.getStart())->getType();

    if (t == piece::PAWN){ // Особые ситуации пешки
        if (c == piece::WHITE && isEnPassantSet(bm.getEnd())){ // Взятие на проходе белые
            removePiece(bm.getEnd().getBottom());
        }
        else if (c == piece::BLACK && isEnPassantSet(bm.getEnd())){ // Взятие на проходе черные
            removePiece(bm.getEnd().getTop());
        }
        else if (bm.getEnd().y() == 7 || bm.getEnd().y() == 0){ // Замена на другую фигуру
            t = bm.getPromote();
        }
    }
    else if (t == piece::KING){ // Ракировки
        int dif = bm.getEnd().x() - bm.getStart().x();
        if (abs(dif) == 2){
            boardPosition currRook, newRookPos;
            currRook.setY((c == piece::WHITE) ? 0 : 7);
            if (dif == 2){ // Короткая
                currRook.setX(7);
                newRookPos = bm.getEnd().getLeft();
            }
            else { // Длинная
                currRook.setX(0);
                newRookPos = bm.getEnd().getRight();
            }
            setPiece(getPiece(currRook), newRookPos);
            removePiece(currRook);
        }
    }
    piece mp(c, t);
    setPiece(&mp, bm.getEnd());
    removePiece(bm.getStart());
    setSpecialPieceFlags(bm);
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
                return allPieces[c][i];
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

bool board::isPathClear(const boardMove &bm) const
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

bool board::isCheck(piece::color c) const
{
    return isAttacked(kingsPos[c], c);
}

bool board::isResultCheck(const boardMove &bm) const
{
    board b = *this;
    b.update(bm);
    return (b.isCheck(bm.getMovedPiece()->getColor()));
}

bool board::isMate(piece::color c) const
{
    return (isCheck(c) && isStalemate(c));
}

bool board::isStalemate(piece::color c) const
{
    return getLegalMoves(c, true).isEmpty();
}

mask board::isAttacked(const boardPosition &bp, piece::color c) const
{
    piece::color attacker = piece::opponentColor(c);
    int pos = bp.number();
    int y = getYState(bp);
    int x = getXState(bp);
    int diagLeftTop = getLeftTopDiagState(bp);
    int diagRightTop = getRightTopDiagState(bp);

    mask lboard = 0LL;
    lboard |= pawnAttacks[c][pos] & lPieces[piece::PAWN] & lColors[attacker];
    lboard |= knightAttacks[pos] & lPieces[piece::KNIGHT] & lColors[attacker];
    lboard |= kingAttacks[pos] & lPieces[piece::KING] & lColors[attacker];
    lboard |= yAttacks[pos][y] & lPieces[piece::ROOK] & lColors[attacker];
    lboard |= yAttacks[pos][y] & lPieces[piece::QUEEN] & lColors[attacker];
    lboard |= xAttacks[pos][x] & lPieces[piece::ROOK] & lColors[attacker];
    lboard |= xAttacks[pos][x] & lPieces[piece::QUEEN] & lColors[attacker];
    lboard |= diagAttacksLeftTop[pos][diagLeftTop] & lPieces[piece::BISHOP] & lColors[attacker];
    lboard |= diagAttacksLeftTop[pos][diagLeftTop] & lPieces[piece::QUEEN] & lColors[attacker];
    lboard |= diagAttacksRightTop[pos][diagRightTop] & lPieces[piece::BISHOP] & lColors[attacker];
    lboard |= diagAttacksRightTop[pos][diagRightTop] & lPieces[piece::QUEEN] & lColors[attacker];

    return lboard;
}

QList<boardMove> board::getLegalMoves(const boardPosition &bp) const
{
    QList<boardMove> moves;
    boardMove move;
    piece *curPiece = getPiece(bp);
    if (curPiece == nullptr){
        return moves;
    }

    switch (curPiece->getType()) { // По типу фигуры моделируем её поведение
    case piece::PAWN: //Пешка
        if (curPiece->getColor() == piece::BLACK){
            if (!isOccupied(bp.getBottom())){ // ход на одну позицию вперет
                move = boardMove(bp, bp.getBottom(), curPiece);
                moves.append(move);
            }
            move = boardMove(bp, bp.getBottom().getBottom(),curPiece);
            if (bp.y() == 6 && isPathClear(move)){ // ход на две позицию вперет
                if (move.getEnd().isValid())
                    moves.append(move);
            }
            move = boardMove(bp, bp.getRightBottom(), curPiece); // Взятие вправо
            if (move.getEnd().isValid() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
            move = boardMove(bp, bp.getLeftBottom(), curPiece); // Взятие влево
            if (move.getEnd().isValid() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
        }
        else {
            if (!isOccupied(bp.getTop())){ // ход на одну позицию вперет
                move = boardMove(bp, bp.getTop(), curPiece);
                moves.append(move);
            }
            move = boardMove(bp, bp.getTop().getTop(), curPiece);
            if (bp.y() == 1 && isPathClear(move)){ // ход на две позицию вперет
                if (move.getEnd().isValid())
                    moves.append(move);
            }
            move = boardMove(bp, bp.getRightTop(), curPiece); // Взятие вправо
            if (move.getEnd().isValid() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
            move = boardMove(bp, bp.getLeftTop(), curPiece); // Взятие влево
            if (move.getEnd().isValid() && (isOccupied(move.getEnd()) &&getPiece(move.getEnd())->getColor() != curPiece->getColor()) || isEnPassantSet(move.getEnd())){
                moves.append(move);
            }
        }
        break;
    case piece::QUEEN: //Ферзь
    case piece::ROOK: //Ладья
        for (move = boardMove(bp, bp.getTop(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getTop(), curPiece)){//Вверх
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        for (move = boardMove(bp, bp.getBottom(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getBottom(), curPiece)){//Вниз
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        for (move = boardMove(bp, bp.getRight(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getRight(), curPiece)){//Вправо
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        for (move = boardMove(bp, bp.getLeft(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getLeft(), curPiece)){//Влево
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        if (curPiece->getType() == piece::ROOK)
            break;
    case piece::BISHOP: //Слон
        for (move = boardMove(bp, bp.getRightTop(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getRightTop(), curPiece)){//Вверх вправо
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        for (move = boardMove(bp, bp.getLeftTop(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getLeftTop(), curPiece)){//Вверх влево
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        for (move = boardMove(bp, bp.getRightBottom(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getRightBottom(), curPiece)){//Вверх
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        for (move = boardMove(bp, bp.getLeftBottom(), curPiece); move.getEnd().isValid() && isPathClear(move); move = boardMove(bp, move.getEnd().getLeftBottom(), curPiece)){//Вверх влево
            moves.append(move);
        }
        if (move.getEnd().isValid() && isOccupied(move.getEnd()) && getPiece(move.getEnd())->getColor() == curPiece->getColor()){
            moves.append(move);
        }
        break;
    case piece::KNIGHT: //Конь
        move = boardMove(bp, bp.getTop().getLeftTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getTop().getRightTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getBottom().getLeftBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getBottom().getRightBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getLeft().getLeftTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getRight().getRightTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getLeft().getLeftBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getRight().getRightBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        break;
    case piece::KING:
        move = boardMove(bp, bp.getTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getRight(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getLeft(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getLeftTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getLeftBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getRightBottom(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        move = boardMove(bp, bp.getRightTop(), curPiece);
        if (move.getEnd().isValid()){
            if (!isOccupied(move.getEnd()) || getPiece(move.getEnd())->getColor() != curPiece->getColor()){
                moves.append(move);
            }
        }
        break;
    }

    for (int i = moves.count() - 1; i >= 0; --i){
        if (isResultCheck(moves[i])){
            moves.removeAt(i);
        }
    }
    return moves;

}

QList<boardMove> board::getLegalMoves(piece::color c, bool fast) const
{
    QList<boardPosition> pos;
    boardPosition movedPiece;
    QList<boardMove> goodMoves;
    //Определяем позиции всех фигур этого цвета
    for (int i = 0; i < 64; ++i){
        if ((lColors[c] >> i) & 1){
            pos.append(boardPosition(i));
        }
    }
    foreach (movedPiece, pos) {
        goodMoves.append(getLegalMoves(movedPiece));
        if (!goodMoves.isEmpty() && fast){
            return goodMoves;
        }
    }
    return goodMoves;
}

int board::getXState(const boardPosition &bp) const
{
    mask state = 0LL;
    int ret = 0;
    char x = bp.x();

    state = (lColors[piece::WHITE] | lColors[piece::BLACK]) & bitBoard().getXMask(bp);
    char shift = x;
    for(int i = 0; i < 7; i++) {
        ret |= (state >> shift);
        shift += 7;
    }

    return ret & 0xFF;
}

int board::getLeftTopDiagState(const boardPosition &bp) const
{
    int state = 0, x = bp.x(), y = bp.y();
    boardPosition tmp;

    if(x + y < 8)
        tmp = boardPosition(0, x + y);
    else
        tmp = boardPosition(x + y-7, 7);

    for(int i = 0; !tmp.isValid(); tmp = tmp.getLeftTop(), i++)
        if(bitBoard::getMask(tmp) & (lColors[piece::WHITE] | lColors[piece::BLACK]))
            state += pow2[i];

    return state;
}

int board::getRightTopDiagState(const boardPosition &bp) const
{
    int state = 0, x = bp.x(), y = bp.y();
    boardPosition tmp;

    if(x > y)
        tmp = boardPosition(x - y,0);
    else
        tmp = boardPosition(0, y - x);

    for(int i = 0; !tmp.isValid(); tmp = tmp.getRightTop(), i++)
        if(bitBoard::getMask(tmp) & (lColors[piece::WHITE] | lColors[piece::BLACK]))
            state += pow2[i];

    return state;
}

