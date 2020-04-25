#ifndef TPSTRATEGY_UNIT_H
#define TPSTRATEGY_UNIT_H

#include<vector>
#include "Entity.h"
#include "UnitModule.h"
#include "unordered_map"
#include "ActionResult.h"
#include "UnitStats.h"

class Unit final : public Entity{
public:
    int movePoints;
    int attackPoints;
    int minePoints;
    UnitStats stats;

    Unit(Game& game, int hp, int color, int pos, std::vector<UnitModuleType> modules);

    ~Unit() override = default;

    void OnNewTurn() override;

    MoveResult Go(int position);

    AttackResult Attack(int position, int number);

    MineResult Mine();

    void SelfDestruct();

    static UnitStats BasicStats;
};


#endif
