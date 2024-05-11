#pragma once

#include "HalmaPlayer.hpp"
#include "Heuristics.hpp"

class AlphaBetaPlayer : public HalmaPlayer {
public:
    AlphaBetaPlayer(
        int depth = 1, FieldType maximizingPlayer = FieldType::WHITE,
        const HeuristicDistance &distanceFunction = ManhattanDistance());
    void makeMove(Halma &game);

private:
    pair<float, piece_move> alphabeta(Halma &game, int depth,
                                      FieldType maximizingPlayer,
                                      const HeuristicDistance &distanceFunction,
                                      float alpha, float beta);

private:
    int depth;
    FieldType maximizingPlayer;
    const HeuristicDistance &distanceFunction;
};
