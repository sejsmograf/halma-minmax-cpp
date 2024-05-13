#pragma once
#include "../interface/IBoardEvaluator.hpp"
#include "../interface/IHalmaPlayer.hpp"
#include "./FieldType.hpp"
#include "./Halma.hpp"

using namespace std;

class MinmaxPlayer : public IHalmaPlayer {
public:
    MinmaxPlayer(const IBoardEvaluator &boardEvaluator, int depth = 1);
    search_result chooseMove(Halma &game);

private:
    search_result minmax(Halma &game, int depth, FieldType maximizingPlayer,
                         const IBoardEvaluator &boardEvaluator);

private:
    int depth;
    const IBoardEvaluator &boardEvaluator;
};
