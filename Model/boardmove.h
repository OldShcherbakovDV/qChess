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
    boardMove(const boardPosition &start, const boardPosition &end, piece *moved, piece::type promote = piece::NOTYPE);

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

    inline bool operator == (const boardMove &other) const { return (lStart == other.lStart && lEnd == other.lEnd && lMovedPiece == other.lMovedPiece && lPromote == other.lPromote); }
private:
    boardPosition lStart; // Начало хода
    boardPosition lEnd;   // Конец хода
    piece *lMovedPiece;   // Фигура которая ходит
    piece::type lPromote; // Тип фигуры которую хоти получить из пешки

};

#endif // BOARDMOVE_H
