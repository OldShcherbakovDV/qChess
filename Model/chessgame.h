#ifndef CHESSGAME_H
#define CHESSGAME_H

//Библиотеки QT
#include <QObject>

//Самописные классы
#include "chessplayer.h"

/*!
 * \brief The chessGame class - класс партии
 */
class chessGame : public QObject
{
        Q_OBJECT
public:
    chessGame(QObject *parent = nullptr);
    /*!
     * \brief chessGame - конструктор для инициализации парой игроков
     * \param p1 - белый игрок
     * \param p2 - черный игрок
     */
    chessGame(chessPlayer *p1, chessPlayer *p2);
    /*!
     * \brief ~chessGame корректно разрушает объект
     */
    ~chessGame();
    /*!
     * \brief newGame - запускает новую игру
     */
    void newGame();
    /*!
     * \brief startGame - начинает новую партию
     */
    void startGame();
    /*!
     * \brief getPlayer2 - возвращает белого игрока
     * \return - указатель на игрока
     */
    inline chessPlayer* getPlayer1() const {  return player1; }
    /*!
     * \brief getPlayer2 - возвращает белого игрока
     * \return - указатель на игрока
     */
    inline chessPlayer* getPlayer2() const {  return player2; }
    /*!
     * \brief getCurrentPlayer - возвращает текущего игрока
     * \return - указатель на игрока
     */
    inline chessPlayer* getCurrentPlayer() const { return (state.isWhiteStep()) ? player1 : player2; }
    /*!
     * \brief getInactivePlayer - возвращает противоположного игрока
     * \return - указатель на игрока
     */
    inline chessPlayer* getInactivePlayer() const { return (state.isWhiteStep()) ? player2 : player1; }
    /*!
     * \brief getSate - получит описание игровой ситуации
     * \return - ситуация
     */
    inline chessGameState getSate() const { return state; }
    /*!
     * \brief getBoard - получить доску
     * \return - доска
     */
    inline board getBoard() const { return state.getBoard(); }
    /*!
     * \brief getColor - получить цвет текущего хода
     * \return цвет
     */
    inline piece::color getColor() const { return state.getColor(); }

    /*!
     * \brief undoMove - отменяет последний ход
     */
    void undoMove();
    /*!
     * \brief canCur - можно ли использовать эту позицию для начала хода
     * \param bp - позиция
     * \return - можо или нет
     */
    inline bool canCur(const boardPosition &bp) const { return getBoard().getPiece(bp) && getBoard().getPiece(bp)->getColor() == getColor(); }
    bool cantStep;

public slots:
    /*!
     * \brief tryMove - попытаться сделать ход
     * \param bm - ход
     * \return - успешность попытки
     */
    bool tryMove(const boardMove &bm);
    void tM1();
    void tM2();
signals:
    /*!
     * \brief madeMove - Был совершен ход
     * \param bm - Ход который был совершен
     */
    void madeMove(boardMove bm);
private:
    /*!
     * \brief player1 - Указатель на белого игрока
     */
    chessPlayer *player1;
    /*!
     * \brief player2 - Указатель на черного игрока
     */
    chessPlayer *player2;
    /*!
     * \brief state - Состояние игры
     */
    chessGameState state;
    /*!
     * \brief history - История состояний
     */
    QList<chessGameState> history;
    /*!
     * \brief redo - Список отмененых ходов
     */
    QList<chessGameState> redo;
    /*!
     * \brief lIsGameInProgress - Идет ли игра?
     */
    bool lIsGameInProgress;
};

#endif // CHESSGAME_H
