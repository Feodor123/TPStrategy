#include "Game.h"
#include "Entity.h"
#include "Unit.h"
#include <algorithm>

using namespace std;

Game::Game(int length, int width, int startGold) : players{Player(startGold), Player(startGold)}{
    fieldLength = length;
    fieldWidth = width;
}

bool Tile::CanAdd(const Entity &e) const {
    return entities.size() >= maxCount;
}

int Game::End() const {

}

void Game::Kill(Entity& e) {
    tiles[e.pos].entities.erase(find(tiles[e.pos].entities.begin(), tiles[e.pos].entities.end(), &e));
}

void Game::Move(Unit& unit, int newPos){
    tiles[unit.pos].entities.erase(find(tiles[unit.pos].entities.begin(), tiles[unit.pos].entities.end(), &unit));
    tiles[newPos].entities.push_back(&unit);
    unit.pos = newPos;
}

int Tile::CurrColor() {
    if (!entities.empty()) {
        return entities[0]->color;
    } else
        return -1;
}

bool Game::InWorld(int pos) const{
    return pos >= 0 && pos < fieldLength;
}