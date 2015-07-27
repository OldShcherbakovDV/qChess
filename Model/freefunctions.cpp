#include "freefunctions.h"

QString outputField(board *game){
    QString state;
    QString res;
    qDebug() << "--============--";
    for (int i = 0; i < 8; ++i){
        state.clear();
        for (int j = 0; j < 8; ++j){
            piece *p = game->getPiece(boardPosition(j, i));
            if (p != nullptr){
                switch (p->getType()) {
                case piece::KING:
                    state += p->getColor() == piece::WHITE ? "K|" : "k|";
                    break;
                case piece::QUEEN:
                    state += p->getColor() == piece::WHITE ? "Q|" : "q|";
                    break;
                case piece::BISHOP:
                    state += p->getColor() == piece::WHITE ? "B|" : "b|";
                    break;
                case piece::KNIGHT:
                    state += p->getColor() == piece::WHITE ? "H|" : "h|";
                    break;
                case piece::ROOK:
                    state += p->getColor() == piece::WHITE ? "R|" : "r|";
                    break;
                case piece::PAWN:
                    state += p->getColor() == piece::WHITE ? "P|" : "p|";
                    break;
                default:
                    break;
                }
            }
            else{
                state +="_|";
            }
        }
        qDebug()<< state;
        res += "\n" + state;
    }
    return res;
}
