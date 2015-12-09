# TicTacToe

## Overview

This is a solver for [tic-tac-toe](https://en.wikipedia.org/wiki/Tic-tac-toe), written in C++.

The program (1) searches the game tree using a [minimax](https://en.wikipedia.org/wiki/Minimax) algorithm with or without [alpha-beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) depending on the macro `AB_PRUNE` in [TicTacToe.cpp](TicTacToe/TicTacToe.cpp), and (2) allows the user to play against the computer.

## Usage

The compiler must support the C++11 standard to compile, e.g. modern versions of [GCC](https://gcc.gnu.org/projects/cxx0x.html) or [Visual Studio](https://msdn.microsoft.com/library/hh567368.aspx).

On Windows, open the Visual Studio solution [TicTacToe.sln](TicTacToe.sln).

On Linux,
```
make
bin/tictactoe
```

## Design

To be completed...

## Outcome

To be completed...

## License

This software is licensed under the MIT License. See [LICENSE](LICENSE).
