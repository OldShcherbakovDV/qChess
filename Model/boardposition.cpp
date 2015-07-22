#include "boardposition.h"

boardPosition::boardPosition() : lX(-1), lY(-1)
{

}

boardPosition::boardPosition(const int &x, const int &y) : lX(x), lY(y)
{

}

boardPosition::boardPosition(const char &x, const int &y) : lX(x - 'a'), lY(y)
{

}

boardPosition::boardPosition(const int number) : lX(number % 8), lY(number / 8)
{

}

