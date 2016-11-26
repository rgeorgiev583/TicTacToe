#include "TicTacToe.h"
#include <cstdio>
#include <iterator>

TicTacToe *TicTacToe::get_child(smallint move) {
    if (!children[move])
        children[move] = new TicTacToe(this, move, -INF, +INF);
    return children[move];
}

bool TicTacToe::is_win() const {
    const smallint pt = parent->turn;
    switch (move) {
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
        turn(MAX), move(-1), depth(0), alpha(-INF), beta(+INF), s(), parent(nullptr) {
    search();
}

TicTacToe::TicTacToe(const TicTacToe *parent, smallint move, smallint alpha, smallint beta):
        turn(-parent->turn), move(move), depth(parent->depth + 1),
        alpha(alpha), beta(beta), parent(parent) {
    std::copy(std::begin(parent->s), std::end(parent->s), s);
    s[move] = parent->turn;
    bool iswin = is_win(),
         isfull = depth == N_POS;
    if (iswin || isfull) {
        // Game just ended.
        if (iswin) {
            // Someone just won.
            v = parent->turn * (10 - depth);
        } else {
            // Draw
            v = ZERO;
        }
    } else {
        // Search for further cases
        search();
    }
}

void TicTacToe::search() {
    if (turn == MAX) {
        smallint max = -INF;
        for (smallint p = 0; p < N_POS; ++p) {
            if (s[p] == ZERO) {
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                children[p] = new TicTacToe(this, p, alpha, beta);
                if (children[p]->v > max) {
                    max = children[p]->v;
#if AB_PRUNE
                    if (max > alpha && (alpha = max) >= beta)
                        break;
#endif
                }
            }
        }
        v = max;
    } else {
        smallint min = +INF;
        for (smallint p = 0; p < N_POS; ++p) {
            if (s[p] == ZERO) {
                // ReSharper disable once CppNonReclaimedResourceAcquisition
                children[p] = new TicTacToe(this, p, alpha, beta);
                if (children[p]->v < min) {
                    min = children[p]->v;
#if AB_PRUNE
                    if (min < beta && (beta = min) <= alpha)
                        break;
#endif
                }
            }
        }
        v = min;
    }
}

TicTacToe::~TicTacToe() {
    for (TicTacToe *child : children)
        delete child;
}

char GetPlayerSign(int p) {
    switch (p)
    {
        case TicTacToe::MAX:
            return 'x';

        case TicTacToe::MIN:
            return 'o';

        default:
            return ' ';
    }
}

void TicTacToe::Print() const {
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
