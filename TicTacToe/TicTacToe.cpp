#include <cstdio>
#include <iterator>

#include "TicTacToe.h"

TicTacToe* TicTacToe::GetChild(Integer move)
{
    if (!children[move])
        children[move] = new TicTacToe(this, move, -Infinity, +Infinity);
    return children[move];
}

bool TicTacToe::IsWin() const
{
    const Integer pt = parent->Turn;
    switch (move)
    {
        case 0:
            return (s[1] == pt && s[2] == pt) ||
                   (s[3] == pt && s[6] == pt) ||
                   (s[4] == pt && s[8] == pt);
        case 1:
            return (s[0] == pt && s[2] == pt) ||
                   (s[4] == pt && s[7] == pt);
        case 2:
            return (s[1] == pt && s[0] == pt) ||
                   (s[5] == pt && s[8] == pt) ||
                   (s[4] == pt && s[6] == pt);
        case 3:
            return (s[4] == pt && s[5] == pt) ||
                   (s[0] == pt && s[6] == pt);
        case 4:
            return (s[3] == pt && s[5] == pt) ||
                   (s[1] == pt && s[7] == pt) ||
                   (s[0] == pt && s[8] == pt) ||
                   (s[2] == pt && s[6] == pt);
        case 5:
            return (s[4] == pt && s[3] == pt) ||
                   (s[2] == pt && s[8] == pt);
        case 6:
            return (s[7] == pt && s[8] == pt) ||
                   (s[3] == pt && s[0] == pt) ||
                   (s[4] == pt && s[2] == pt);
        case 7:
            return (s[6] == pt && s[8] == pt) ||
                   (s[4] == pt && s[1] == pt);
        case 8:
            return (s[7] == pt && s[6] == pt) ||
                   (s[5] == pt && s[2] == pt) ||
                   (s[4] == pt && s[0] == pt);
        default:
            return false;
    }
}

TicTacToe::TicTacToe():
        Turn(Max), move(-1), Depth(0), alpha(-Infinity), beta(+Infinity), s(), parent(nullptr)
{
    Search();
}

TicTacToe::TicTacToe(const TicTacToe *parent, Integer move, Integer alpha, Integer beta):
        Turn(-parent->Turn), move(move), Depth(parent->Depth + 1), alpha(alpha), beta(beta), parent(parent)
{
    std::copy(std::begin(parent->s), std::end(parent->s), s);
    s[move] = parent->Turn;
    bool iswin = IsWin(), isfull = Depth == Size;
    if (iswin || isfull)
        v = iswin ? parent->Turn * (10 - Depth) : Zero;
    else
        Search();
}

void TicTacToe::Search()
{
    if (Turn == Max)
    {
        Integer max = -Infinity;
        for (Integer p = 0; p < Size; ++p)
            if (s[p] == Zero)
            {
                children[p] = new TicTacToe(this, p, alpha, beta);
                if (children[p]->v > max)
                {
                    max = children[p]->v;
                    if (max > alpha && (alpha = max) >= beta)
                        break;
                }
            }
        v = max;
    }
    else
    {
        Integer min = +Infinity;
        for (Integer p = 0; p < Size; ++p)
            if (s[p] == Zero)
            {
                children[p] = new TicTacToe(this, p, alpha, beta);
                if (children[p]->v < min)
                {
                    min = children[p]->v;
                    if (min < beta && (beta = min) <= alpha)
                        break;
                }
            }
        v = min;
    }
}

TicTacToe::~TicTacToe()
{
    for (TicTacToe* child: children)
        delete child;
}

char GetPlayerSign(TicTacToe::Integer p) {
    switch (p)
    {
        case TicTacToe::Max:
            return 'x';

        case TicTacToe::Min:
            return 'o';

        default:
            return ' ';
    }
}

void TicTacToe::Print() const
{
    printf(
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n",
        GetPlayerSign(s[0]), GetPlayerSign(s[1]), GetPlayerSign(s[2]),
        GetPlayerSign(s[3]), GetPlayerSign(s[4]), GetPlayerSign(s[5]),
        GetPlayerSign(s[6]), GetPlayerSign(s[7]), GetPlayerSign(s[8])
    );
}
