#ifndef BOARD_H
#define BOARD_H

//Библиотеки QT
#include <QList>

#include "bitboard.h"
#include "boardmove.h"

class board
{
public:
    /*!
     * \brief board - конструктор по умолчанию создает c фигурами в стартовой позиции
     */
    board();
    ~board();

    /*!
     * \brief setDefault - задает внутренние значения в исходное состояние
     */
    void setDefault();
    /*!
     * \brief setupPieces - раставляет заново фигуры на доску
     */
    void resetupPieces();
    /*!
     * \brief getPiece - возвращает фигуру из заданной позиции
     * \param bp - позиция
     * \return - указатель на фигуру
     */
    piece *getPiece(const boardPosition &bp) const;
    /*!
     * \brief setPiece
     * \param p
     * \param bp
     */
    void setPiece(piece *p, const boardPosition &bp);
    /*!
     * \brief removePiece - удаляет фигуру с доски
     * \param bp - удаляет фигуру из заданой позиции
     */
    void removePiece(const boardPosition &bp);
    /*!
     * \brief isPathClear - проверяет есть ли на пути другие фигуры
     * \param bm - ход
     * \return свободен ли путь
     */
    bool isPathClear(const boardMove &bm) const;
    /*!
     * \brief isOccupied - проверяет является ли клетка занятой
     * \param bp - позиция клетки
     * \return занята ли клетка
     */
    bool isOccupied(const boardPosition &bp) const;

    QList<boardMove> getLegalMoves (const boardPosition &bp) const;

private:
    static piece *allPieces[2][6]; //Указатель на фигуру каждого типа
    static bool isSetup;

    int lTotalPiece[2];     //Полное количество фигур цвета
    int lPieceCount[2][6];  //количество фигур данного типа и цвета

    mask lPieces[6];        //Маска доски по типам фигур
    mask lColors[2];        //Маска доски по цветам фигур
    mask lCastlingFlags;    //Маска доски по допустимым ракировкам
    mask lEnpassling;

    boardPosition kingsPos[2]; //Позиции королей
};

#endif // BOARD_H
