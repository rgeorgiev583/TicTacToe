#include <cstdlib>
#include <iostream>
#include <chrono>
#include "TicTacToe.h"
#define IS_DEBUG 1

using std::cout;
using std::cin;
using std::endl;
using std::flush;

int main() {
#if IS_DEBUG
    cout << "sizeof TicTacToe node: " << sizeof TicTacToe << " bytes\n" << endl;
#endif
    cout << "Solving Tic-tac-toe with minimax search "
#if AB_PRUNE
    "WITH"
#else
    "WITHOUT"
#endif
    << " alpha-beta pruning..." << endl;

    auto t0 = std::chrono::high_resolution_clock::now();
        TicTacToe ttt;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
    cout << "Time elapsed: " << dt.count() << " ms" << endl;

    cout << "\nPly\tMAX\tMIN\n";
    for (int d = 1; d <= 9; ++d)
        cout << d << '\t' << ttt.win_counter[d] << '\t' << ttt.lose_counter[d] << '\n';
    cout << "\nDraws\t"<< ttt.draw_counter << '\n'
         << "Leaves\t" << ttt.leaf_counter << '\n'
         << "Nodes\t" << ttt.node_counter << endl
         << "\nChoose an option:\n"
         << "(X) Play as MAX\n"
         << "(O) Play as MIN\n"
         << "(Q) Quit" << endl;
    TicTacToe::smallint player = 0;
    while (!player) {
        char option;
        cin >> option;
        if (option == 'Q')
            return EXIT_SUCCESS;
        else if (option == 'X')
            player = TicTacToe::MAX;
        else if (option == 'O')
            player = TicTacToe::MIN;
    }
    cout << ttt << flush;

    return EXIT_SUCCESS;
}
