#include "Unit.h"
#include "Entity.h"
#include "ActionResult.h"

using namespace std;

UnitStats Unit::BasicStats(
        unordered_map<StatType, int>
                {
                        {StatType::Cost,        50},
                        {StatType::MaxHP,       100},
                        {StatType::Speed,       1},
                        {StatType::AttackRange, 1},
                        {StatType::AttackCount, 1},
                        {StatType::Damage,      0},
                        {StatType::MineSpeed,   0},
                        {StatType::MineCount,   1},
                        {StatType::PassiveIncome, 0},
                },
        unordered_map<StatType, bool>
                {
                        {StatType::CanAttack, false},
                        {StatType::CanMine, false},
                        {StatType::Immovable, false},
                        {StatType::Fabric, false},
                }
);

UnitStats Unit::FortressStats(
        unordered_map<StatType, int>
                {
                        {StatType::Cost,        0},
                        {StatType::MaxHP,       800},
                        {StatType::Speed,       0},
                        {StatType::AttackRange, 0},
                        {StatType::AttackCount, 0},
                        {StatType::Damage,      0},
                        {StatType::MineSpeed,   0},
                        {StatType::MineCount,   0},
                        {StatType::PassiveIncome, 50},
                },
        unordered_map<StatType, bool>
                {
                        {StatType::CanAttack, false},
                        {StatType::CanMine, false},
                        {StatType::Immovable, true},
                        {StatType::Fabric, true},
                }
);

Unit::Unit(Game &game, int color, int pos, vector<UnitModuleType>& modules) : Entity(game,-1,color,pos), stats(BasicStats){
    stats.AddModules(modules);
    hp = stats.iStats[StatType::MaxHP];
}

Unit::Unit(Game& game, int color, int pos, UnitStats& stats) : Entity(game,-1,color,pos), stats(stats) {
    hp = stats.iStats[StatType::MaxHP];
}

void Unit::OnNewTurn() {
    movePoints = stats.iStats[StatType::Speed];
    attackPoints = stats.iStats[StatType::AttackCount];
    minePoints = stats.iStats[StatType::MineCount];
    game.players[color].ChangeGold(stats.iStats[StatType::PassiveIncome]);
}

MoveResult Unit::Go(int position) {
    if (stats.bStats[StatType::Immovable])
        return MoveResult::UnitImmovable;
    if (pos == position)
        return MoveResult::Done;
    if (!game.InWorld(position))
        return MoveResult::TileOutOfWorld;
    int l = abs(position - pos);
    if (l > movePoints)
        return MoveResult::TileTooFar;
    if (!game.tiles[position].CanAdd(*this))
        return MoveResult::TileOvercrowded;
    int step = position > pos ? 1 : -1;
    for (int i = 1;i <= l;++i){
        if (game.tiles[pos + i * step].CurrColor() != -1 && game.tiles[pos + i * step].CurrColor() != color)
            return MoveResult::PathBlocked;
    }
    game.Move(*this, position);
    movePoints -= l;
    attackPoints = 0;
    minePoints = 0;
    return MoveResult::Done;
}

AttackResult Unit::Attack(int position, int number){
    if (!stats.bStats[StatType::CanAttack])
        return AttackResult::CantAttack;
    if (attackPoints <= 0)
        return AttackResult::NoAttackPoints;
    if (abs(position - pos) > stats.iStats[StatType::AttackRange])
        return AttackResult::TargetOutOfRange;
    if (!game.InWorld(position) || game.tiles[position].entities.size() <= number)
        return AttackResult::TargetNotExist;
    game.tiles[position].entities[number]->Hit(stats.iStats[StatType::Damage]);
    movePoints = 0;
    attackPoints -= 1;
    minePoints = 0;
    return AttackResult::Done;
}

MineResult Unit::Mine() {
    if (!stats.bStats[StatType::CanMine])
        return MineResult::CantMine;
    if (minePoints <= 0)
        return MineResult::NoMinePoints;
    game.players[color].ChangeGold(stats.iStats[StatType::MineSpeed]);
    return MineResult::Done;
}

CreateResult Unit::Create(vector<UnitModuleType>& modules) {
    if (!stats.bStats[StatType::Fabric])
        return CreateResult::CantCreate;
    if (!UnitModule::AreCompatible(modules))
        return CreateResult ::IncompatibleModules;
    Unit unit = Unit(game,color,pos,modules);
    if (unit.stats.iStats[StatType::Cost] > game.players[color].gold)
        return CreateResult::TooExpensive;
    if (!game.tiles[unit.pos].CanAdd(unit))
        return CreateResult::TileOvercrowded;
    game.AddEntity(*(new Unit(unit)));
    game.players[color].ChangeGold(-unit.stats.iStats[StatType::Cost]);
    return CreateResult::Done;
}

//something like resource retrieval possible, unlike just death
void Unit::SelfDestruct() {
    game.Kill(*this);
}
