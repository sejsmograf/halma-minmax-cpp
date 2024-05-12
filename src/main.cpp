#include <filesystem>
#include <iostream>
#include <string>

#include "./header/AlphaBetaPlayer.hpp"
#include "./header/Halma.hpp"
#include "./header/Heuristics.hpp"
#include "./header/MinmaxPlayer.hpp"
#include "header/BoardEvaluators.hpp"
#include "interface/BoardEvaluator.hpp"
#include "interface/PawnHeuristic.hpp"

static vector<string> readStdin() {
    vector<string> inputLines;
    string line;
    while (getline(cin, line)) {
        inputLines.push_back(line);
    }

    return inputLines;
}

int main() {
    Halma h(readStdin());
    const PawnHeuristic &distance = ManhattanDistance();
    CampDistance campEvaluator(distance);
    CampCenterDistance cornerEvaluator(distance);

    AlphaBetaPlayer player(campEvaluator, 3, h.PLAYER_ONE);
    ;

    for (int i = 0; i < 1000; i++) {
    }
}
