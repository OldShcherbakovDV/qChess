#ifndef OPTIONS_H
#define OPTIONS_H

//Библиотеки Qt
#include <QString>
#include <QColor>

/*!
 * \brief The options class - класс конфигураций (содержит все конфигурации программы)
 */
class options
{
public:
    /*!
     * \brief options - Конструктор по умолчанию (в результате получается игра с параметрами по умолчанию)
     */
    options();
    /*!
     * \brief getPlayer1 - Получить имя класса белого игрока
     * \return имя класса (Например: "AI" или "humen");
     */
    inline QString getPlayer1() const { return player1; }
    /*!
     * \brief getPlayer2 - Получить имя класса белого игрока
     * \return имя класса (Например: "AI" или "humen");
     */
    inline QString getPlayer2() const { return player2; }
    /*!
     * \brief getBlackPiece - Получить цвет черных фигур
     * \return цвет
     */
    inline QColor  getBlackPiece() const { return blackPiece; }
    /*!
     * \brief getWhitePiece - Получить цвет белых фигур
     * \return цвет
     */
    inline QColor  getWhitePiece() const { return whitePiece; }
    /*!
     * \brief getBlackCell - Получить цвет черных клеток
     * \return цвет
     */
    inline QColor  getBlackCell() const { return blackCell; }
    /*!
     * \brief getWhiteCell - Получить цвет белых клеток
     * \return цвет
     */
    inline QColor  getWhiteCell() const { return whiteCell; }
    /*!
     * \brief getBlackCellAttacked - Получить цвет черных клеток во время атаки
     * \return цвет
     */
    inline QColor  getBlackCellAttacked() const { return blackCellAttacked; }
    /*!
     * \brief getWhiteCellAttacked - Получить цвет белых клеток во время атаки
     * \return цвет
     */
    inline QColor  getWhiteCellAttacked() const { return whiteCellAttacked; }
    /*!
     * \brief getBlackCellCanMove - Получить цвет черных клеток на которые можно сделать ход
     * \return цвет
     */
    inline QColor  getBlackCellCanMove() const { return blackCellCanMove; }
    /*!
     * \brief getWhiteCellCanMove - Получить цвет белых клеток на которые можно сделать ход
     * \return цвет
     */
    inline QColor  getWhiteCellCanMove() const { return whiteCellCanMove; }
    /*!
     * \brief getBlackPiece - Получить цвет клеток мертвых фигур
     * \return цвет
     */
    inline QColor  getDeadCell() const { return deadCell; }
    /*!
     * \brief getAiCof1 - получить коофициент сложности белого игрока
     * \return коофициент от 1 до 3
     */
    inline int  getAiCof1() const { return aiCof1; }
    /*!
     * \brief getAiCof1 - получить коофициент сложности черного игрока
     * \return коофициент от 1 до 3
     */
    inline int  getAiCof2() const { return aiCof2; }
    /*!
     * \brief setAiCof1 - задать коофициент сложности белого игрока
     * \param c - коофициент от 1 до 3
     */
    inline void setAiCof1(int c) { aiCof1 = c; }
    /*!
     * \brief setAiCof2 - задать коофициент сложности белого игрока
     * \param c - коофициент от 1 до 3
     */
    inline void setAiCof2(int c) { aiCof2 = c; }
    /*!
     * \brief setPlayer1 - задать тип белого игрока
     * \param p - имя типа строкой
     */
    inline void setPlayer1(QString p) { player1 = p; }
    /*!
     * \brief setPlayer2 - задать тип черного игрока
     * \param p - имя типа строкой
     */
    inline void setPlayer2(QString p) { player2 = p; }
private:
    // Игровые настройки
    /*!
     * \brief player1 - Имя класса игрока управляющего белыми фигурами
     */
    QString player1;
    /*!
     * \brief player2 - Имя класса игрока управляющего белыми фигурами
     */
    QString player2;
    /*!
     * \brief blackPiece - Цвет черных фигур
     */
    QColor  blackPiece;
    /*!
     * \brief whitePiece - Цвет белых фигур
     */
    QColor  whitePiece;
    /*!
     * \brief blackCell - Цвет черных клеток поля
     */
    QColor  blackCell;
    /*!
     * \brief whiteCell - Цвет белых клеток поля
     */
    QColor  whiteCell;
    /*!
     * \brief blackCellAttacked - Цвет черных клеток поля во время атаки на них
     */
    QColor  blackCellAttacked;
    /*!
     * \brief whiteCellAttacked - Цвет белых клеток поля во время атаки на них
     */
    QColor  whiteCellAttacked;
    /*!
     * \brief blackCellCanMove - Цвет черных клеток если на них можно сходить
     */
    QColor  blackCellCanMove;
    /*!
     * \brief whiteCellCanMove - Цвет белых клеток если на них можно сходить
     */
    QColor  whiteCellCanMove;
    /*!
     * \brief deadCell - Цвет поля мертвой фигуры
     */
    QColor  deadCell;
    /*!
     * \brief aiCof1 - коофициент сложности ИИ белого игрока
     */
    int aiCof1;
    /*!
     * \brief aiCof2 - коофициент сложности ИИ черного игрока
     */
    int aiCof2;
};

#endif // OPTIONS_H
