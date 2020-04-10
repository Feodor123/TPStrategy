#include "Entity.h"

int Entity::currId = 0;
Entity::Entity(int hp){
    this->hp = hp;
    this->id = currId++;
}