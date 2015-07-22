#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H

/*!
 * \brief The boardPosition class - класс которы описывает позицию на доске
 */
class boardPosition
{
public:
    /*!
     * \brief boardPosition - будет получена позиция (-1,-1)
     */
    boardPosition();
    /*!
     * \brief boardPosition - конструктор по координатам
     * \param x - горизонтальная (от 0 клетки)
     * \param y - вертикальна (от 0 клетки)
     */
    boardPosition(const int &x, const int &y);
    /*!
     * \brief boardPosition - конструктор из классического шахматного обозначения тип а1 и т.д.
     * \param x - координата маленькой латинской буквой
     * \param y - вертикальная координата
     */
    boardPosition(const char &x, const int &y);
    /*!
     * \brief boardPosition - конструктор из номера позиции номер определяется формулой : y*8 + x
     * \param number - номер
     */
    boardPosition(const int number);

    // Методы доступа

    /*!
     * \brief x - вернуть Х
     * \return Х
     */
    inline int x() const { return lX; }
    /*!
     * \brief y - вернуть Y
     * \return Y
     */
    inline int y() const { return lY; }
    /*!
     * \brief number - возвращает номер позиции
     * \return номер
     */
    inline int number() const { return (8*lY - lX); }
    /*!
     * \brief xToChar - вернуть Х  в виде символа
     * \return Х
     */
    inline char xToChar() const { return lX + 'a'; }
    /*!
     * \brief xToNumber - вернуть Х  в виде позиции от 1
     * \return Х
     */
    inline char xToNumber() const { return lX + 1; }
    /*!
     * \brief yToNumber - вернуть Y в виде позиции от 1
     * \return Y
     */
    inline int yToNumber() const { return lY + 1; }
    /*!
     * \brief setX - задает горизонтальную позицию по координате
     * \param x - координата
     */
    inline void setX(const int &x) { lX = x; }
    /*!
     * \brief setX - Задает горизонтальную позицию по букве
     * \param x - позиция латинской буквой
     */
    inline void setX(const char &x) { lX = x - 'a'; }
    /*!
     * \brief setY - Задвет позицию по вертикале
     * \param у - позиция
     */
    inline void setY(const int &y) { lY = y; }
    /*!
     * \brief setNuber - задает координаты из номера позиции номер определяется формулой : x*8 + y
     * \param number - номер
     */
    inline void setNuber(const int &number) { lX = number % 8; lY = number / 8; }
    /*!
     * \brief - setInvalidData задает координаты не принадлежащие доске
     */
    inline void setInvalidData() { lX = -1; lY = -1; }

    // Методы работы с классом

    /*!
     * \brief isValid - проверяет является ли данная позиция позицией доски
     * \return является ли данная позиция позицией доски
     */
    inline bool isValid() const { return (lX >= 0 && lX < 8 && lY >= 0 && lY < 8); }

    /*!
     * \brief getRight - возвращает значение позиции на одну клетку правее
     * \return
     */
    inline boardPosition getRight() const { return boardPosition(lX + 1, lY); }
    /*!
     * \brief getRightTop - возвращает значение позиции на одну клетку правее и выше
     * \return
     */
    inline boardPosition getRightTop() const { return boardPosition(lX + 1, lY + 1); }
    /*!
     * \brief getTop - - возвращает значение позиции на одну клетку выше
     * \return
     */
    inline boardPosition getTop() const { return boardPosition(lX, lY + 1); }
    /*!
     * \brief getLeftTop - - возвращает значение позиции на одну клетку левее и выше
     * \return
     */
    inline boardPosition getLeftTop() const { return boardPosition(lX - 1, lY + 1); }
    /*!
     * \brief getLeft - возвращает значение позиции на одну клетку левее
     * \return
     */
    inline boardPosition getLeft() const { return boardPosition(lX - 1, lY); }
    /*!
     * \brief getLeftBottom - возвращает значение позиции на одну клетку левее и ниже
     * \return
     */
    inline boardPosition getLeftBottom() const { return boardPosition(lX - 1, lY - 1); }
    /*!
     * \brief getBottom - возвращает значение позиции на одну клетку ниже
     * \return
     */
    inline boardPosition getBottom() const { return boardPosition(lX, lY - 1); }
    /*!
     * \brief getRightBottom- возвращает значение позиции на одну клетку правее ниже
     * \return
     */
    inline boardPosition getRightBottom() const { return boardPosition(lX + 1, lY - 1); }

    inline bool operator == (const boardPosition &other) const { return (lX == other.lX && lY == other.lY); }
    inline bool operator != (const boardPosition &other) const { return !(*this == other); }
private:
    int lX;
    int lY;
};

#endif // BOARDPOSITION_H
