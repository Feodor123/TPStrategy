#include "Game.h"
#include "Entity.h"
#include "Unit.h"
#include <algorithm>

using namespace std;

Game::Game(int length, int width, int startGold) : players{Player(startGold), Player(startGold)}{
    fieldLength = length;
    fieldWidth = width;
    for (int i = 0;i < fieldLength;++i)
        tiles.push_back(Tile(fieldWidth));
    tiles[0].entities.push_back(new Unit(*this,0,0,Unit::FortressStats));
    tiles[fieldLength - 1].entities.push_back(new Unit(*this,1,fieldLength - 1,Unit::FortressStats));
    baseIds[0] = tiles[0].entities[0]->id;
    baseIds[1] = tiles[fieldLength - 1].entities[0]->id;
}

Tile::Tile(int maxCount) {
    this->maxCount = maxCount;
}

bool Tile::CanAdd(const Entity &e) const {
    return entities.size() < maxCount;
}

void Game::OnNewTurn(int playerColor){
    for (int i = 0;i < fieldLength;++i){
        for (int h = 0;h < tiles[i].entities.size();++h){
            if (tiles[i].entities[h]->color == playerColor)
                tiles[i].entities[h]->OnNewTurn();
        }
    }
}

void Game::AddEntity(Entity& e){
    tiles[e.pos].entities.push_back(&e);
    e.OnNewTurn();
}

int Game::End() const {
    if (tiles[0].entities.empty() || tiles[0].entities[0]->id != baseIds[0])
        return 1;
    if (tiles[fieldLength - 1].entities.empty() || tiles[fieldLength - 1].entities[0]->id != baseIds[1])
        return 0;
    return -1;
}

void Game::Kill(Entity& e) {
    tiles[e.pos].entities.erase(find(tiles[e.pos].entities.begin(), tiles[e.pos].entities.end(), &e));
    e.~Entity();
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