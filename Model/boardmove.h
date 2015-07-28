#ifndef BOARDMOVE_H
#define BOARDMOVE_H

//Самописные классы
#include "boardposition.h"
#include "piece.h"

/*!
 * \brief The boardMove class - класс игрового хода
 */
class boardMove
{
public:
    /*!
     * \brief boardMove - конструктор по умолчанию
     */
    boardMove();
    /*!
     * \brief boardMove - конструктор по параметрам
     * \param start - позиция начала хода
     * \param end - позиция конца хода
     * \param moved - фигура которая ходит
     * \param promote - тип вигуры в поле замены пешки
     */
    boardMove(const boardPosition &start, const boardPosition &end, piece *moved, piece::type promote = piece::QUEEN);

    // Методы доступа
    /*!
     * \brief start - вернуть стартовую позицию
     * \return - стартовая позиция
     */
    inline boardPosition getStart() const { return lStart; }
    /*!
     * \brief end - вернуть конечную позицию
     * \return конечная позиция
     */
    inline boardPosition getEnd() const { return lEnd; }
    /*!
     * \brief getMovedPiece - вернуть фигуру
     * \return - указатель на фигуру
     */
    inline piece *getMovedPiece() const { return lMovedPiece; }
    /*!
     * \brief getPromote - возвращает тип фигуры в поле end
     * \return тип фигуры
     */
    inline piece::type getPromote() const { return lPromote; }
    /*!
     * \brief setPromote - задает тип получаемой фигуры
     * \param t - тип получаемой фигуры
     */
    inline void setPromote(const piece::type &t) { lPromote = t; }

    // Методы работы с классом
    /*!
     * \brief needPromotion - необходимо ли задать тип замена
     * \return
     */
    bool needPromotion(const QList<boardMove> &legals) const;
    /*!
     * \brief isLegal - проверяет можно ли произвести такой ход
     * \return
     */
    bool isLegal(const QList<boardMove> &legals) const;

    /*!
     * \brief yDiff - Изменение положение по вертикали
     * \return - Разница между начальным и конечным положением по Y
     */
    inline int yDiff() const { return abs(lStart.y() - lEnd.y()); }
    /*!
     * \brief xDiff - Изменение положение по горизонтали
     * \return - Разница между начальным и конечным положением по X
     */
    inline int xDiff() const { return abs(lStart.x() - lEnd.x()); }
    /*!
     * \brief operator == - Оператор сравнения ходов
     * \param other - Ход с которым сравниваем
     * \return - Равны ли?
     */
    inline bool operator == (const boardMove &other) const { return (lStart == other.lStart && lEnd == other.lEnd && lMovedPiece == other.lMovedPiece && lPromote == other.lPromote); }
private:
    /*!
     * \brief lStart - Позиция начала хода
     */
    boardPosition lStart;
    /*!
     * \brief lEnd - Позиция конца хода
     */
    boardPosition lEnd;
    /*!
     * \brief lMovedPiece - Фигура, совершающая ход
     */
    piece *lMovedPiece;
    /*!
     * \brief lPromote -  Тип фигуры которую хоти получить из пешки
     */
    piece::type lPromote;

};

#endif // BOARDMOVE_H
