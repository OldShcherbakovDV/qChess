#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

//Библиотеки QT
#include <QString>
#include <QDebug>

//Самописные классы
#include "chessgamestate.h"

/*!
 * \brief The chessPlayer class - абстрактный класс игрока
 */
class chessPlayer
{
public:

   static chessPlayer *create(QString typeName);

   virtual ~chessPlayer();

   virtual void newGame() = 0;

   virtual void startGame() = 0;

   virtual void loadGame(const chessGameState &cgs) = 0;

   virtual void opponentMove(const boardMove &move, const chessGameState &cgs) = 0;

   inline bool isThinking() const
       { return lIsThinking; }

   inline bool isHuman() const
       { return lIsHuman; }

   virtual void think(const chessGameState &cgs) = 0;

   inline boardMove getMove()
       { return lMove; }

   inline void interruptThinking()
       { lIsThinking = false; }

   virtual bool needMove() = 0;

   inline void sendMove(const boardMove &bm) { lMove = bm; }

   virtual void undoMove() = 0;

   inline void setIsWhite(bool isWhite)
       { lIsWhite = isWhite; }

   inline bool isWhite() const
       { return lIsWhite; }

   inline bool isTrustworthy() const
       { return lIsTrustworthy; }

   inline piece::color getColor() const
       { return (lIsWhite ? piece::WHITE : piece::BLACK); }

protected:
   chessPlayer();

   bool lIsWhite;
   bool lIsThinking;
   bool lIsHuman;
   bool lIsTrustworthy;
   boardMove lMove;
};

/*!
 * \brief The human class - описывает игрока человека
 */
class human : private chessPlayer {
public:
    human(){
        lIsThinking = false;
        lIsHuman = true;
        lIsTrustworthy = true;
        lIsWhite = true;
    }

    virtual void newGame();

    virtual void startGame();

    virtual void loadGame(const chessGameState &cgs);

    virtual void opponentMove(const boardMove &move, const chessGameState &cgs);

    virtual void think(const chessGameState &cgs);

    virtual bool needMove();

    virtual void undoMove();

};
/*!
 * \brief The AI class - описывает игрока искуственного интелекта
 */
class AI : private chessPlayer {
public:
    AI(){

    }

    virtual void newGame();

    virtual void startGame();

    virtual void loadGame(const chessGameState &cgs);

    virtual void opponentMove(const boardMove &move, const chessGameState &cgs);

    virtual void think(const chessGameState &cgs);

    virtual bool needMove();

    virtual void undoMove();
};

#endif // CHESSPLAYER_H
