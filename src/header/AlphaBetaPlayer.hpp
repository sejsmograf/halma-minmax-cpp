#pragma once

#include "../interface/IBoardEvaluator.hpp"
#include "../interface/IHalmaPlayer.hpp"

class AlphaBetaPlayer : public IHalmaPlayer {
public:
    AlphaBetaPlayer(const IBoardEvaluator &boardEvaluator, int depth = 2);
    search_result chooseMove(Halma &game) const;

private:
    search_result alphabeta(Halma &game, int depth, FieldType maximizingPlayer,
                            const IBoardEvaluator &boardEvaluator, float alpha,
                            float beta);

private:
    int depth;
    const IBoardEvaluator &boardEvaluator;
};
