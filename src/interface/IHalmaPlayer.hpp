#pragma once

#include "../header/SearchResult.hpp"

class Halma;

class IHalmaPlayer {
public:
    virtual search_result chooseMove(Halma &game) const = 0;
    void setPlayer(FieldType player) { this->player = player; }
    FieldType player;
};
