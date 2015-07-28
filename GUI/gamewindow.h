#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>


//самописные классы
#include "Model/chessgame.h"
#include "Model/options.h"
#include "Model/freefunctions.h"

namespace Ui {
class gameWindow;
}
/*!
 * \brief The gameWindow class - Класс игрового виджета
 */
class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(options *o, QWidget *p = 0);
    ~gameWindow();
    /*!
     * \brief paintBox - Отрисовать ячейку
     * \param bp - Позиция ячейки в модели
     * \param wantGoHere - Отобразить как возможный ход
     */
    void paintBox(const boardPosition &bp, bool wantGoHere = false);
    /*!
     * \brief paintBoard - Отрисовать всю доску
     */
    void paintBoard();
    /*!
     * \brief paintSet - Отрисовать набор ячеек
     * \param set - Набор координат в модели
     * \param wantGoHere - Отобразить как возможный ход
     */
    void paintSet(const QList<boardMove> &set, bool wantGoHere = false);
    /*!
     * \brief getUnicodPiece - Получить символ обозначающий фигуру
     * \param p - фигура
     * \return - Символ
     */
    QString getUnicodPiece(const piece &p) const;

private slots:
    /*!
     * \brief on_board_cellClicked - Слот вызывающийся по нажатию на ячейку виджета таблицы
     * \param y - Позиция по вертикали
     * \param x - Позиция по горизонтали
     */
    void on_board_cellClicked(int y, int x);
    /*!
     * \brief makeMove - Отобразить сделаный в модели ход
     * \param bm - Ход
     */
    void makeMove(boardMove bm);

private:
    /*!
     * \brief ui - Указатель на виджет
     */
    Ui::gameWindow *ui;
    /*!
     * \brief game - Указатель на игру
     */
    chessGame *game;
    /*!
     * \brief opts - конфигурации игры
     */
    options *opts;
    /*!
     * \brief lastGoodCurCell - последняя выбраная клетка с которой можно совершить ход
     */
    boardPosition lastGoodCurCell;
    /*!
     * \brief parrent - указатель на виджет родителя
     */
    QWidget *p;
};

#endif // GAMEWINDOW_H
