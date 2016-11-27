#ifndef _TIC_TAC_TOE_H
#define _TIC_TAC_TOE_H

#include <cstdint>

// Represents a tic-tac-toe game state including the history,
// i.e. a node in the game tree.

class TicTacToe {
public:
    using Integer = int_fast8_t;
    static const Integer Max = 1, Min = -1, Zero = 0, Infinity = 64, Size = 9;

    // Construct the root node and its descendants (i.e. the complete game tree)
    TicTacToe();

    // Destroy the (sub)tree recursively
    ~TicTacToe();

    // It is MAX's or MIN's Turn.
    // For empty board, Turn is MAX.
    const Integer Turn;

    // The latest move (0 ~ 8) that led to the current state
    // (meaningless for root node)
    const Integer move;

    // Depth of the node in the tree (0 ~ 9)
    const Integer Depth;

    // Current MAX's payoff
    // (1) X wins
    //     MAX * (10 - Depth)
    // (2) O wins
    //     MIN * (10 - Depth)
    // (3) Draw
    //     ZERO
    Integer v;

    Integer alpha, beta;

    // The stone at each board position is MAX, MIN, or ZERO.
    Integer s[Size];

    // The previous TicTacToe state (parent node)
    // For the empty board (root node), parent is nullptr
    const TicTacToe *parent;

    // Array containing pointers to the child nodes, indexed by the move (0 ~ 8).
    // nullptr indicates a nonexistent (invalid) child node.
    TicTacToe *children[Size] = {};

    TicTacToe *GetChild(Integer move);

    // Check if the last player has just won the game
    bool IsWin() const;

    // Perform minimax Search while constructing child nodes
    // This is called during construction if necessary.
    void Search();

    // Print the current TicTacToe board to stdout
    void Print() const;

private:
    // Construct a non-root node and its descendants,
    // given its parent node and the move (0 ~ 8) from the parent state to the current state
    TicTacToe(const TicTacToe *parent, Integer move, Integer alpha, Integer beta);
};

#endif
