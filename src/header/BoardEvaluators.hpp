#pragma once

#include "../interface/BoardEvaluator.hpp"
#include "../interface/PawnHeuristic.hpp"
#include <random>

class CampDistance : public BoardEvaluator {
public:
    CampDistance(const PawnHeuristic &pawnHeuristic);
    float evaluateBoard(const Board &board, FieldType player) const;

private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dis;
    const PawnHeuristic &pawnHeuristic;
    float squareDistancePenalty(float penalty) const;
};

class CampCenterDistance : public BoardEvaluator {
public:
    CampCenterDistance(const PawnHeuristic &pawnHeuristic);
    float evaluateBoard(const Board &board, FieldType player) const;

private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dis;
    const PawnHeuristic &pawnHeuristic;
    float squareDistancePenalty(float penalty) const;
};
