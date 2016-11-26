#include <cstdio>
#include <cstdlib>
#include <limits>
#include "TicTacToe.h"

bool play(TicTacToe *it);

int main() {
    TicTacToe root;
    while (play(&root));
    return EXIT_SUCCESS;
}

bool play(TicTacToe *it) {
    printf("\nChoose an option:\n"
           "(X) Play as MAX\n"
           "(O) Play as MIN\n"
           "(Q) Quit\n");
    TicTacToe::smallint human = 0;
    while (!human) {
        char option;
        scanf("%c", &option);
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
        printf("\n");
        it->Print();
        int move;
        if (it->turn == human) {
            // Human move
            printf("Your move: ");
            for (;;) {
                int moveX, moveY;
                scanf("%d %d", &moveX, &moveY);
                move = moveY * 3 + moveX;
                if (0 <= move && move < TicTacToe::N_POS &&
                        it->s[move] == TicTacToe::ZERO)
                    break;
                printf("Invalid move!\n");
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
            printf("Computer move: \n");
        }
        it = it->get_child(move);
        if (it->depth == TicTacToe::N_POS || it->is_win()) {
            // Game just ended.
            printf("\n");
            it->Print();
            TicTacToe::smallint human_payoff = human * it->v;
            if (human_payoff > 0)
                printf("You win!\n");
            else if (human_payoff < 0)
                printf("You lose!\n");
            else
                printf("Draw!\n");
            return true;
        }
    }
}
