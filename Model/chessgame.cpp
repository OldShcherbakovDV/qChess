#include "chessgame.h"

chessGame::chessGame(QObject *parent) : QObject(parent), player1(nullptr), player2(nullptr)
{

}

chessGame::chessGame(chessPlayer *p1, chessPlayer *p2) : lIsGameInProgress(true)
{
    player1 = p1;
    player2 = p2;
    player1->setIsWhite(true);
    player2->setIsWhite(false);
    if (!player1->isHuman())
        connect(player1, SIGNAL(haveMove()), this, SLOT(tM1()));
    if (!player2->isHuman())
        connect(player2, SIGNAL(haveMove()), this, SLOT(tM2()));
    cantStep = !player1->isHuman();
    player1->think(state);
}

chessGame::~chessGame()
{
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
}

void chessGame::newGame()
{
    //state.init();

    lIsGameInProgress = false;
    player1->newGame();
    player2->newGame();

    history.clear();
    redo.clear();

}

void chessGame::startGame()
{
    player1->startGame();
    player2->startGame();
    lIsGameInProgress = true;
}

bool chessGame::tryMove(const boardMove &bm)
{
    if (bm.isLegal(getBoard().getLegalMoves(bm.getStart()))){
        state.makeMove(bm);

        history.append(state);
        redo.clear();

        emit madeMove(bm);

        cantStep = !getCurrentPlayer()->isHuman();
        if (cantStep){
            getCurrentPlayer()->think(state);
        }
    }
    return false;
}

void chessGame::tM1()
{
    tryMove(player1->getMove());
}

void chessGame::tM2()
{
    tryMove(player2->getMove());
}

void chessGame::undoMove()
{
    if (!history.isEmpty()){
        redo.append(history.takeLast());
        state = redo.last();
    }
    player1->undoMove();
    player2->undoMove();
}

