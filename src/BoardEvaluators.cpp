#include "./header/BoardEvaluators.hpp"

// CampDistanceEvaluator
std::random_device CampDistanceEvaluator::rd;
std::mt19937 CampDistanceEvaluator::gen(CampDistanceEvaluator::rd());
std::uniform_int_distribution<int> CampDistanceEvaluator::dis(0, 2);

CampDistanceEvaluator::CampDistanceEvaluator(
    const IPawnHeuristic &pawnHeuristic)
    : pawnHeuristic(pawnHeuristic){};

float CampDistanceEvaluator::evaluateBoard(const Board &board,
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

float CampDistanceEvaluator::squareDistancePenalty(float penalty) const {
    return penalty * penalty;
}

// CampAndCenterDistanceEvaluator
std::random_device CampAndCenterDistanceEvaluator::rd;
std::mt19937
    CampAndCenterDistanceEvaluator::gen(CampAndCenterDistanceEvaluator::rd());
std::uniform_int_distribution<int> CampAndCenterDistanceEvaluator::dis(0, 2);

CampAndCenterDistanceEvaluator::CampAndCenterDistanceEvaluator(
    const IPawnHeuristic &pawnHeuristic)
    : pawnHeuristic(pawnHeuristic){};

float CampAndCenterDistanceEvaluator::evaluateBoard(const Board &board,
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
        float centerDistance = pawnHeuristic.evaluatePawnScore(
            row, col, board.BOARD_SIZE / 2, board.BOARD_SIZE / 2);

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

float CampAndCenterDistanceEvaluator::squareDistancePenalty(
    float penalty) const {
    return penalty * penalty;
}

// MovePotential
std::random_device MovePotentialEvaluator::rd;
std::mt19937 MovePotentialEvaluator::gen(MovePotentialEvaluator::rd());
std::uniform_int_distribution<int> MovePotentialEvaluator::dis(0, 2);

MovePotentialEvaluator::MovePotentialEvaluator(
    const IPawnHeuristic &pawnHeuristic)
    : pawnHeuristic(pawnHeuristic){};

float MovePotentialEvaluator::evaluateBoard(const Board &board,
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
        int possiblePieceMoves = board.getPieceMoves(row, col).size();

        evaluation -= squareDistancePenalty(goalDistance);
        evaluation += possiblePieceMoves;

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

float MovePotentialEvaluator::squareDistancePenalty(float penalty) const {
    return penalty * penalty;
}
