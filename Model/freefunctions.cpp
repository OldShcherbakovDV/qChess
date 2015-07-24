#include "freefunctions.h"

void outputField(chessGame *game){
    QString state;
    for (int i = 0; i < 8; ++i){
        state.clear();
        for (int j = 0; j < 8; ++j){
            piece *p = game->getBoard().getPiece(boardPosition(j, i));
            if (p != nullptr){
                if (p->getType() == piece::KING){
                    if (p->getColor() == piece::WHITE)
                        state +="K|";
                    else
                        state +="k|";
                }
                else if (p->getType() == piece::QUEEN){
                    if (p->getColor() == piece::WHITE)
                        state +="Q|";
                    else
                        state +="q|";
                }
                else if (p->getType() == piece::BISHOP){
                    if (p->getColor() == piece::WHITE)
                        state +="B|";
                    else
                        state +="b|";
                }
                else if (p->getType() == piece::KNIGHT){
                    if (p->getColor() == piece::WHITE)
                        state +="H|";
                    else
                        state +="h|";
                }
                else if (p->getType() == piece::ROOK){
                    if (p->getColor() == piece::WHITE)
                        state +="R|";
                    else
                        state +="r|";
                }
                else if (p->getType() == piece::PAWN){
                    if (p->getColor() == piece::WHITE)
                        state +="P|";
                    else
                        state +="p|";
                }
            }
            else{
                state +="_|";
            }
        }
        qDebug()<< state;
    }
}
