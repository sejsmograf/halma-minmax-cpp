#pragma once

class IPawnHeuristic {
public:
    virtual float evaluatePawnScore(int row, int col, int goalRow,
                                    int goalCol) const = 0;
};
