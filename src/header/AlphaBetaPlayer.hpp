#pragma once

#include "../interface/IBoardEvaluator.hpp"
#include "../interface/IHalmaPlayer.hpp"

class AlphaBetaPlayer : public IHalmaPlayer {
public:
    AlphaBetaPlayer(const IBoardEvaluator &boardEvaluator, int depth = 1,
                    FieldType maximizingPlayer = FieldType::WHITE);
    void makeMove(Halma &game);

private:
    pair<float, piece_move> alphabeta(Halma &game, int depth,
                                      FieldType maximizingPlayer,
                                      const IBoardEvaluator &boardEvaluator,
                                      float alpha, float beta);

private:
    int depth;
    FieldType maximizingPlayer;
    const IBoardEvaluator &boardEvaluator;
};
