#ifndef OPTIONS_H
#define OPTIONS_H

//Библиотеки Qt
#include <QString>
#include <QColor>

class options
{
public:
    options();

    inline QString getPlayer1() const { return player1; }
    inline QString getPlayer2() const { return player2; }
    inline QColor  getBlackPiece() const { return blackPiece; }
    inline QColor  getWhitePiece() const { return whitePiece; }
    inline QColor  getBlackCell() const { return blackCell; }
    inline QColor  getWhiteCell() const { return whiteCell; }
    inline QColor  getBlackCellAttacked() const { return blackCellAttacked; }
    inline QColor  getWhiteCellAttacked() const { return whiteCellAttacked; }
    inline QColor  getBlackCellCanMove() const { return blackCellCanMove; }
    inline QColor  getWhiteCellCanMove() const { return whiteCellCanMove; }
    inline QColor  getDeadCell() const { return deadCell; }

private:
    // Игровые настройки
    QString player1;
    QString player2;
    QColor  blackPiece, whitePiece;
    QColor  blackCell, whiteCell;
    QColor  blackCellAttacked, whiteCellAttacked;
    QColor  blackCellCanMove, whiteCellCanMove;
    QColor  deadCell;
};

#endif // OPTIONS_H
