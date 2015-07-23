#include "chessplayer.h"

chessPlayer *chessPlayer::create(QString typeName)
{
    if (typeName == "AI"){
        return (chessPlayer*)(new AI());
    }
    else if (typeName == "humen"){
        return (chessPlayer*)(new humen());
    }
    return nullptr;
}

chessPlayer::~chessPlayer()
{

}

chessPlayer::chessPlayer() : lIsThinking(false), lIsHuman(false), lIsTrustworthy(false), lIsWhite(false)
{}



void humen::newGame()
{

}

void humen::startGame()
{

}

void humen::loadGame(const chessGameState &cgs)
{

}

void humen::opponentMove(const boardMove &move, const chessGameState &cgs)
{

}

void humen::think(const chessGameState &cgs)
{

}

bool humen::needMove()
{

}

void humen::undoMove()
{

}

void AI::newGame()
{

}

void AI::startGame()
{

}

void AI::loadGame(const chessGameState &cgs)
{

}

void AI::opponentMove(const boardMove &move, const chessGameState &cgs)
{

}

void AI::think(const chessGameState &cgs)
{

}

bool AI::needMove()
{

}

void AI::undoMove()
{

}
