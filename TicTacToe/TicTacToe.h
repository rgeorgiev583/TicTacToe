#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H

#include <cstdint>


class TicTacToe
{
public:
    using Integer = int_fast8_t;
    static const Integer Max = 1, Min = -1, Zero = 0, Infinity = 64, Size = 9;

    TicTacToe();
    ~TicTacToe();

    const Integer Turn, move, Depth;

    Integer v;
    Integer alpha, beta;
    Integer s[Size];

    const TicTacToe* parent;
    TicTacToe *children[Size] = {};

    TicTacToe *GetChild(Integer move);

    bool IsWin() const;
    void Search();
    void Print() const;

private:
    TicTacToe(const TicTacToe* parent, Integer move, Integer alpha, Integer beta);
};

#endif
