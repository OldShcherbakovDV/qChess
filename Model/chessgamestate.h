#ifndef CHESSGAMESTATE_H
#define CHESSGAMESTATE_H

//Библиотеки QT
#include <QPair>

//Самописные классы
#include "board.h"

class chessGameState
{
public:
    chessGameState();
    /*!
     * \brief init - приводит игровую статистику к стартовому состаянию
     */
    void init();
    /*!
     * \brief makeMove - сделать ход
     * \param bm - ход
     */
    void makeMove(const boardMove &bm);
    /*!
     * \brief getBoard - получить доску
     * \return доска
     */
    inline board getBoard() const { return lBoard; }
    /*!
     * \brief getLastMove - получить последний совершенный ход
     * \return - ход
     */
    inline boardMove getLastMove() const { return lLastMove; }
    /*!
     * \brief getStepNumber - получить номер хода
     * \return номер хода
     */
    inline int getStepNumber() const { return lStepNumber; }
    /*!
     * \brief isChek - шах на доске
     * \return является ли положение шаховым
     */
    inline bool isChek() const { return lIsCheck; }
    /*!
      * \brief isWhiteStep - какой цвет сходил в последний раз
      * \return - был ли это белый цвет?
      */
     inline bool isWhiteStep() const { return lIsWhiteStep; }
     /*!
      * \brief getColor - вернуть цвет хода
      * \return цвет
      */
     inline piece::color getColor() const { return (lIsWhiteStep) ? piece::WHITE : piece::BLACK; }
     /*!
      * \brief isPositionSelectable - можно ли эту клетку
      * \param bp - позиция
      * \return можно ли
      */
     bool isPositionSelectable(const boardPosition& bp) const;
private:
    QList<QPair<serialBoard, int> > lThreefoldCount; // История "бесполезных" ходов
    piece* lPieces[64]; // Фигуры на 'хеше'
    board lBoard; // Доска
    boardMove lLastMove; // последний сделаный ход
    bool lIsWhiteStep, lIsCheck, isThreefold; // Цвет, шах, удавлетворяет ли ход правилу 50 ходов
    int lStepNumber, l50Moves; // Номер хода, Счетчик для правила 50 ходов
};

#endif // CHESSGAMESTATE_H
