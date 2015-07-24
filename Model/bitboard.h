#ifndef BITBOARD_H
#define BITBOARD_H

//Самописные классы
#include "boardposition.h"

typedef unsigned long long mask;
/*!
 * \brief The bitBoard class - побитовая карта доски. (т.к. тип unsigned long long содержит 64 бита, что равно кол ву полей на доске)
 */
class bitBoard
{
public:
    /*!
     * \brief bitBoard - конструктор в результате которого все биты опущены
     */
    bitBoard();

    /*!
     * \brief bitBoard - конструктор который копирует исходную битовую маску
     * \param board - битовая маска
     */
    bitBoard(const unsigned long long & board);
    // Методы доступа
    /*!
     * \brief setBit - устанавливает бит в заданной позиции в поднятое положение
     * \param bp - позиция
     */
    void setBit(const boardPosition &bp);
    /*!
     * \brief unsetBit - устанавливает бит в заданной позиции в опущенное положение
     * \param bp - позиция
     */
    void unsetBit(const boardPosition &bp);
    /*!
     * \brief invert - переворачивает все биты доски
     */
    void invert();
    /*!
     * \brief getBoard - вернуть битовую маску
     * \return  - битовая маска
     */
    inline unsigned long long getBoard() const { return lBoard; }

    // Методы работы с классом
    /*!
     * \brief getXMask - вернет все битовую маску для всех позицы с координатой х равной bp.x()
     * \param bp - текущая позиция
     * \return - битовая маска
     */
    static unsigned long long getXMask(const boardPosition & bp);
    /*!
     * \brief getYMask - вернет все битовую маску для всех позицы с координатой y равной bp.x()
     * \param bp - текущая позиция
     * \return - битовая маска
     */
    static unsigned long long getYMask(const boardPosition & bp);
    /*!
     * \brief getMask - возвращает маску заданного бита
     * \param bp - позиция бита
     * \return маска где понят или опущен необходимый бит, остальные опущены
     */
    static unsigned long long getMask(const boardPosition & bp);


private:
    unsigned long long lBoard;
};

#endif // BITBOARD_H
