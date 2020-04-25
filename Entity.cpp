#include "Entity.h"


int Entity::currId = 0;

Entity::Entity(Game& game, int hp, int color, int pos):game(game){
    this->hp = hp;
    this->pos = pos;
    this->color = color;
    this->id = currId++;
}

void Entity::Hit(int damage) {
    hp = std::max(0, hp - damage);
    if (hp == 0)
        game.Kill(*this);
}
