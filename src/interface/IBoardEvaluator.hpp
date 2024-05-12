#pragma once

#include "../header/Board.hpp"
#include "../header/FieldType.hpp"

class IBoardEvaluator {
public:
    virtual float evaluateBoard(const Board &board, FieldType player) const = 0;
};
