#ifndef TPSTRATEGY_GAME_H
#define TPSTRATEGY_GAME_H

#include "vector"

class Entity;
class Unit;
class Building;

struct Player{
    Player(int gold){
        this->gold = gold;
    }
    int gold;
    void AddGold(int val){
        gold += val;
    }
};

struct Tile{
    std::vector<Entity*> entities;
    bool CanAdd(const Entity& e) const;
    int maxCount;
    int CurrColor();
};

class Game {
public:
    std::vector<Tile> tiles;
    int fieldLength;
    int fieldWidth;
    Player players[2];

    Game(int length = 20, int width = 5, int startGold = 100);

    //return -1 if not end; winner number else
    int End() const;

    void Kill(Entity& e);

    void Move(Unit& unit, int newPos);

    bool InWorld(int pos) const;
};

#endif
