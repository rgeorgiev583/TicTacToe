#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H
#include <iostream>

// Represents a tic-tac-toe game state including the history,
// i.e. a node in the game tree.
class TicTacToe {
public:
    static const int MAX = 1, MIN = -1, ZERO = 0;
    static const int N_POS = 9;
    
    // Construct the root node and its descendants
    TicTacToe();

    // Construct a non-root node and its descendants,
    // given its parent node and the move (0 ~ 8) from the parent state to the current state
    TicTacToe(const TicTacToe *parent, int move);

    // Destroy the game tree
    ~TicTacToe();

    // It is MAX's or MIN's turn.
    // For empty board, turn is MAX.
    int turn;

    // Current MAX's gain
    // MAX: X just won
    // MIN: O just won
    // ZERO: game is continuing
    int gain = ZERO;

    // The stone at each position is MAX, MIN, or NEUTRAL.
    int s[N_POS];

    // The previous TicTacToe state (parent node)
    // For the empty board (root node), parent is nullptr
    const TicTacToe *parent;

    // An array containing the child nodes, indexed by the move (0 ~ 8).
    // nullptr indicates a nonexistent child node.
    TicTacToe *children[N_POS];

private:
    // Perform minimax search with alpha-beta pruning while constructing child nodes
    // This is called during construction.
    void search();
};

// Print the current TicTacToe board to ostream
std::ostream &operator<<(std::ostream &out, const TicTacToe &ttt);

#endif
