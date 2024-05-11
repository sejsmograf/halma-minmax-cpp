#pragma once
#include "Board.hpp"
#include "FieldType.hpp"
#include "Halma.hpp"
#include "HalmaPlayer.hpp"
#include "HeuristicDistance.hpp"
#include "Heuristics.hpp"

using namespace std;

class MinmaxPlayer : public HalmaPlayer {
public:
    MinmaxPlayer(
        int depth = 1, FieldType maximizingPlayer = FieldType::WHITE,
        const HeuristicDistance &distanceFunction = ManhattanDistance());
    void makeMove(Halma &game);

private:
    pair<float, piece_move> minmax(Halma &game, int depth,
                                   FieldType maximizingPlayer,
                                   const HeuristicDistance &distanceFunction);

private:
    int depth;
    FieldType maximizingPlayer;
    const HeuristicDistance &distanceFunction;
};
