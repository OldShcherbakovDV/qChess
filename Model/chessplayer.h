#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

//Самописные классы
#include "chessgamestate.h"

/*!
 * \brief The chessPlayer class - абстрактный класс игрока
 */
class chessPlayer
{
public:

   chessPlayer();

   virtual ~chessPlayer() = 0;

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

   virtual void sendMove(const boardMove &bm) = 0;

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

   bool lIsWhite;
   bool lIsThinking;
   bool lIsHuman;
   bool lIsTrustworthy;
   boardMove lMove;
};

#endif // CHESSPLAYER_H
