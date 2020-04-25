#ifndef TPSTRATEGY_PLAYER_H
#define TPSTRATEGY_PLAYER_H

#include "Game.h"

class Controller {
public:
    virtual void PerformActions(Game& game) = 0;
    virtual ~Controller() = default;
};


#endif
