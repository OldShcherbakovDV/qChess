#include "gamewindow.h"
#include "ui_gamewindow.h"

gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    //Инициализация игрового процесса
    opts = new options;
    game = new chessGame(chessPlayer::create(opts->getPlayer1()), chessPlayer::create(opts->getPlayer2()));
    game->newGame();
    game->startGame();

    //Инициализация таблици
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            ui->board->setItem(i,j, new QTableWidgetItem);
        }
    }
    paintBoard();

    connect(game, SIGNAL(madeMove(boardMove)), this, SLOT(makeMove(boardMove)));



}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::paintBox(const boardPosition &bp, bool wantGoHere)
{
    QTableWidgetItem * cell = ui->board->item(7 - bp.y(),bp.x());
    cell->setTextAlignment(Qt::AlignCenter);
    bool isWhite = ((bp.x() + bp.y())%2 != 0);
    if (wantGoHere){
        cell->setBackgroundColor( isWhite ? opts->getWhiteCellCanMove() : opts->getBlackCellCanMove());
    }
    else{
        cell->setBackgroundColor( isWhite ? opts->getWhiteCell() : opts->getBlackCell());
    }
    piece *p = game->getBoard().getPiece(bp);
    if (p != nullptr){
        cell->setText(getUnicodPiece(*p));
        cell->setTextColor( (p->getColor() == piece::WHITE) ? opts->getWhitePiece() : opts->getBlackPiece());
        if (wantGoHere){
            cell->setBackgroundColor( isWhite ? opts->getWhiteCellAttacked() : opts->getBlackCellAttacked());
        }
    }
    else{
        cell->setText("");
    }
}

void gameWindow::paintBoard()
{
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            paintBox(boardPosition(i,j));
        }
    }
}

void gameWindow::paintSet(const QList<boardMove> &set, bool wantGoHere)
{
    boardMove bm;
    foreach (bm, set) {
        paintBox(bm.getEnd(), wantGoHere);
    }
}

QString gameWindow::getUnicodPiece(const piece &p) const
{
    switch (p.getType()) {
    case piece::PAWN:
        return "♟";
    case piece::ROOK:
        return "♖";
    case piece::BISHOP:
        return "♗";
    case piece::KNIGHT:
        return "♘";
    case piece::QUEEN:
        return "♕";
    case piece::KING:
        return "♚";
    default:
        break;
    }
    return 0;
}

void gameWindow::on_board_cellClicked(int y, int x)
{
    boardPosition curCell(x, 7 - y);
    if (game->canCur(curCell)){
        lastGoodCurCell = curCell;
        paintSet(game->getBoard().getLegalMoves(lastGoodCurCell), true);
    }
    else if (lastGoodCurCell.isValid()){
        boardMove bm(lastGoodCurCell, curCell, game->getBoard().getPiece(lastGoodCurCell));
        if (bm.isLegal(game->getBoard().getLegalMoves(lastGoodCurCell))){
            paintSet(game->getBoard().getLegalMoves(lastGoodCurCell));
            lastGoodCurCell.setInvalidData();
            ui->board->setCurrentCell(8,8);
            game->tryMove(bm);
        }
    }
    else{
        ui->board->setCurrentCell(8,8);
    }
}

void gameWindow::makeMove(boardMove bm)
{
    paintBox(bm.getStart());
    if (!ui->board->item(7 - bm.getEnd().y(), bm.getEnd().x())->text().isEmpty()){
        QTableWidget *t = (game->getColor() == piece::WHITE) ? ui->white :ui->black;
        t->insertRow(0);
        t->setItem(0,0, new QTableWidgetItem(*ui->board->item(7 - bm.getEnd().y(), bm.getEnd().x())));
        t->item(0,0)->setBackground(opts->getDeadCell());
    }
    paintBox(bm.getEnd());
    if (bm.getMovedPiece()->getType() == piece::KING || bm.getMovedPiece()->getType() == piece::PAWN){
        paintBoard();
    }
    //Обнавляем запись в заголовке
    ui->step->setText("Ход №"+QString::number(1+ (game->getSate().getStepNumber() - 1)*2 + (game->getSate().isWhiteStep() ? 0 : 1))+".");
    ui->color->setText(game->getSate().isWhiteStep() ? "Ходят белые." : "Ходят черные.");
    if (game->getSate().getBoard().isMate(game->getColor())){
        ui->sit->setText("Мат " + (game->getSate().isWhiteStep() ? QString("белым."): QString("черным.")));
    }
    else if (game->getSate().getBoard().isCheck(game->getColor())){
        ui->sit->setText("Шах " + (game->getSate().isWhiteStep() ? QString("белым.") : QString("черным.")));
    }
    else if (game->getSate().getBoard().isStalemate(game->getColor())){
        ui->sit->setText("Пат " + (game->getSate().isWhiteStep() ? QString("белым.") : QString("черным.")));
    }
    else{
        ui->sit->clear();
    }
}
