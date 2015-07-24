#include "chessgame.h"

chessGame::chessGame(QObject *parent) : player1(nullptr), player2(nullptr)
{

}

chessGame::chessGame(chessPlayer *p1, chessPlayer *p2) : lIsGameInProgress(true)
{
    player1 = p1;
    player2 = p2;
    player1->setIsWhite(true);
    player2->setIsWhite(false);
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

void chessGame::loadGame(const chessGameState &cgs)
{
    player1->loadGame(cgs);
    player2->loadGame(cgs);
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

        if (!getCurrentPlayer()->isHuman()){
            getCurrentPlayer()->think(state);
            tryMove(getCurrentPlayer()->getMove());
        }
    }
    return false;
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

