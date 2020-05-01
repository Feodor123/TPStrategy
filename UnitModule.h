#ifndef TPSTRATEGY_UNITMODULE_H
#define TPSTRATEGY_UNITMODULE_H

#include "vector"
#include "unordered_set"
#include "unordered_map"
#include "StatType.h"
#include "UnitModuleType.h"

struct UnitModule {
    std::unordered_map<StatType, int> iValues;

    std::unordered_map<StatType, bool> bValues;

    std::unordered_set<UnitModuleType> incompatibilities;

    UnitModule() = default;

    UnitModule(std::unordered_set<UnitModuleType> incompatibilities,
            std::unordered_map<StatType, int> iValues,
            std::unordered_map<StatType, bool> bValues);

    static bool AreCompatible(std::vector<UnitModuleType>& modules);
};

#endif
