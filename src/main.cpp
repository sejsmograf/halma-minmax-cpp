#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

#include "./header/Halma.hpp"
#include "./header/Heuristics.hpp"
#include "./interface/IPawnHeuristic.hpp"
#include "header/AlphaBetaPlayer.hpp"
#include "header/BoardEvaluators.hpp"
#include "header/MinmaxPlayer.hpp"
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
    const IBoardEvaluator &movePotentialEvaluator =
        MovePotentialEvaluator(distance);
    const IBoardEvaluator &campDistanceEvaluator =
        CampDistanceEvaluator(distance);
    AlphaBetaPlayer player1(campDistanceEvaluator, 2);
    AlphaBetaPlayer player2(campDistanceEvaluator, 2);

    try {
        auto start = chrono::high_resolution_clock::now();

        Halma h(&player1, &player2);
        int visited = h.playGame();

        auto end = chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        std::cout << "\nVisited a total of: " << visited << " nodes";
        std::cout << "\nCalulation time: " << elapsed_seconds.count()
                  << " seconds\n";

    } catch (const exception &ex) {
        cerr << "An error occurred: " << ex.what() << endl;
    }
}
