#ifndef __TIC_TAC_TOE__
#define __TIC_TAC_TOE__

#include <cstdint>


class TicTacToe
{
public:
    using Integer = int_fast8_t;
    static const Integer Max = 1, Min = -1, Zero = 0, Infinity = 64, Size = 9;

    TicTacToe();
    ~TicTacToe();

    const Integer Turn, move, Depth;

    Integer Payoff;
    Integer alpha, beta;
    Integer Board[Size];

    const TicTacToe* parent;
    TicTacToe *children[Size] = {};

    TicTacToe *GetChild(Integer move);

    bool IsWin() const;
    void Search();
    void Print() const;

private:
    TicTacToe(const TicTacToe* parent, Integer move, Integer alpha, Integer beta);
};

#endif  // __TIC_TAC_TOE__
