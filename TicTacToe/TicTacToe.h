#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H
#include <iostream>

// Switch alpha-beta pruning on or off
//#define PRUNE

// Represents a tic-tac-toe game state including the history,
// i.e. a node in the game tree.
class TicTacToe {
public:
    static const int MAX = 1, MIN = -1, ZERO = 0;
    static const int N_POS = 9;

    // For statistical purpose
    static int win_counter[],
               lose_counter[],
               draw_counter;

    // Note that even when pruning is on, leaf_counter is the number of valid sequences,
    // which is more then the number of distinct final states.
    static int leaf_counter;

    // Construct the root node and its descendants (i.e. the complete game tree)
    TicTacToe();

    // Construct a non-root node and its descendants,
    // given its parent node and the move (0 ~ 8) from the parent state to the current state
    TicTacToe(const TicTacToe *parent, int move);

    // Destroy the (sub)tree recursively
    ~TicTacToe();

    // It is MAX's or MIN's turn.
    // For empty board, turn is MAX.
    const int turn;

    // The latest move (0 ~ 8) that led to the current state
    // (meaningless for root node)
    const int move;

    // Depth of the node in the tree (0 ~ 9)
    const int depth;

    // Current MAX's gain
    // MAX: X just won
    // MIN: O just won
    // ZERO: game is continuing
    int gain = ZERO;

    // The stone at each board position is MAX, MIN, or NEUTRAL.
    int s[N_POS];

    // The previous TicTacToe state (parent node)
    // For the empty board (root node), parent is nullptr
    const TicTacToe *parent;

    // Array containing pointers to the child nodes, indexed by the move (0 ~ 8).
    // nullptr indicates a nonexistent (invalid) child node.
    TicTacToe *children[N_POS] = {};
    
private:
    // Check if the last player has just won the game
    bool is_win() const;

    // Perform minimax search while constructing child nodes
    // This is called during construction.
    void search();
};

// Print the current TicTacToe board to ostream
std::ostream &operator<<(std::ostream &out, const TicTacToe &ttt);

#endif
