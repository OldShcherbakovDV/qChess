#include "chessgamestate.h"

chessGameState::chessGameState()
{
    init();
}

void chessGameState::init()
{
    l50Moves = 0;
    lIsCheck = false;
    isThreefold = false;
    lStepNumber = 1;
    lIsWhiteStep = true;
    lLastMove = boardMove();
    lThreefoldCount.clear();
    lBoard.setDefault();

    piece::type t;
    piece::color c;
    boardPosition bp;
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            c = (y < 2) ? piece::WHITE : piece::BLACK;
            bp = boardPosition(x, y);

            if (y == 1 || y == 6){
                t = piece::PAWN;
            }
            else if(y != 0 || y != 7){
                lPieces[bp.number()] = nullptr;
                break;
            }
            else if(x == 0 || x == 7){
                t = piece::ROOK;
            }
            else if(x == 1 || x == 6){
                t = piece::KNIGHT;
            }
            else if(x == 2 || x == 5){
                t = piece::BISHOP;
            }
            else if(x == 3){
                t = piece::QUEEN;
            }
            else{
                t = piece::KING;
            }

            lPieces[bp.number()] = new piece(c, t);
            lBoard.addPiecet(lPieces[bp.number()], bp);
        }
    }
}

void chessGameState::makeMove(const boardMove &bm)
{
    serialBoard sb;
    piece::color c = bm.getMovedPiece()->getColor();
    piece::type  t = bm.getMovedPiece()->getType();

    if (lStepNumber > 1 && lLastMove.needPromotion(lBoard.getLegalMoves(lLastMove.getStart()))){
        return;
    }

    if (lStepNumber == 1){
        sb = lBoard.serialize();
        sb.whiteTurn = 1;
        lThreefoldCount.append(QPair<serialBoard, int>(sb, 1));
    }
    if (t != piece::PAWN || lBoard.isOccupied(bm.getEnd())){ //Правилло 50 ходов
        l50Moves++;
    }
    else{
        l50Moves = 0;
        lThreefoldCount.clear();
    }

    lBoard.update(bm);
    lLastMove = bm;
    lIsWhiteStep = !lIsWhiteStep;

    if (t == piece::PAWN && bm.getStart().x() != bm.getEnd().x() && lPieces[bm.getEnd().number()] == nullptr){
        //Взятие на проходе
        lPieces[(c == piece::WHITE) ? bm.getEnd().getTop().number() : bm.getEnd().getBottom().number()] = nullptr;
    }
    else if (t == piece::KING ){
        int dif = bm.getStart().x() - bm.getEnd().x();
        if (abs(dif) == 2){ //рокировка
            boardPosition currentRook((dif < 0) ? 0 : 7, (c == piece::WHITE) ? 0 : 7);
            lPieces[(dif > 0) ? bm.getStart().getRight().number() : bm.getStart().getLeft().number()] = lPieces[currentRook.number()];
            lPieces[currentRook.number()] = nullptr;
        }
    }

    lPieces[bm.getEnd().number()] = lPieces[bm.getStart().number()];
    lPieces[bm.getEnd().number()]->turnPawnToOtherPiece(bm.getPromote());
    lPieces[bm.getStart().number()] = nullptr;

    lIsCheck = lBoard.isCheck(piece::opponentColor(bm.getMovedPiece()->getColor()));


    sb = lBoard.serialize();
    sb.whiteTurn = lIsWhiteStep ? 1 : 0;
    int i;
    for(; i < lThreefoldCount.size(); ++i) {
        if(isEquivalent(sb, lThreefoldCount[i].first)) {
            lThreefoldCount[i].second++;
            if(lThreefoldCount[i].second >= 3) {
                isThreefold = true;
            }
            break;
        }
    }
    if(i == lThreefoldCount.size()) {
        lThreefoldCount.append(QPair <serialBoard, int> (sb, 1));
    }

    if (lIsWhiteStep){
        lStepNumber++;
    }
}

bool chessGameState::isPositionSelectable(const boardPosition &bp) const
{
    return bp.isValid() && lBoard.isOccupied(bp) && lBoard.getPiece(bp)->getColor() == getColor();
}

