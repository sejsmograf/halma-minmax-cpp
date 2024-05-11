#pragma once

#include "../interface/BoardEvaluator.hpp"
#include "../interface/HalmaPlayer.hpp"

class AlphaBetaPlayer : public HalmaPlayer {
public:
    AlphaBetaPlayer(const BoardEvaluator &boardEvaluator, int depth = 1,
                    FieldType maximizingPlayer = FieldType::WHITE);
    void makeMove(Halma &game);

private:
    pair<float, piece_move> alphabeta(Halma &game, int depth,
                                      FieldType maximizingPlayer,
                                      const BoardEvaluator &boardEvaluator,
                                      float alpha, float beta);

private:
    int depth;
    FieldType maximizingPlayer;
    const BoardEvaluator &boardEvaluator;
};
