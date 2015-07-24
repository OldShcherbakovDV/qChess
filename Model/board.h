#ifndef BOARD_H
#define BOARD_H

//Библиотеки QT
#include <QList>

//Самописные классы
#include "bitboard.h"
#include "boardmove.h"
/*!
 * \brief The serialBoard struct - упращенная структура представления доски
 */
struct serialBoard {
    mask pieces[6];
    mask color[2];
    union {
        int allFlags;
        struct {
            int whiteEnpassant:8;
            int blackEnpassant:8;
            int whiteTurn:1;
            int wkCastling:1;
            int wqCastling:1;
            int bkCastling:1;
            int bqCastling:1;
            int:11;
        };
    };
};
/*!
 * \brief isEquivalent - сравнивает доски
 * \param a - первая доска
 * \param b - вторая доска
 * \return равны ли доски
 */
bool isEquivalent (const serialBoard &a, const serialBoard &b);

class board
{
public:
    /*!
     * \brief board - конструктор по умолчанию создает c фигурами в стартовой позиции
     */
    board();
    ~board();

    /*!
     * \brief init - инициализация статических полей класса
     */
    static void init();
    /*!
     * \brief setDefault - задает внутренние значения в исходное состояние
     */
    void setDefault();
    /*!
     * \brief setupPieces - раставляет заново фигуры на доску
     */
    void setupPieces();
    /*!
     * \brief setSpecialPieceFlags - отмечает изменения на схемах рокировок и взятий на проходе
     * \param bm
     */
    void setSpecialPieceFlags(const boardMove &bm);
    /*!
     * \brief update - совершает ход
     * \param bm -ход
     */
    void update(const boardMove &bm);
    /*!
     * \brief getPiece - возвращает фигуру из заданной позиции
     * \param bp - позиция
     * \return - указатель на фигуру
     */
    piece *getPiece(const boardPosition &bp) const;
    /*!
     * \brief setPiece
     * \param p
     * \param bp
     */
    void setPiece(piece *p, const boardPosition &bp);
    /*!
     * \brief addPiecet - добавляет новую фигуру на доску
     * \param p - фигура
     * \param bp - позиция на доске
     */
    void addPiecet(piece *p, const boardPosition &bp);
    /*!
     * \brief removePiece - удаляет фигуру с доски
     * \param bp - удаляет фигуру из заданой позиции
     */
    void removePiece(const boardPosition &bp);
    /*!
     * \brief isPathClear - проверяет есть ли на пути другие фигуры
     * \param bm - ход
     * \return свободен ли путь
     */
    bool isPathClear(const boardMove &bm) const;
    /*!
     * \brief isOccupied - проверяет является ли клетка занятой
     * \param bp - позиция клетки
     * \return занята ли клетка
     */
    bool isOccupied(const boardPosition &bp) const;
    /*!
     * \brief isEnPassantSet - содержит ли взятия на проходе
     * \param bp
     * \return
     */
    inline bool isEnPassantSet(const boardPosition & bp) const
        { return (0 != (bitBoard::getMask(bp) & lEnpassling)); }
    /*!
     * \brief isCheck - проверяет является ли ситуация шаховой для данного цвета
     * \param c - цвет
     * \return - является ли ситуация шаховой
     */
    bool isCheck(piece::color c) const;
    /*!
     * \brief isResultCheck - проверяет является ли ситуация после хода шаховой
     * \param bm - ход
     * \return будет ли шах
     */
    bool isResultCheck(const boardMove &bm) const;
    /*!
     * \brief isMate - проверяет является ли ситуация на доске матом для фигуры звдвнного цвета
     * \param c - цвет
     * \return результат проверки
     */
    bool isMate(piece::color c) const;
    /*!
     * \brief isStalemate - проверяет является ли ситуация на доске патом для фигуры звдвнного цвета
     * \param c - цвет
     * \return результат проверки
     */
    bool isStalemate(piece::color c) const;
    /*!
     * \brief isAttacked - проверяет находится ли фигура под боем
     * \param bp - позиция
     * \param c  - цвет фигуры
     * \return   - признак атаки
     */
    mask isAttacked(const boardPosition& bp, piece::color c) const;
    /*!
     * \brief getLegalMoves - возвращает все допустимые ходы для фигуры в этой клетке
     * \param bp - клетка
     * \return -список ходов
     */
    QList<boardMove> getLegalMoves (const boardPosition &bp, bool cheks = true) const;
    /*!
     * \brief getLegalMoves - возвращает все допустимые ходы для фигуры для фигур этого цвета
     * \param c - цвет
     * \param fast - позволяет не искать все возможные ходы, а возвращает ходы первой попавшейся фигуры
     * \return -список ходов
     */
    QList<boardMove> getLegalMoves (piece::color c, bool cheks = true, bool fast = false) const;
    /*!
     * \brief serialize - получение описания доски в виде структуры
     * \return
     */
    serialBoard serialize() const;

    inline int getYState (const boardPosition &bp) const {
        return ((lColors[piece::WHITE] | lColors[piece::BLACK]) >> bp.y()*8) & 0xff;
    }

    int getXState (const boardPosition &bp) const;

    int getLeftTopDiagState (const boardPosition &bp) const;

    int getRightTopDiagState (const boardPosition &bp) const;


    // Возможные маски атак.
    static mask pawnAttacks[2][64];
    static mask knightAttacks[64];
    static mask kingAttacks[64];
    static mask xAttacks[64][256];
    static mask yAttacks[64][256];
    static mask diagAttacksLeftTop[64][256];
    static mask diagAttacksRightTop[64][256];

    static int pow2[8];

private:
    static piece *allPieces[2][6]; //Указатель на фигуру каждого типа
    static bool isSetup;

    int lTotalPiece[2];     //Полное количество фигур цвета
    int lPieceCount[2][6];  //количество фигур данного типа и цвета

    mask lPieces[6];        //Маска доски по типам фигур
    mask lColors[2];        //Маска доски по цветам фигур
    mask lCastlingFlags;    //Маска доски по допустимым ракировкам
    mask lEnpassling;

    boardPosition kingsPos[2]; //Позиции королей
};



#endif // BOARD_H
