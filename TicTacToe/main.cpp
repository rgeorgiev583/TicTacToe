#include <cstdlib>
#include <limits>
#include <iostream>
#include <ios>
#include <chrono>
#include "TicTacToe.h"
#define IS_DEBUG 0

using std::cout;
using std::cin;
using std::endl;
using std::flush;

void play(TicTacToe *it);

int main() {
#if IS_DEBUG
    cout << "sizeof TicTacToe node: " << sizeof(TicTacToe) << " bytes\n" << endl;
#endif
    cout << "Solving Tic-tac-toe with minimax search "
#if AB_PRUNE
    "WITH"
#else
    "WITHOUT"
#endif
    << " alpha-beta pruning..." << endl;

    auto t0 = std::chrono::high_resolution_clock::now();
        // Root node
        TicTacToe root;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
    cout << "Time elapsed: " << dt.count() << " ms" << endl;

    cout << "\nPly\tMAX\tMIN\n";
    for (int d = 1; d <= 9; ++d)
        cout << d << '\t' << root.win_counter[d]
                  << '\t' << root.lose_counter[d] << '\n';
    cout << "\nDraws\t"<< root.draw_counter << '\n'
         << "Leaves\t" << root.leaf_counter << '\n'
         << "Nodes\t" << root.node_counter << endl;
    cout << "\nPayoff at root node: " << static_cast<int>(root.payoff) << endl;
    for (;;) {        
        play(&root);
        cout << "Press enter to play again..." << endl;
        cin.ignore();
        cin.get();
    }
    return EXIT_SUCCESS;
}

void play(TicTacToe *it) {
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
            return;
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
                else {
                    cout << "Invalid move!" << endl;
                    if (!cin) {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
#if AB_PRUNE

#endif
        } else {
            // Computer move
            if (human == TicTacToe::MAX) {
                TicTacToe::smallint min = +TicTacToe::INF;
                for (TicTacToe::smallint p = 0; p < TicTacToe::N_POS; ++p) {
                    if (it->s[p] == TicTacToe::ZERO) {
                        if (it->children[p]->payoff < min) {
                            min = it->children[p]->payoff;
                            move = p;
                        }
                    }
                }
            } else {
                TicTacToe::smallint max = -TicTacToe::INF;
                for (TicTacToe::smallint p = 0; p < TicTacToe::N_POS; ++p) {
                    if (it->s[p] == TicTacToe::ZERO) {
                        if (it->children[p]->payoff > max) {
                            max = it->children[p]->payoff;
                            move = p;
                        }
                    }
                }
            }
            cout << "Computer move: " << move << endl;
        }
        it = it->children[move];
        if (it->depth == TicTacToe::N_POS || it->is_win()) {
            // Game just ended.
            cout << '\n' << *it << flush;
            TicTacToe::smallint human_payoff = human * it->payoff;
            if (human_payoff > 0)
                cout << "You win!" << endl;
            else if (human_payoff < 0)
                cout << "You lose!" << endl;
            else
                cout << "Draw!" << endl;
            break;
        }
    }
}
