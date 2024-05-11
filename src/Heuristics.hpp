#pragma once
#include <random>

#include "Board.hpp"
#include "FieldType.hpp"
#include "HeuristicDistance.hpp"

class ManhattanDistance : public HeuristicDistance {
public:
    float calculateDistance(int row, int col, int goalRow, int goalCol) const;
};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> dis(0, 1);

static float evaluateBoardState(const Board &board, FieldType playerType,
                                const HeuristicDistance &distanceFunction) {
    vector<pair<int, int>> goalCamp = board.getPlayerGoalCamp(playerType);
    vector<pair<int, int>> playerCamp = board.PLAYER_CAMPS.at(playerType);
    pair<int, int> goalPosition = board.getEmptyGoal(goalCamp);

    vector<pair<int, int>> playerPositions =
        board.getPlayerPositions(playerType);

    float evaluation = 0;
    for (const pair<int, int> &position : playerPositions) {
        int row = position.first;
        int col = position.second;
        evaluation -= distanceFunction.calculateDistance(
            row, col, goalPosition.first, goalPosition.second);

        bool isInGoalCamp = false;
        for (const auto &goal : goalCamp) {
            if (goal == position) {
                isInGoalCamp = true;
                break;
            }
        }
        if (isInGoalCamp) {
            evaluation += 20;
        }
        evaluation += dis(gen);
    }

    return evaluation;
}