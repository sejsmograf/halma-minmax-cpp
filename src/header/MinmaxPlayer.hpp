#pragma once
#include "../interface/BoardEvaluator.hpp"
#include "../interface/HalmaPlayer.hpp"
#include "../interface/PawnHeuristic.hpp"
#include "./Board.hpp"
#include "./FieldType.hpp"
#include "./Halma.hpp"

using namespace std;

class MinmaxPlayer : public HalmaPlayer {
public:
    MinmaxPlayer(const BoardEvaluator &boardEvaluator, int depth = 1,
                 FieldType maximizingPlayer = FieldType::WHITE);
    void makeMove(Halma &game);

private:
    pair<float, piece_move> minmax(Halma &game, int depth,
                                   FieldType maximizingPlayer,
                                   const BoardEvaluator &boardEvaluator);

private:
    int depth;
    FieldType maximizingPlayer;
    const BoardEvaluator &boardEvaluator;
};
