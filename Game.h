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
    void ChangeGold(int delta){
        gold += delta;
    }
};

struct Tile{
    Tile(int maxCount);
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
    int baseIds[2];

    Game(int length = 10, int width = 4, int startGold = 200);

    void OnNewTurn(int playerColor);

    //return -1 if not end; winner number else
    int End() const;

    void AddEntity(Entity& e);

    void Kill(Entity& e);

    void Move(Unit& unit, int newPos);

    bool InWorld(int pos) const;
};

#endif
