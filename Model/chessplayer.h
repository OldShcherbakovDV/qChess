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
        lIsHuman = false;
        lIsTrustworthy = true;
        lPly = 1;
    }

    virtual void newGame();

    virtual void startGame();

    virtual void loadGame(const chessGameState &cgs);

    virtual void opponentMove(const boardMove &move, const chessGameState &cgs);

    virtual void think(const chessGameState &cgs);

    virtual bool needMove();

    virtual void undoMove();

    int getPly() { return lPly; }
    void setPly(int ply) { lPly = ply; }

protected:
    int evaluateBoard(const board & b, piece::color c);
    int search(board b, piece::color c, int depth, int alpha, int beta, boardMove& bm);
    int pawnBonus(const boardPosition & bp, const board & b,  piece::color turn, bool endgame);
    int knightBonus(const boardPosition & bp, const board & b,  piece::color turn, bool endgame);
    int bishopBonus(const boardPosition & bp, const board & b,  piece::color turn, bool endgame);
    int rookBonus(const boardPosition & bp, const board & b,  piece::color turn, bool endgame);
    int queenBonus(const boardPosition & bp, const board & b,  piece::color turn, bool endgame);
    int kingBonus(const boardPosition & bp, const board & b,  piece::color turn, bool endgame);

    int numAttackedSquares(const mask & pieceAttacks);

    bool isIsolatedPawn(const boardPosition & bp, const board & b);
    bool isDoubledPawn(const boardPosition & bp, const board & b);

    // Used to calculate positional bonuses
    static int m_bishop[64];
    static int m_knight[64];
    static int m_wpawn[64];
    static int m_bpawn[64];
    static int m_wking[64];
    static int m_bking[64];
    static int m_end_king[64];

    int lPly;
};

#endif // CHESSPLAYER_H
