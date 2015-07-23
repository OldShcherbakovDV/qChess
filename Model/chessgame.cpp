#include "chessgame.h"

chessGame::chessGame() : player1(nullptr), player2(nullptr)
{

}

chessGame::chessGame(chessPlayer *p1, chessPlayer *p2) : player1(p1), player2(p2), lIsGameInProgress(true)
{
    p1->setIsWhite(true);
    p2->setIsWhite(false);
}

chessGame::~chessPlayer()
{
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
}

void chessGame::newGame()
{
    state.init();

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

