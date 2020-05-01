#ifndef TPSTRATEGY_PLAYER_H
#define TPSTRATEGY_PLAYER_H

#include "Game.h"

class Controller {
public:
    virtual void PerformActions() = 0;
    virtual void SetGame(Game& game){
        this->game = &game;
    }
    Controller() = default;
    virtual ~Controller() = default;
protected:
    Game* game;
};


#endif
