#ifndef BOARD_H
#define BOARD_H

//Библиотеки QT
#include <QList>
#include <QDebug>

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
    /*!
     * \brief getKing - Вернуть позицию короля заданного цвета
     * \param c - Цвет
     * \return - Позиция короля
     */
    boardPosition getKing(piece::color c) const;
    /*!
     * \brief haveCastling - проверяет возможность левой или правой роккировки для фигур заданного цвета
     * \param c - цвет
     * \param isLeft - Левая ли роккировка проверяется
     * \return возможна ли такая роккировка
     */
    bool haveCastling(piece::color c, bool isLeft) const;
    /*!
     * \brief getYState - вернуть статус горизонтали
     * \param bp - позиция через которую проходит горизонталь
     * \return статус
     */
    inline int getYState (const boardPosition &bp) const {
        return ((lColors[piece::WHITE] | lColors[piece::BLACK]) >> bp.y()*8) & 0xff;
    }
    /*!
     * \brief getYState - вернуть статус вертикали
     * \param bp - позиция через которую проходит вертикаль
     * \return статус
     */
    int getXState (const boardPosition &bp) const;
    /*!
     * \brief getLeftTopDiagState - вернуть статус левой верхней наклонной
     * \param bp - позиция через которую проходит наклонная
     * \return статус
     */
    int getLeftTopDiagState (const boardPosition &bp) const;
    /*!
     * \brief getLeftTopDiagState - вернуть статус правой верхней наклонной
     * \param bp - позиция через которую проходит наклонная
     * \return статус
     */
    int getRightTopDiagState (const boardPosition &bp) const;


    // Возможные маски атак.
    /*!
     * \brief pawnAttacks - Атаки пешек по цветам
     */
    static mask pawnAttacks[2][64];
    /*!
     * \brief knightAttacks - атаки королей
     */
    static mask knightAttacks[64];
    /*!
     * \brief kingAttacks - атаки короля
     */
    static mask kingAttacks[64];
    /*!
     * \brief xAttacks - атаки по горизонтали
     */
    static mask xAttacks[64][256];
    /*!
     * \brief yAttacks - атаки по вертикали
     */
    static mask yAttacks[64][256];
    /*!
     * \brief diagAttacksLeftTop - Атаки лежащии на левой верхней диаганали
     */
    static mask diagAttacksLeftTop[64][256];
    /*!
     * \brief diagAttacksRightTop - Атаки лежащии на правой верхней диаганали
     */
    static mask diagAttacksRightTop[64][256];
    /*!
     * \brief pow2 - Необходима для оценки приоритетов блоком ии
     */
    static int pow2[8];
    friend class AI;

private:
    /*!
     * \brief allPieces - Указатель на фигуру каждого типа и каждого цвета
     */
    static piece *allPieces[2][6]; //Указатель на фигуру каждого типа
    /*!
     * \brief isSetup -
     */
    static bool isSetup;
    /*!
     * \brief lTotalPiece - Полное количество фигур по цветам
     */
    int lTotalPiece[2];
    /*!
     * \brief lPieceCount - Количество фигур по цветам и типам
     */
    int lPieceCount[2][6];

    /*!
     * \brief lPieces - Маски доски по типам фигур
     */
    mask lPieces[6];
    /*!
     * \brief lColors - Маски доски по цветам фигур
     */
    mask lColors[2];        //Маска доски по цветам фигур
    /*!
     * \brief lCastlingFlags - Маска доски по допустимым ракировкам
     */
    mask lCastlingFlags;
    /*!
     * \brief lEnpassling - Маска доски с помечеными взятиями на проходе
     */
    mask lEnpassling;
    /*!
     * \brief kingsPos - Позиции королей по цветам
     */
    boardPosition kingsPos[2]; //Позиции королей

    /*!
     * \brief getPawnLegalMoves - Вернуть возможные ходы пешки, стоящей в этой позиции
     * \param bp - Позиция
     * \return - Список ходов
     */
    QList<boardMove> getPawnLegalMoves (const boardPosition &bp) const;
    /*!
     * \brief getRookLegalMoves - возвращает допустимые ходы ладьи, стоящей в этой позиции
     * \param bp - Позиция
     * \return - Список ходов
     */
    QList<boardMove> getRookLegalMoves (const boardPosition &bp) const;
    /*!
     * \brief getBishopLegalMoves - возвращает допустимые ходы слона, стоящей в этой позиции
     * \param bp - Позиция
     * \return - Список ходов
     */
    QList<boardMove> getBishopLegalMoves (const boardPosition &bp) const;
    /*!
     * \brief getKnightLegalMoves - возвращает допустимые ходы коня, стоящей в этой позиции
     * \param bp - Позиция
     * \return - Список ходов
     */
    QList<boardMove> getKnightLegalMoves (const boardPosition &bp) const;
    /*!
     * \brief getKingLegalMoves - возвращает допустимые ходы короля, стоящей в этой позиции
     * \param bp - Позиция
     * \return - Список ходов
     */
    QList<boardMove> getKingLegalMoves (const boardPosition &bp) const;
};

#endif // BOARD_H
