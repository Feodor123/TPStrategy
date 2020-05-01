#ifndef TPSTRATEGY_UNIT_H
#define TPSTRATEGY_UNIT_H

#include<vector>
#include "Entity.h"
#include "UnitModule.h"
#include "unordered_map"
#include "ActionResult.h"
#include "UnitStats.h"

class Unit : public Entity{
public:
    Unit(Game& game, int color, int pos, std::vector<UnitModuleType>& modules);

    Unit(Game& game, int color, int pos, UnitStats& stats);

    ~Unit() override = default;

    void OnNewTurn() override;

    MoveResult Go(int position);

    AttackResult Attack(int position, int number);

    MineResult Mine();

    CreateResult Create(std::vector<UnitModuleType>& modules);

    void SelfDestruct();

    static UnitStats BasicStats;

    static UnitStats FortressStats;

    int MovePoints(){return movePoints;}

    int AttackPoints(){return attackPoints;}

    int MinePoints(){return minePoints;}

    const UnitStats& Stats(){return stats;}

protected:
    int movePoints;
    int attackPoints;
    int minePoints;
    UnitStats stats;
};


#endif
