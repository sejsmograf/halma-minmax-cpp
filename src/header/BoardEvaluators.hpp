#pragma once

#include "../interface/IBoardEvaluator.hpp"
#include "../interface/IPawnHeuristic.hpp"
#include <random>

class CampDistanceEvaluator : public IBoardEvaluator {
public:
    CampDistanceEvaluator(const IPawnHeuristic &pawnHeuristic);
    float evaluateBoard(const Board &board, FieldType player) const;

private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dis;
    const IPawnHeuristic &pawnHeuristic;
    float squareDistancePenalty(float penalty) const;
};

class CampAndCenterDistanceEvaluator : public IBoardEvaluator {
public:
    CampAndCenterDistanceEvaluator(const IPawnHeuristic &pawnHeuristic);
    float evaluateBoard(const Board &board, FieldType player) const;

private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dis;
    const IPawnHeuristic &pawnHeuristic;
    float squareDistancePenalty(float penalty) const;
};

class MovePotentialEvaluator : public IBoardEvaluator {
public:
    MovePotentialEvaluator(const IPawnHeuristic &pawnHeuristic);
    float evaluateBoard(const Board &board, FieldType player) const;

private:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_int_distribution<int> dis;
    const IPawnHeuristic &pawnHeuristic;
    float squareDistancePenalty(float penalty) const;
};
