#pragma once

class HeuristicDistance {
public:
    virtual float calculateDistance(int row, int col, int goalRow,
                                    int goalCol) const = 0;
};
