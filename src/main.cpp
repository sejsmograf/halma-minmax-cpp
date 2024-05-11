#include <iostream>

#include "AlphaBetaPlayer.hpp"
#include "Halma.hpp"
#include "Heuristics.hpp"
#include "MinmaxPlayer.hpp"

int main() {
    ManhattanDistance distance;
    Halma h;
    AlphaBetaPlayer player1(2, h.PLAYER_ONE, distance);
    AlphaBetaPlayer player2(2, h.PLAYER_TWO, distance);

    for (int i = 0; i < 1000; i++) {
        player1.makeMove(h);
        h.printBoard();
        cout << "\n\n\n";
        if (h.isGameOver) {
            break;
        }

        player2.makeMove(h);
        h.printBoard();
        cout << "\n\n\n";
        if (h.isGameOver) {
            break;
        }
    }

    return 0;
}
