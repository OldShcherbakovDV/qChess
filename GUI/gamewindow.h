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

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = 0);
    ~gameWindow();
    void paintBox(const boardPosition &bp, bool wantGoHere = false);
    void paintBoard();
    void paintSet(const QList<boardMove> &set, bool wantGoHere = false);
    QString getUnicodPiece(const piece &p) const;

private slots:
    void on_board_cellClicked(int y, int x);
    void makeMove(boardMove bm);

private:
    Ui::gameWindow *ui;
    chessGame *game;
    options *opts;
    boardPosition lastGoodCurCell;
};

#endif // GAMEWINDOW_H
