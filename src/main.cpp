#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

#include "./header/Halma.hpp"
#include "./header/Heuristics.hpp"
#include "./header/MinmaxPlayer.hpp"
#include "./interface/IBoardEvaluator.hpp"
#include "./interface/IPawnHeuristic.hpp"
#include "header/AlphaBetaPlayer.hpp"
#include "header/BoardEvaluators.hpp"

static vector<string> readStdin() {
    vector<string> inputLines;
    if (!isatty(fileno(stdout))) {
        string line;
        while (getline(cin, line)) {
            inputLines.push_back(line);
        }
    }

    return inputLines;
}

int main() {
    Halma h(readStdin());
    const IPawnHeuristic &distance = ManhattanDistance();
    MovePotentialEvaluator moveEvaluator(distance);
    CampAndCenterDistanceEvaluator centerEvaluator(distance);
    AlphaBetaPlayer player1(moveEvaluator, 2, h.PLAYER_ONE);
    AlphaBetaPlayer player2(moveEvaluator, 2, h.PLAYER_TWO);

    for (int i = 0; i < 1000; i++) {
        player1.makeMove(h);
        h.printBoard();
        if (h.isGameOver) {
            break;
        }

        player2.makeMove(h);
        h.printBoard();
        if (h.isGameOver) {
            break;
        }
    }
}
