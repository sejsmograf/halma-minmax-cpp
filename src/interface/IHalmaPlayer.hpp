#pragma once
#include "../header/Halma.hpp"

class IHalmaPlayer {
public:
    virtual void makeMove(Halma &game) = 0;
};
