#include "Heuristics.hpp"
#include "Halma.hpp"
#include <cstdlib>

float ManhattanDistance::evaluatePawnScore(int row, int col, int goalRow,
                                           int goalCol) const {
    return abs(row - goalRow) + abs(col - goalCol);
};
