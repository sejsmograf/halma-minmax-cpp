#pragma once
#include "Board.hpp"
#include "FieldType.hpp"
#include "Halma.hpp"
#include "HalmaPlayer.hpp"
#include "Heuristic.hpp"
#include "Heuristics.hpp"

using namespace std;

class MinmaxPlayer : public HalmaPlayer {
public:
    MinmaxPlayer(int depth = 1, FieldType maximizingPlayer = FieldType::WHITE,
                 const Heuristic &distanceFunction = ManhattanDistance());
    void makeMove(Halma &game);

private:
    pair<float, piece_move> minmax(Halma &game, int depth,
                                   FieldType maximizingPlayer,
                                   const Heuristic &distanceFunction);

private:
    int depth;
    FieldType maximizingPlayer;
    const Heuristic &distanceFunction;
};
