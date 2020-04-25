#ifndef TPSTRATEGY_UNITMODULE_H
#define TPSTRATEGY_UNITMODULE_H

#include "vector"
#include "unordered_set"
#include "unordered_map"
#include "StatType.h"

enum UnitModuleType{
    Attack1,
    Attack2,
    Attack3,
    Mine1,
    Mine2,
    Mine3,
};

class UnitModule {
public:
    std::unordered_map<StatType, int> iValues;

    std::unordered_map<StatType, bool> bValues;

    std::unordered_set<UnitModuleType> incompatibilities;

    UnitModule() = default;

    UnitModule(std::unordered_set<UnitModuleType> incompatibilities,
            std::unordered_map<StatType, int> iValues,
            std::unordered_map<StatType, bool> bValues);

    static std::unordered_map<UnitModuleType, UnitModule> Templates;

    static bool AreCompatible(std::vector<UnitModuleType>& modules);
};

#endif
