#pragma once
#include "../interface/IBoardEvaluator.hpp"
#include "../interface/IHalmaPlayer.hpp"
#include "../interface/IPawnHeuristic.hpp"
#include "./Board.hpp"
#include "./FieldType.hpp"
#include "./Halma.hpp"

using namespace std;

class MinmaxPlayer : public IHalmaPlayer {
public:
    MinmaxPlayer(const IBoardEvaluator &boardEvaluator, int depth = 1,
                 FieldType maximizingPlayer = FieldType::WHITE);
    void makeMove(Halma &game);

private:
    pair<float, piece_move> minmax(Halma &game, int depth,
                                   FieldType maximizingPlayer,
                                   const IBoardEvaluator &boardEvaluator);

private:
    int depth;
    FieldType maximizingPlayer;
    const IBoardEvaluator &boardEvaluator;
};
