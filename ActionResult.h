#ifndef TPSTRATEGY_ACTIONRESULT_H
#define TPSTRATEGY_ACTIONRESULT_H

enum MoveResult{
    MoveDone,
    TileOvercrowded,
    TileTooFar,
    TileOutOfWorld,
    PathBlocked,
};

enum AttackResult{
    AttackDone,
    CantAttack,
    TargetNotExist,
    TargetOutOfRange,
    NoAttackPoints,
};

enum MineResult{
    MineDone,
    CantMine,
    NoMinePoints,
};

#endif
