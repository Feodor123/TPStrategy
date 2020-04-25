#ifndef TPSTRATEGY_ENTITY_H
#define TPSTRATEGY_ENTITY_H

#include "vector"
#include "Game.h"

class Entity {
public:
    int id;
    int hp;
    int color;
    int pos;
    Game& game;
    virtual void Hit(int damage);
    virtual void OnNewTurn() = 0;
    virtual ~Entity() = default;

protected:
    Entity(Game& game, int hp, int color, int pos);
private:
    static int currId;
};


#endif
