#include "./header/BoardEvaluators.hpp"

static std::random_device rd;
static std::mt19937 gen;
static std::uniform_int_distribution<int> dis;

DistanceEvaluator::DistanceEvaluator(const PawnHeuristic &pawnHeuristic)
    : pawnHeuristic(pawnHeuristic){};

float DistanceEvaluator::evaluateBoard(const Board &board,
                                       FieldType player) const {

    vector<pair<int, int>> goalCamp = board.getPlayerGoalCamp(player);
    vector<pair<int, int>> playerCamp = board.PLAYER_CAMPS.at(player);
    pair<int, int> goalPosition = board.getEmptyGoal(goalCamp);
    vector<pair<int, int>> playerPositions = board.getPlayerPositions(player);
    float evaluation = 0;

    for (const pair<int, int> &position : playerPositions) {
        int row = position.first;
        int col = position.second;
        float penalty = pawnHeuristic.evaluatePawnScore(
            row, col, goalPosition.first, goalPosition.second);
        evaluation -= squareDistancePenalty(penalty);

        bool isInGoalCamp = false;
        for (const auto &goal : goalCamp) {
            if (goal == position) {
                isInGoalCamp = true;
                break;
            }
        }
        if (isInGoalCamp) {
            evaluation += 1000;
        }
        evaluation += dis(gen);
    }

    return evaluation;
};

float DistanceEvaluator::squareDistancePenalty(float penalty) const {
    return penalty * penalty;
}
