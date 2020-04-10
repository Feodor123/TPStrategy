#ifndef TPSTRATEGY_UNIT_H
#define TPSTRATEGY_UNIT_H


#include<vector>
#include "Entity.h"

enum CommandType{

};

class Unit final : public Entity{
public:
    int hp;
    virtual void DoCommand(CommandType command, std::vector<int> params) = 0;
};


#endif
