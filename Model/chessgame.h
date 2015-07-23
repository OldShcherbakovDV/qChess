#ifndef CHESSGAME_H
#define CHESSGAME_H

//Самописные классы
#include "chessplayer.h"

/*!
 * \brief The chessGame class - класс партии
 */
class chessGame
{
public:
    chessGame();
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
     * \brief loadGame - загружает игру
     * \param cgs - состояние игры
     */
    void loadGame(const chessGameState &cgs);
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
    inline piece::color getColor() { return state.getColor(); }
    /*!
     * \brief tryMove - попытаться сделать ход
     * \param bm - ход
     * \return - успешность попытки
     */
    bool tryMove(const boardMove &bm);
    /*!
     * \brief undoMove - отменяет последний ход
     */
    void undoMove();

private:
    chessPlayer *player1;
    chessPlayer *player2;
    chessGameState state;

    QList<chessGameState> history;
    QList<chessGameState> redo;

    bool lIsGameInProgress;
};

#endif // CHESSGAME_H
