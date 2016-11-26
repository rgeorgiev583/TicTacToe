#include <cstdlib>
#include <limits>
#include <iostream>
#include <ios>
#include <chrono>
#include "TicTacToe.h"

using std::cout;
using std::cin;
using std::endl;
using std::flush;

bool play(TicTacToe *it);

int main() {
    TicTacToe root;
    while (play(&root));
    return EXIT_SUCCESS;
}

bool play(TicTacToe *it) {
    cout << "\nChoose an option:\n"
        << "(X) Play as MAX\n"
        << "(O) Play as MIN\n"
        << "(Q) Quit" << endl;
    TicTacToe::smallint human = 0;
    while (!human) {
        char option;
        cin >> option;
        switch (option) {
        case 'Q': case 'q':
            return false;
        case 'X': case 'x':
            human = TicTacToe::MAX;
            break;
        case 'O': case 'o':
            human = TicTacToe::MIN;
            break;
        }
    }
    for (;;) { // Each move
        cout << '\n' << *it << flush;
        int move;
        if (it->turn == human) {
            // Human move
            cout << "Your move: " << flush;
            for (;;) {
                cin >> move;
                if (0 <= move && move < TicTacToe::N_POS &&
                        it->s[move] == TicTacToe::ZERO)
                    break;
                cout << "Invalid move!" << endl;
                if (!cin) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        } else {
            // Computer move
            if (human == TicTacToe::MAX) {
                TicTacToe::smallint min = +TicTacToe::INF;
                for (TicTacToe::smallint p = 0; p < TicTacToe::N_POS; ++p) {
                    if (it->s[p] == TicTacToe::ZERO) {
                        TicTacToe *child = it->get_child(p);
                        if (child->v < min) {
                            min = child->v;
                            move = p;
                        }
                    }
                }
            } else {
                TicTacToe::smallint max = -TicTacToe::INF;
                for (TicTacToe::smallint p = 0; p < TicTacToe::N_POS; ++p) {
                    if (it->s[p] == TicTacToe::ZERO) {
                        TicTacToe *child = it->get_child(p);
                        if (child->v > max) {
                            max = child->v;
                            move = p;
                        }
                    }
                }
            }
            cout << "Computer move: " << move << endl;
        }
        it = it->get_child(move);
        if (it->depth == TicTacToe::N_POS || it->is_win()) {
            // Game just ended.
            cout << '\n' << *it << flush;
            TicTacToe::smallint human_payoff = human * it->v;
            if (human_payoff > 0)
                cout << "You win!" << endl;
            else if (human_payoff < 0)
                cout << "You lose!" << endl;
            else
                cout << "Draw!" << endl;
            return true;
        }
    }
}
