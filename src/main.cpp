#include <iostream>

#include "./header/AlphaBetaPlayer.hpp"
#include "./header/Halma.hpp"
#include "./header/Heuristics.hpp"
#include "./header/MinmaxPlayer.hpp"
#include "header/BoardEvaluators.hpp"

int main() {
    ManhattanDistance distance;
    DistanceEvaluator evaluator(distance);
    Halma h;
    MinmaxPlayer player1(evaluator, 2, h.PLAYER_ONE);
    MinmaxPlayer player2(evaluator, 2, h.PLAYER_TWO);

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
