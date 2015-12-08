#include <cstdlib>
#include <iostream>
#include "TicTacToe.h"

using std::cout;
using std::endl;

int main() {
    TicTacToe ttt;
    cout << "Ply\tMAX\tMIN" << endl;
    for (int d = 1; d <= 9; ++d)
        cout << d << '\t' << ttt.win_counter[d] << '\t' << ttt.lose_counter[d] << endl;
    cout << "\nDraws\t"<< ttt.draw_counter << endl;
    cout << "Leaf\t" << ttt.leaf_counter << endl;
    std::cin.get();
    return EXIT_SUCCESS;
}
