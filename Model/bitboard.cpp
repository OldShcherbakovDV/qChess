#include "bitboard.h"

bitBoard::bitBoard() : lBoard(0LL)
{

}

bitBoard::bitBoard(const unsigned long long &board) : lBoard(board)
{

}

void bitBoard::setBit(const boardPosition &bp)
{
    if (bp.isValid())
        lBoard |= getMask(bp);
}

void bitBoard::unsetBit(const boardPosition &bp)
{
    if (bp.isValid())
        lBoard ^= getMask(bp);
}

void bitBoard::invert()
{
    lBoard = ~lBoard;
}

unsigned long long bitBoard::getXMask(const boardPosition &bp)
{
    unsigned long long mask = 0LL;

    for (int i = 0; i < 8; ++i)
        mask |= (1LL << (bp.x() + 8*i));

    return mask;
}

unsigned long long bitBoard::getYMask(const boardPosition &bp)
{
    return (0xffLL << bp.x()*8);
}

unsigned long long bitBoard::getMask(const boardPosition &bp)
{
    return 1LL << bp.number();
}


