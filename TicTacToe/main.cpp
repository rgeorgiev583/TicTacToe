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
    cout << "sizeof TicTacToe: " << sizeof TicTacToe << " bytes\n" << endl;
#endif
    cout << "Solving Tic-tac-toe with minimax search "
#if AB_PRUNE
    "WITH"
#else
    "WITHOUT"
#endif
    << " alpha-beta pruning..." << endl;

    auto t1 = std::chrono::high_resolution_clock::now();
        TicTacToe ttt;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    cout << "Time elapsed: " << dt.count() << "ms\n";

    cout << "\nPly\tMAX\tMIN\n";
    for (int d = 1; d <= 9; ++d)
        cout << d << '\t' << ttt.win_counter[d] << '\t' << ttt.lose_counter[d] << '\n';
    cout << "\nDraws\t"<< ttt.draw_counter << '\n'
         << "Leaf\t" << ttt.leaf_counter << '\n'
         << "Nodes\t" << ttt.node_counter << '\n'
         << "\nPress enter to challenge me..." << flush;
    cin.get();

    cout << ttt << flush;

    return EXIT_SUCCESS;
}
