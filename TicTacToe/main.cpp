#include <cstdlib>
#include <iostream>
#include "TicTacToe.h"

using std::cout;
using std::endl;

int main() {
    TicTacToe ttt;
    cout << ttt.leaf_counter << endl;
    std::cin.get();
    return EXIT_SUCCESS;
}
