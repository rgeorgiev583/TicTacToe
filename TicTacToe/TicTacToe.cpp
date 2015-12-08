#include "TicTacToe.h"
#include <cstdio>
#include <iterator>

TicTacToe::TicTacToe():
    turn(MAX), s(), parent(nullptr) {
    
}

TicTacToe::TicTacToe(const TicTacToe *parent, int move):
    turn(parent->turn == MAX ? MIN : MAX), parent(parent) {
    std::copy(std::begin(parent->s), std::end(parent->s), s);
    s[move] = parent->turn;
    // Check if the game is over
    switch(move) {
    case 0:
        
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:

        break;
    case 8:

        break;
    }
}

void TicTacToe::search() {
    for (int p = 0; p < N_POS; ++p) {
        if (s[p] == ZERO) {
            // ReSharper disable once CppNonReclaimedResourceAcquisition
            children[p] = new TicTacToe(this, p);

        } else
            children[p] = nullptr;
    }
}

TicTacToe::~TicTacToe() {
    for (TicTacToe *child : children)
        delete child;
}

// Visualize a stone
char v(int s) {
    const char X = 'x', O = 'o', S = ' ';
    if (s == TicTacToe::MAX)
        return X;
    else if (s == TicTacToe::MIN)
        return O;
    else // if (s == TicTacToe::ZERO)
        return S;
}

std::ostream &operator<<(std::ostream &out, const TicTacToe &t) {
    const int BUFSIZE = 256;
    char buffer[BUFSIZE];
    snprintf(
        buffer, BUFSIZE,
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n",
        v(t.s[0]), v(t.s[1]), v(t.s[2]),
        v(t.s[3]), v(t.s[4]), v(t.s[5]),
        v(t.s[6]), v(t.s[7]), v(t.s[8])
    );
    return out << buffer;
}
