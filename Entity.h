#ifndef TPSTRATEGY_ENTITY_H
#define TPSTRATEGY_ENTITY_H

#include "vector"
#include "Game.h"

class Entity {
    friend Game;
    friend Tile;
public:
    virtual void Hit(int damage);
    virtual void OnNewTurn() = 0;
    virtual ~Entity() = default;
    int Id(){return id;}
    int HP(){return hp;}
    int Color(){return color;}
    int Pos(){return pos;}
protected:
    int id;
    int hp;
    int color;
    int pos;
    Game& game;
    Entity(Game& game, int hp, int color, int pos);
private:
    static int currId;
};


#endif
