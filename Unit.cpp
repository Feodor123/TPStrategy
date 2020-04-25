#include "Unit.h"
#include "Entity.h"

using namespace std;

UnitStats Unit::BasicStats(
        unordered_map<StatType, int>
                {
                        {Cost,        50},
                        {MaxHP,       100},
                        {Speed,       1},
                        {AttackRange, 1},
                        {AttackCount, 1},
                        {Damage,      0},
                        {MineSpeed,   0},
                        {MineCount,   1},
                },
        unordered_map<StatType, bool>
                {
                        {CanAttack, false},
                        {CanMine, false},
                }
);

Unit::Unit(Game &game, int hp, int color, int pos, vector<UnitModuleType> modules) : Entity(game,hp,color,pos), stats(BasicStats){
    stats.AddModules(modules);
    hp = stats.iStats[MaxHP];
}

void Unit::OnNewTurn() {
    movePoints = stats.iStats[StatType::Speed];
    attackPoints = stats.iStats[StatType::AttackCount];
    minePoints = stats.iStats[StatType::MineCount];
}

MoveResult Unit::Go(int position) {
    if (pos == position)
        return MoveDone;
    if (!game.InWorld(position))
        return TileOutOfWorld;
    int l = abs(position - pos);
    if (l > movePoints)
        return TileTooFar;
    if (!game.tiles[position].CanAdd(*this))
        return TileOvercrowded;
    int step = position > pos ? 1 : -1;
    for (int i = 1;i <= l;++i){
        if (game.tiles[pos + i * step].CurrColor() != -1 && game.tiles[pos + i * step].CurrColor() != color)
            return PathBlocked;
    }
    game.Move(*this, position);
    movePoints -= l;
    attackPoints = 0;
    minePoints = 0;
    return MoveDone;
}

AttackResult Unit::Attack(int position, int number){
    if (!stats.iStats[CanAttack])
        return CantAttack;
    if (attackPoints <= 0)
        return NoAttackPoints;
    if (abs(position - pos) > stats.iStats[AttackRange])
        return TargetOutOfRange;
    if (!game.InWorld(position) || game.tiles[position].entities.size() <= number)
        return TargetNotExist;
    game.tiles[position].entities[number]->Hit(stats.iStats[Damage]);
    movePoints = 0;
    attackPoints -= 1;
    minePoints = 0;
    return AttackDone;
}

MineResult Unit::Mine() {
    if (!stats.iStats[CanMine])
        return CantMine;
    if (minePoints <= 0)
        return NoMinePoints;
    game.players[color].AddGold(stats.iStats[MineSpeed]);
    return MineDone;
}

//something like resource retrieval possible, unlike just death
void Unit::SelfDestruct() {
    game.Kill(*this);
}
