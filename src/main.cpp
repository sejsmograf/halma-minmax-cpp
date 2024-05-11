#include <iostream>

#include "./header/AlphaBetaPlayer.hpp"
#include "./header/Halma.hpp"
#include "./header/Heuristics.hpp"
#include "./header/MinmaxPlayer.hpp"
#include "header/BoardEvaluators.hpp"
#include "interface/PawnHeuristic.hpp"

int main() {
    const PawnHeuristic &distance = ManhattanDistance();
    CampDistance evaluator(distance);
    CampCenterDistance centerEvaluator(distance);
    Halma h;
    AlphaBetaPlayer player1(evaluator, 3, h.PLAYER_ONE);
    AlphaBetaPlayer player2(centerEvaluator, 3, h.PLAYER_TWO);

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
