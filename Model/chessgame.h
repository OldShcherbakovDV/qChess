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
     * \brief getPlaer1 - возвращает белого игрока
     */
    inline chessPlayer* getPlaer1() const {  return player1; }
    /*!
     * \brief getPlaer2 - возвращает белого игрока
     */
    inline chessPlayer* getPlaer2() const {  return player2; }
private:
    chessPlayer *player1;
    chessPlayer *player2;
    chessGameState state;

    QList<chessGameState> history;
    QList<chessGameState> redo;

    bool lIsGameInProgress;
};

#endif // CHESSGAME_H
