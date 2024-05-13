#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

#include "./header/Halma.hpp"
#include "./header/Heuristics.hpp"
#include "./interface/IPawnHeuristic.hpp"
#include "header/AlphaBetaPlayer.hpp"
#include "header/BoardEvaluators.hpp"
#include "interface/IBoardEvaluator.hpp"

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
    const IPawnHeuristic &distance = ManhattanDistance();
    const IBoardEvaluator &moveEvaluator = MovePotentialEvaluator(distance);
    const IBoardEvaluator &evaluator = CampDistanceEvaluator(distance);
    AlphaBetaPlayer player1(moveEvaluator, 2);
    AlphaBetaPlayer player2(evaluator, 2);

    try {
        Halma h(&player1, &player2);
        int visited = h.playGame();
        std::cout << "\nVisited a total of: " << visited << " nodes\n";

    } catch (const exception &ex) {
        cerr << "An error occurred: " << ex.what() << endl;
    }
}
