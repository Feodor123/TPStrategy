#ifndef TPSTRATEGY_UNITSTATS_H
#define TPSTRATEGY_UNITSTATS_H

#include "UnitModule.h"
#include "unordered_map"

struct UnitStats {
    std::unordered_map<StatType, int> iStats;
    std::unordered_map<StatType, bool> bStats;

    UnitStats(const std::unordered_map<StatType, int>& iVals, const std::unordered_map<StatType, bool>& bVals);

    void AddModules(const std::vector<UnitModuleType>& modules);
};


#endif
