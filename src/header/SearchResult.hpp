#include "Board.hpp"

struct search_result {
    float evaluation;
    piece_move move;
    int visitedNodes;
};
