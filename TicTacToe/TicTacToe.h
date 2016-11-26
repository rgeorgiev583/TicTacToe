#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H

#include <cstdint>

class TicTacToe {
public:
    typedef int_fast8_t Smallint;

    static const Smallint MAX = 1, MIN = -1, ZERO = 0,
                          INF = 64, N_POS = 9;

    TicTacToe();
    ~TicTacToe();

    const Smallint Turn, Depth;
    Smallint v, s[N_POS];
    const TicTacToe *parent;
    TicTacToe *children[N_POS] = {};

    TicTacToe *GetChild(Smallint move);

    bool IsWin() const;
    void Print() const;

    void Search();

private:
    const Smallint move;
    Smallint alpha, beta;

    TicTacToe(const TicTacToe *parent, Smallint move, Smallint alpha, Smallint beta);
};

#endif
