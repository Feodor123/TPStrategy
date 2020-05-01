#ifndef TPSTRATEGY_ACTIONRESULT_H
#define TPSTRATEGY_ACTIONRESULT_H

enum class MoveResult{
    Done,
    TileOvercrowded,
    TileTooFar,
    TileOutOfWorld,
    PathBlocked,
    UnitImmovable,
};

enum class AttackResult{
    Done,
    CantAttack,
    TargetNotExist,
    TargetOutOfRange,
    NoAttackPoints,
};

enum class MineResult{
    Done,
    CantMine,
    NoMinePoints,
};

enum class CreateResult{
    Done,
    CantCreate,
    IncompatibleModules,
    TooExpensive,
    TileOvercrowded,
};

#endif
