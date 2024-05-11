#include "./header/BoardEvaluators.hpp"

std::random_device CampDistance::rd;
std::mt19937 CampDistance::gen(CampDistance::rd());
std::uniform_int_distribution<int> CampDistance::dis(0, 2);

// CornerDistance
CampDistance::CampDistance(const PawnHeuristic &pawnHeuristic)
    : pawnHeuristic(pawnHeuristic){};

float CampDistance::evaluateBoard(const Board &board, FieldType player) const {

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

float CampDistance::squareDistancePenalty(float penalty) const {
    return penalty * penalty;
}

// CornerCenterDistance
std::random_device CampCenterDistance::rd;
std::mt19937 CampCenterDistance::gen(CampCenterDistance::rd());
std::uniform_int_distribution<int> CampCenterDistance::dis(0, 2);

CampCenterDistance::CampCenterDistance(const PawnHeuristic &pawnHeuristic)
    : pawnHeuristic(pawnHeuristic){};

float CampCenterDistance::evaluateBoard(const Board &board,
                                        FieldType player) const {

    vector<pair<int, int>> goalCamp = board.getPlayerGoalCamp(player);
    vector<pair<int, int>> playerCamp = board.PLAYER_CAMPS.at(player);
    pair<int, int> goalPosition = board.getEmptyGoal(goalCamp);
    vector<pair<int, int>> playerPositions = board.getPlayerPositions(player);
    float evaluation = 0;

    for (const pair<int, int> &position : playerPositions) {
        int row = position.first;
        int col = position.second;
        float goalDistance = pawnHeuristic.evaluatePawnScore(
            row, col, goalPosition.first, goalPosition.second);
        float centerDistance = pawnHeuristic.evaluatePawnScore(row, col, 8, 8);

        evaluation -= squareDistancePenalty(goalDistance);
        evaluation -= centerDistance;

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

float CampCenterDistance::squareDistancePenalty(float penalty) const {
    return penalty * penalty;
}
