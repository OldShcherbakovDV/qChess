#include "chessplayer.h"

chessPlayer *chessPlayer::create(QString typeName)
{
    if (typeName == "AI"){
        return (chessPlayer*)(new AI());
    }
    else if (typeName == "human"){
        return (chessPlayer*)(new human());
    }
    return nullptr;
}

chessPlayer::~chessPlayer()
{

}

chessPlayer::chessPlayer() : lIsThinking(false), lIsHuman(false), lIsTrustworthy(false), lIsWhite(false)
{}



void human::newGame()
{
    qDebug() << "start";
}

void human::startGame()
{

}

void human::loadGame(const chessGameState &cgs)
{

}

void human::opponentMove(const boardMove &move, const chessGameState &cgs)
{

}

void human::think(const chessGameState &cgs)
{

}

bool human::needMove()
{

}

void human::undoMove()
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
